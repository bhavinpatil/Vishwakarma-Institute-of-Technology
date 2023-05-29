#ifndef FRAME_SIZE
    #include "./headers/containers.h"
    #include "utilities.c"
#endif
#include "./headers/errors.h"
#include <stdarg.h>


void terminate(PCB *jobPCB, INTERRUPTS *interrupts, FILE *fWritePtr, int errCount, ...){
    int errorId;
    va_list argPointer;
    va_start(argPointer, errCount);
    
    fprintf(fWritePtr, "%s", "Execution Terminated Abnormally\n\n");

    for(int i=0 ; i<errCount ; i++){
        errorId = va_arg(argPointer, int);

        if(errorId == NO_ERROR){
            printf("IN NO ERROR");
        }
        else if(errorId == OUT_OF_DATA_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ OUT_OF_DATA_ERROR ~~~~~~ \n");
        }
        else if(errorId == LINE_LIMIT_EXCEEDED_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ LINE_LIMIT_EXCEEDED_ERROR ~~~~~~ \n");
        }
        else if(errorId == TIME_LIMIT_EXCEEDED_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ TIME_LIMIT_EXCEEDED_ERROR ~~~~~~ \n");
        }
        else if(errorId == OPERATION_CODE_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ OPERATION_CODE_ERROR ~~~~~~ \n");
        }
        else if(errorId == OPERAND_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ OPERAND_ERROR ~~~~~~ \n");
        }
        else if(errorId == INVALID_PAGE_FAULT_ERROR){
            fprintf(fWritePtr, "%s", "~~~~~~ INVALID_PAGE_FAULT_ERROR ~~~~~~ \n");
        }
    }
    

    fprintf(fWritePtr, "%s", "\n---------------------------------------------------------------\n");
    fprintf(fWritePtr, "%s", "|  JID  |  TTC  |  TLC  |  TTL  |  TLL  |   SI  |   TI  |   PI  |\n");
    fprintf(fWritePtr, "%s", "---------------------------------------------------------------\n");
    fprintf(fWritePtr, "|  %3d  |  %3d  |  %3d  |  %3d  |  %3d  |  %3d  |  %3d  |  %3d  |\n ", jobPCB->JID, jobPCB->TTC, jobPCB->TLC, jobPCB->TTL, jobPCB->TLL, interrupts->SI, interrupts->SI, interrupts->TI, interrupts->PI);
    fprintf(fWritePtr, "%s", "---------------------------------------------------------------\n");

    exit(1);
}

//====================Master Mode
void interruptHandler(PCB *jobPCB, INTERRUPTS *interrupts, FILE *fileWriter){
    if(interrupts->TI == 0){
        if(interrupts->SI == 3){
            terminate(jobPCB, interrupts, fileWriter, 1, NO_ERROR);
        }
        else if(interrupts->PI == 1){
            terminate(jobPCB, interrupts, fileWriter, 1, OPERATION_CODE_ERROR);
        }
        else if(interrupts->PI == 2){
            terminate(jobPCB, interrupts, fileWriter, 1, OPERAND_ERROR);
        }
        else if(interrupts->PI == 3){
            // TODO - valid page fault allocate, update page table, adjust IC if needed
            // TODO - resume execution of 'executeUserProgram()' program otherwise terminate(6)

            // TODO - Check valid page fault or not and rest of the stuff
            // if(checkIfPageFault())
            terminate(jobPCB, interrupts, fileWriter, 1, INVALID_PAGE_FAULT_ERROR);
        }
    } 
    else if (interrupts->TI == 2){
        
        if(interrupts->PI == 1){
            terminate(jobPCB, interrupts, fileWriter, 2, TIME_LIMIT_EXCEEDED_ERROR, OPERATION_CODE_ERROR);
        } 
        else if(interrupts->PI == 2){
            terminate(jobPCB, interrupts, fileWriter, 2, TIME_LIMIT_EXCEEDED_ERROR, OPERAND_ERROR);
        }

        if (interrupts->SI == 1){
            terminate(jobPCB, interrupts, fileWriter, 1, TIME_LIMIT_EXCEEDED_ERROR);
        } 
        else if(interrupts->SI == 2){
            // TODO - Write then terminate
            terminate(jobPCB, interrupts, fileWriter, 1, TIME_LIMIT_EXCEEDED_ERROR);
        } 
        else if(interrupts->SI == 3){
            terminate(jobPCB, interrupts, fileWriter, 1, NO_ERROR);
        } 
        else if(interrupts->PI == 3){
            terminate(jobPCB, interrupts, fileWriter, 1, TIME_LIMIT_EXCEEDED_ERROR);
        }
    }
}

