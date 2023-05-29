#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int readLine(FILE *fptr, char* buffer){
    // ^ is an indication for the inverted set for the given scanset
    int res = fscanf(fptr, "%[^\n]", buffer);
    getc(fptr);
    return res;
}

void init(char *M, int size){
    memset(M, '\0', size * sizeof(char));
}

int main(){
    char M[100][4];
    char R[4];
    char IR[4];
    int IC;
    int C;
    char buffer[41];

    FILE *fptr = fopen("./input.txt", "r");


    while(!feof(fptr)){
        int res = readLine(fptr, buffer);
        
        if((buffer[0] == '$') && (buffer[1] == 'A')){
            init(*M, 100 * 4);
            init(R, 4);
            init(IR, 4);

            res = readLine(fptr, buffer);

            int i=0, offset=0;
            char instruction[4];


            while(1){
                char first = buffer[offset];
                if(first == 'H'){
                    M[i++][0] = buffer[offset];
                    break;
                } else {
                    memcpy(M[i++], buffer+offset, 4);
                    offset+=4;
                }
            }
        }
        else if((buffer[0] == '$') && (buffer[0] == 'D')){

        }
        else if((buffer[0] == '$') && (buffer[0] == 'E')){

        }
    }

    fclose(fptr);
    return 0;
}