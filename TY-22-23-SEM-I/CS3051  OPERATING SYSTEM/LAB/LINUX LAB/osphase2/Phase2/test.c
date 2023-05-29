#include <stdio.h>
#include <string.h>

char* convertIntToCharAddrress(int address, char *cantThinkOfAGoodVariableName){
	int ptr = 3;
	while(address != 0){
		cantThinkOfAGoodVariableName[ptr--] = (char)((address%10) + 48);
		address /= 10;
	}
	while(ptr>=0){
		cantThinkOfAGoodVariableName[ptr--] = '0';
	}
	return cantThinkOfAGoodVariableName;
}

int convertCharToIntNumber(char *number){
	int res = 0;
	for(int i=0 ; i<4 ; i++){
		int temp = (int)number[i] - 48;
		res = (res * 10) + (temp);
	}
	return res;
}

int main(){
    char M[4];
    int n = 44;
    char cantThinkOfAGoodVariableName[4];
    memcpy(M, convertIntToCharAddrress(n, cantThinkOfAGoodVariableName), 4);
    printf("%c%c%c%c\n", M[0], M[1], M[2], M[3]);
	printf("num = %d\n", convertCharToIntNumber(M));
    return 0;
}