// ! - What is SLAVE MODE / MASTER MODE ?
void executeUserProgram(MEMCONTEXT *memContext, PCB *jobPCB, INTERRUPTS *interrupts){
    int realAddress;
    int virtualAddress;
    int PI = 0;
    int isValid = FALSE;
    int isValidOperand = TRUE;
    
    jobPCB->TTC = 0;
    memContext->fWritePtr = fopen("./IO/output.txt", "w");


    while(TRUE){
        addressMap(memContext, memContext->IC, &realAddress);
        
        // TODO Handle PI error checking
        if(PI != 0) break;
        
        // ?  IR <- M[IC]
        memcpy(memContext->IR, memContext->M[realAddress], 4);

        checkIfValidOperand(memContext->IR, &isValidOperand);

        // * INVALID OPERAND
        if(!isValidOperand){
            interrupts->PI = 2;
        }
        
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * LR
        if((memContext->IR[0] == 'L') && (memContext->IR[1] == 'R')){
            ++jobPCB->TTC;

            if(isValidOperand){
                char virtualAddressInChar[4];
                convertCharArrToNumber(&(memContext->IR[2]), &virtualAddress, 2);
                convertNumberToCharArr(virtualAddress, virtualAddressInChar, 4);
                // addressMap(memContext, virtualAddress, &realAddress);
                memcpy(memContext->R, virtualAddressInChar, 4);
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * SR
        else if((memContext->IR[0] == 'S') && (memContext->IR[1] == 'R')){
            jobPCB->TTC += 2;
            
            if(isValidOperand){
                convertCharArrToNumber(&(memContext->IR[2]), &virtualAddress, 2);
                addressMap(memContext, virtualAddress, &realAddress);
                
                memcpy(memContext->M[realAddress], memContext->R, 4);
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * CR
        else if((memContext->IR[0] == 'C') && (memContext->IR[1] == 'R')){
            ++jobPCB->TTC;

            if(isValidOperand){
                int virtualIRStart, virtualRStart ;
                int realIRStart, realRStart;
                
                // ? These are logical addresses
                convertCharArrToNumber(&memContext->IR[2], &virtualIRStart, 2);
                convertCharArrToNumber(&memContext->R[2], &virtualRStart, 2);
                
                // TODO MAP IRStart and RStart with their real addresses
                addressMap(memContext, virtualIRStart, &realIRStart);
                addressMap(memContext, virtualRStart, &realRStart);

                // ? DIRECTLY STORING THE RESULT IN memContext->C by passing its address
                compareString(memContext->M[realIRStart], memContext->M[realRStart], 4*PAGE_SIZE, &memContext->C); 
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * BT
        else if((memContext->IR[0] == 'B') && (memContext->IR[1] == 'T')){
            ++jobPCB->TTC;
            
            if(isValidOperand){
                if(memContext->C == TRUE){
                    int jumpOffset;
                    convertCharArrToNumber(memContext->IR+2, &jumpOffset, 2);
                    memContext->IC = jumpOffset - 1;
                }
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * GD
        else if((memContext->IR[0] == 'G') && (memContext->IR[1] == 'D')){
            jobPCB->TTC += 2;
            interrupts->SI = 1;
            
            if(isValidOperand){
                convertCharArrToNumber(memContext->IR+2, &virtualAddress, 2);
                addressMap(memContext, virtualAddress, &realAddress);
                
                int res = readLine(memContext->fReadPtr, memContext->buffer);
                if(res == -1){
                    printf("\n!!! UNEXPECTED EOF (Out of Data Error) !!!\n");
                    exit(1);
                }

                // * NO ERROR JUST TERMINATE THE EXECUTION
                if((memContext->buffer[0] == '$') && (memContext->buffer[0] == 'E')){
                    // terminate(jobPCB, interrupts, 1, NO_ERROR);
                    exit(1);
                }
                
                memcpy(memContext->M[realAddress], memContext->buffer, 4 * PAGE_SIZE);
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * PD
        else if((memContext->IR[0] == 'P') && (memContext->IR[1] == 'D')){
            ++jobPCB->TTC;
            ++jobPCB->TLC;
            interrupts->SI = 2;
            
            if(isValidOperand){
                int PTRBaseAddr = memContext->PTR * PAGE_SIZE;
                int PTE = PTRBaseAddr + (virtualAddress / PAGE_SIZE);
                checkIfPageFault(memContext->M, PTE, &isValid);

                // * CHECKING WHETHER THE LOCATION ACTUALLY EXISTS i.e PAGE FAULT?
                if(!isValid){
                    // TODO - INVOKE SOME INTERRUPT
                }
                // * IF EXISTS THEN PUT IT IN OUTPUT.TXT
                else {
                    convertCharArrToNumber(memContext->IR+2, &virtualAddress, 2);
                    addressMap(memContext, virtualAddress, &realAddress);
                    
                    memcpy(memContext->buffer, memContext->M[realAddress], 4 * PAGE_SIZE);
                    writeLine(memContext->fWritePtr, memContext->buffer);
                }
            }
        }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * H
        else if((memContext->IR[0] == 'H')){
            ++jobPCB->TTC;
            interrupts->SI = 3;
            putc('\n', memContext->fWritePtr);
            putc('\n', memContext->fWritePtr);
            break;
        }
        // * OPCODE ERROR
        else {
            interrupts->PI = 1;
        }

        ++memContext->IC;

        if(jobPCB->TTC > jobPCB->TTL){
            interrupts->TI = 2;
        }
        if(jobPCB->TLC > jobPCB->TLL){
            terminate(jobPCB, interrupts, memContext->fWritePtr, 1, LINE_LIMIT_EXCEEDED_ERROR);
        }

        interruptHandler(jobPCB, interrupts, memContext->fWritePtr);
    }
}


void startExecution(MEMCONTEXT *memContext, PCB *job, INTERRUPTS *interrupts){
    memContext->IC = 0;
    executeUserProgram(memContext, job, interrupts);
}


// jid counter 
// program termiated abromally


