#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// TODO - convert the .c into proper header files
#include "utilities.c"
#include "execution.c"
// #include "headers/utilities.h"
#include "headers/errors.h"


int main(){
    MEMCONTEXT memContext;
    PCB job;
    job.ttc = 0;
    job.tlc = 0;
    INTERRUPTS interrupts;
    interrupts.SI = 0;
    interrupts.TI = 0;
    
    init(memContext.M, REAL_MEMORY_LEN*4);

    memContext.fReadPtr = fopen("./IO/input.txt", "r");
    
    while(!feof(memContext.fReadPtr)){
        // TODO Confirm the location of PCB, where it is to be initialized
        int res = readLine(memContext.fReadPtr, memContext.buffer);
        if(res == -1){
            printf("\n ENCOUNTERED EOF \n");
            break;
        }

        // * check if CONTROL CARD
        if(memContext.buffer[0] == '$'){

            // * AMJ
            if(memContext.buffer[1] == 'A'){
                // ? Getting frame index for page table
                memContext.PTR = allocate(memContext.M, REAL_MEMORY_LEN);
                memset(memContext.M[memContext.PTR*10], '*', 4*PAGE_SIZE);
                char tempArr[4];
                
                // ? Copying JOB ID
                memcpy(tempArr, memContext.buffer+4, 4);
                convertCharArrToNumber(tempArr, &job.jId, 4);
                
                // ? COPYING TOTAL TIME LIMIT
                memcpy(tempArr, memContext.buffer+8, 4);
                convertCharArrToNumber(tempArr, &job.ttl, 4);
                
                // ? COPYING TOTAL LINE LIMIT
                memcpy(tempArr, memContext.buffer+12, 4);
                convertCharArrToNumber(tempArr, &job.tll, 4);
            }
            // * DTA
            else if (memContext.buffer[1] == 'D'){
                startExecution(&memContext, &job, &interrupts);
            }
            // * END
            else if (memContext.buffer[1] == 'E'){
                break;
            }
        }
        // * else PROGRAM CARD
        else{
            int pageTableInternalOffset = 0;
            int newPageOffset = -1;
            
            if(feof(memContext.fReadPtr)){
                printf("!!! UNEXPECTED EOF !!!\n");
            }

            // ? CREATING A NEW PAGE AND ADDING IT TO PTR
            createNewPage(&memContext, pageTableInternalOffset, &newPageOffset);
            ++pageTableInternalOffset;

            int internalPageOffset = 0, readerOffset = 0;
            char first;

            while(TRUE){
                first = memContext.buffer[readerOffset];

                // * IF PAGE OFFSET GOES ABOVE 10 INDEXES
                if(internalPageOffset > 9){
                    // ? CREATING A NEW PAGE AND ADDING IT TO PTR
                    createNewPage(&memContext, pageTableInternalOffset, &newPageOffset);
                    ++pageTableInternalOffset;
                    internalPageOffset = 0;
                }
                
                // * IF READER OFFSET IS ON END OF LINE
                if(first == '\0'){
                    res = readLine(memContext.fReadPtr, memContext.buffer);
                    readerOffset = 0;
                    first = memContext.buffer[readerOffset];
                    if(res == -1){
                        printf("!!! UNEXPECTED EOF !!!");
                        exit(1);
                    }
                }

                if(first == 'H'){
                    memContext.M[(newPageOffset*10) + internalPageOffset][0] = memContext.buffer[readerOffset];
                    ++internalPageOffset;
                    break;
                } else {
                    memcpy(memContext.M[(newPageOffset*10) + internalPageOffset], &memContext.buffer[readerOffset], 4);
                    readerOffset += 4;
                    ++internalPageOffset;
                }
            }
            
        }
    }

}