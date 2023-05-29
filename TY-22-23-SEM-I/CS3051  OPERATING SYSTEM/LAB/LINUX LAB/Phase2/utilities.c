#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "./headers/containers.h"

int allocate(char (*M)[4], int limit){
	limit = limit / 10;
	srand(time(0));

    int random;
	random = rand() % limit;
	if(M[random * 10][0] != '\0'){
		for(int i=1 ; i<limit ; i++){
			char c = M[((random + i) % limit) * 10][0];
			if(c == '\0'){
				return random + i;
			}
		}
	}

    return random;
}


int readLine(FILE *fptr, char* buffer){
	// ^ is an indication for the inverted set for the given scanset
	memset(buffer, '\0', 10*4);
	int res = fscanf(fptr, "%[^\n]", buffer);
	getc(fptr);
	return res;
}


void writeLine(FILE *fptr, char* content){
	fprintf(fptr, "%s", content);
	fputc('\n', fptr);
}


void init(char (*M)[4], int size){
	memset(M, '\0', size * sizeof(char));
}


void convertNumberToCharArr(int number, char *numberInCharArr, int length){
	int ptr = length-1;
	while((number != 0)  && (ptr >= 0)){
		numberInCharArr[ptr--] = (char)((number%10) + 48);
		number /= 10;
	}
	while(ptr>=0){
		numberInCharArr[ptr--] = '0';
	}
}


void convertCharArrToNumber(char *numberInCharArr, int *number, int length){
	*number = 0;
	for(int i=0 ; i<length ; i++){
		*number = (*number * 10) + ((int)numberInCharArr[i] - 48);
	}
}


void checkIfPageFault(char (*M)[4], int realAddress, int *isValid){
	*isValid = TRUE;

	if((M[realAddress][3] == '*') || (M[realAddress][3] == '\0')){
		*isValid = FALSE;
	}
}


void createNewPage(MEMCONTEXT *memCntx, int offset, int *newPageOffset){
	*newPageOffset = allocate(memCntx->M, REAL_MEMORY_LEN);
	char newPageOffsetInChar[4];
	
	memset(memCntx->M[*newPageOffset*10], '*', 4*PAGE_SIZE);
	// addressMap(memCntx, *offset, &realAddress);
	convertNumberToCharArr(*newPageOffset, newPageOffsetInChar, 4);
	memcpy(&memCntx->M[(memCntx->PTR * 10) + offset], newPageOffsetInChar, 4);
}


void addressMap(MEMCONTEXT *memCntx, int virtualAddress, int *realAddress){
	// ? PTR = Page Table Register
	// ? PTE = Page Table Entry
	int PTRBaseAddr = memCntx->PTR * PAGE_SIZE;
	int PTE = PTRBaseAddr + (virtualAddress / PAGE_SIZE);
	int pageFound = FALSE;

	checkIfPageFault(memCntx->M, PTE, &pageFound);
	
	// * PAGE NOT FOUND => PAGE FAULT
	if(!pageFound){
		int newPageOffset;
		char newPageOffsetInCharArr[4];

		int pageTableEntryOffset = PTE % (memCntx->PTR * PAGE_SIZE);

		createNewPage(memCntx, pageTableEntryOffset, &newPageOffset);
		convertNumberToCharArr(newPageOffset, newPageOffsetInCharArr, 4);
		memcpy(memCntx->M[PTE], newPageOffsetInCharArr, 4);
		*realAddress = newPageOffset * 10;
	}	
	else {
		int targetAddress;
		convertCharArrToNumber(memCntx->M[PTE], &targetAddress, 4);
		*realAddress = (targetAddress * 10) + (virtualAddress % PAGE_SIZE);
	}
}


void checkIfValidOperand(char *IR, int *validOperandFlag){
    *validOperandFlag = FALSE;
    
    if((('0' <= IR[2])&&(IR[2] <= '9')) && (('0' <= IR[3])&&(IR[3] <= '9'))){
        *validOperandFlag = TRUE;
    }
}



void compareString(char *str1, char *str2, int len, int *areEqual){
	*areEqual = TRUE;
	for(int i=0 ; i<len ; i++){
		// printf("%c <=> %c\n", *(str1+i), *(str2+i));
		if(*(str1+i) != *(str2+i)) {
			*areEqual = FALSE;
			break;
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~ DEBUGGING UTILITIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void printMemoryContents(char (*arr)[4]){
	for(int i=0;i<70;i++){
		printf("%d   ", i);
		for(int j=0;j<4;j++){
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

// int main(){
//     char M[100][4];
//     int limit=10;
//     for(int i=0 ; i<limit ; i++){
//         if(i == 8){  
//             M[i*10][0] = '\0';
//             continue;
//         }
//         M[i*10][0] = '1';
//         printf("%d\n", i);
//     }
//     int frame = allocate(M, limit);
//     printf("FRAME = %d\n", frame);
// }