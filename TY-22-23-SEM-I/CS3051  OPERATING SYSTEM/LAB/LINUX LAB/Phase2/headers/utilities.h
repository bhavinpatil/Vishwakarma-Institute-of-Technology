#pragma once
#include <stdio.h>
#include "containers.h"

/**
*   Arg 1 -> (*M)[4]
*   We pass the memory to check whether the already given memory is not returned again.
*   Arg 2 -> limit
*   Is the total size of the memory
*/
int allocate(char (*M)[4], int limit);

// READ LINE ~ INPUT READER ~ LINE BY LINE
int readLine(FILE *fptr, char* buffer);

void writeLine(FILE *fptr, char* content);

void init(char (*M)[4], int size);

/**
*   If you have address, for example 16 then this converts a char arr -> ['0', '0', '1', '6'] if the length is 4
*   Not checking whether it is bigger than that, MF do your own error checking
*/
void convertNumberToCharArr(int number, char* numberInCharArr, int length);

/**
 *  Exactly opposite of convertIntToCharNumber.
 *  if ['0', '0', '1', '6'] is passed then 16 is stored in the other 
 *  the number should be a char array of len 4
*/
void convertCharArrToNumber(char *numberInCharArr, int *number, int length);

void createNewPage(MEMCONTEXT *memCntx, int *offset, int *newPageOffset);

void compareString(char *str1, char *str2, int len, int *areEqual);

/**
 * Maps the virtual address to the real address
*/
void addressMap(MEMCONTEXT *memCntx, int virtualAddress, int *realAddress);


void isValidOperand(char *IR, int *validOperandFlag);

void checkIfPageFault(char (*M)[4], int realAddress, int *isValid);

// ~~~~~~~~~~~~~~~~~~~~~~~ DEBUGGING UTILITIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void printMemoryContents(char (*arr)[4]);