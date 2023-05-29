#ifndef FRAME_SIZE
#include "./headers/containers.h"
#include "utilities.c"
#include "./headers/errors.h"
#endif

// ! - What is SLAVE MODE / MASTER MODE ?
void executeUserProgram(MEMCONTEXT *memContext, PCB *jobPCB, INTERRUPTS *interrupts)
{
    int realAddress;
    int virtualAddress;
    int PI = 0;
    int isValid = FALSE;

    jobPCB->ttc = 0;
    memContext->fWritePtr = fopen("./IO/output.txt", "w");

    while (TRUE)
    {
        addressMap(memContext, memContext->IC, &realAddress);

        // TODO Handle PI error checking
        if (PI != 0)
            break;

        // ?  IR <- M[IC]
        memcpy(memContext->IR, memContext->M[realAddress], 4);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * VALID OPERAND OR NOT
        checkIfValidOperand(memContext->IR, &isValid);
        if (!isValid)
        {
            interrupts->PI = 2;
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * LR
        if ((memContext->IR[0] == 'L') && (memContext->IR[1] == 'R'))
        {
            ++jobPCB->ttc;

            char virtualAddressInChar[4];
            convertCharArrToNumber(&(memContext->IR[2]), &virtualAddress, 2);
            convertNumberToCharArr(virtualAddress, virtualAddressInChar, 4);
            // addressMap(memContext, virtualAddress, &realAddress);
            memcpy(memContext->R, virtualAddressInChar, 4);
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * SR
        else if ((memContext->IR[0] == 'S') && (memContext->IR[1] == 'R'))
        {
            jobPCB->ttc += 2;

            convertCharArrToNumber(&(memContext->IR[2]), &virtualAddress, 2);
            addressMap(memContext, virtualAddress, &realAddress);

            memcpy(memContext->M[realAddress], memContext->R, 4);
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * CR
        else if ((memContext->IR[0] == 'C') && (memContext->IR[1] == 'R'))
        {
            ++jobPCB->ttc;
            int virtualIRStart, virtualRStart;
            int realIRStart, realRStart;

            // ? These are logical addresses
            convertCharArrToNumber(&memContext->IR[2], &virtualIRStart, 2);
            convertCharArrToNumber(&memContext->R[2], &virtualRStart, 2);

            // TODO MAP IRStart and RStart with their real addresses
            addressMap(memContext, virtualIRStart, &realIRStart);
            addressMap(memContext, virtualRStart, &realRStart);

            // ? DIRECTLY STORING THE RESULT IN memContext->C by passing its address
            compareString(memContext->M[realIRStart], memContext->M[realRStart], 4 * PAGE_SIZE, &memContext->C);
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * BT
        else if ((memContext->IR[0] == 'B') && (memContext->IR[1] == 'T'))
        {
            ++jobPCB->ttc;

            if (memContext->C == TRUE)
            {
                int jumpOffset;
                convertCharArrToNumber(memContext->IR + 2, &jumpOffset, 2);
                memContext->IC = jumpOffset - 1;
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * GDm
        else if ((memContext->IR[0] == 'G') && (memContext->IR[1] == 'D'))
        {
            jobPCB->ttc += 2;
            interrupts->SI = 1;

            convertCharArrToNumber(memContext->IR + 2, &virtualAddress, 2);
            addressMap(memContext, virtualAddress, &realAddress);

            int res = readLine(memContext->fReadPtr, memContext->buffer);
            if (res == -1)
            {
                printf("\n!!! UNEXPECTED EOF !!!\n");
                exit(1);
            }

            if ((memContext->buffer[0] == '$') && (memContext->buffer[0] == 'E'))
            {
                printf("\n!!! NO DATA FOUND TO READ !!!\n");
                exit(1);
            }

            memcpy(memContext->M[realAddress], memContext->buffer, 4 * PAGE_SIZE);
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * PD
        else if ((memContext->IR[0] == 'P') && (memContext->IR[1] == 'D'))
        {
            ++jobPCB->ttc;
            ++jobPCB->tlc;
            interrupts->SI = 2;

            int PTRBaseAddr = memContext->PTR * PAGE_SIZE;
            int PTE = PTRBaseAddr + (virtualAddress / PAGE_SIZE);
            checkIfPageFault(memContext->M, PTE, &isValid);

            // * CHECKING WHETHER THE LOCATION ACTUALLY EXISTS i.e PAGE FAULT?
            if (!isValid)
            {
                // TODO - INVOKE SOME INTERRUPT
            }
            // * IF EXISTS THEN PUT IT IN OUTPUT.TXT
            else
            {
                convertCharArrToNumber(memContext->IR + 2, &virtualAddress, 2);
                addressMap(memContext, virtualAddress, &realAddress);

                memcpy(memContext->buffer, memContext->M[realAddress], 4 * PAGE_SIZE);
                writeLine(memContext->fWritePtr, memContext->buffer);
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // * H
        else if ((memContext->IR[0] == 'H'))
        {
            ++jobPCB->ttc;
            interrupts->SI = 3;
            putc('\n', memContext->fWritePtr);
            putc('\n', memContext->fWritePtr);
            break;
        }
        else
        {
            // TODO - Handle OPCODE ERROR
            interrupts->PI = 1;
        }

        ++memContext->IC;
        if (jobPCB->ttc > jobPCB->ttl)
        {
            // TODO - GENERATE INTERRUPTS
        }
    }
}

void startExecution(MEMCONTEXT *memContext, PCB *job, INTERRUPTS *interrupts)
{
    memContext->IC = 0;
    executeUserProgram(memContext, job, interrupts);
}

// void terminate(int errorMessage){
//     if(errorMessage == OPERATION_CODE_ERROR){

//     }
// }

// void interruptHandler(INTERRUPTS *interrupts){
//     if(interrupts->TI == 0){
//         if(interrupts->SI == 3){
//             terminate(NO_ERROR);
//         }
//         else if(interrupts->PI = 1){
//             terminate(OPERATION_CODE_ERROR);
//         }
//         else if(interrupts->PI = 2){
//             terminate(OPERAND_ERROR);
//         }
//         else if(interrupts->PI = 3){
//             // TODO - valid page fault allocate, update page table, adjust IC if needed
//             // TODO - resume execution of 'executeUserProgram()' program otherwise terminate(6)

//             // TODO - Check valid page fault or not and rest of the stuff
//             // if(checkIfPageFault())
//             terminate(INVALID_PAGE_FAULT_ERROR);
//         }
//     }
//     else if (interrupts->TI == 2){
//         if (interrupts->SI == 1){
//             terminate(TIME_LIMIT_EXCEEDED_ERROR);
//         }
//         else if(interrupts->SI == 2){
//             // TODO - Write then terminate
//             terminate(TIME_LIMIT_EXCEEDED_ERROR);
//         }
//         else if(interrupts->SI == 3){
//             terminate(NO_ERROR);
//         }
//         else if(interrupts->PI == 1){
//             terminate(TIME_LIMIT_EXCEEDED_ERROR);
//             terminate(OPERATION_CODE_ERROR);
//         }
//         else if(interrupts->PI == 2){
//             terminate(TIME_LIMIT_EXCEEDED_ERROR);
//             terminate(OPERAND_ERROR);
//         }
//         else if(interrupts->PI == 3){
//             terminate(TIME_LIMIT_EXCEEDED_ERROR);
//         }
//     }
// }