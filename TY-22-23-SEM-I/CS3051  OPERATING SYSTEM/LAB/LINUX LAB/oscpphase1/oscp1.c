#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readLine(FILE *file, char *buffer)
{
    int res = fscanf(file, "%[^\n]", buffer);
    getc(file);
    return res;
}

void init(char *M, int size)
{
    memset(M, '\0', size * sizeof(char));
}

void execution(char *IR, char *M)
{
    int IC = 0, SI;
    memcpy(IR, M[IC++], 4);
    if(IR[0] == 'G'){
        SI=1;
    }
    else if(IR[0] == 'P')
    {
        SI=2;
    }
}


int main()
{
    char M[100][4];
    char R[4];
    char IR[4];
    int IC;
    int C;
    char buffer[41];

    FILE *file = fopen("./input.txt", "r");

    while (!feof(file))
    {
        int res = readLine(file, buffer);
        if ((buffer[0] == '$') && (buffer[1] == 'A'))
        {
            init(M, 100 * 4);
            init(R, 4);
            init(IR, 4);

            res = readLine(file, buffer);

            int i = 0, offset = 0;

            while (1)
            {
                char first = buffer[offset];
                if (first == 'H')
                {
                    M[i++][0] = buffer[offset];
                    break;
                }
                else
                {
                    memcpy(M[i++], buffer + offset, 4);
                    offset += 4;
                }
            }
        }
        else if ((buffer[0] == '$') && (buffer[0] == 'D'))
        {
            execution(IR, M);
        }
        else if ((buffer[0] == '$') && (buffer[0] == 'E'))
        {
        }
    }

    fclose(file);
    return 0;
}