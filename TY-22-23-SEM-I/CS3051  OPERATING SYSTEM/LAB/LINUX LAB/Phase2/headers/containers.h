#define TRUE 1
#define FALSE 0
#define REAL_MEMORY_LEN 300
#define VIRTUAL_MEMORY_LEN 100
#define FRAME_SIZE 10
#define PAGE_SIZE FRAME_SIZE

typedef struct pcb{
    int jId;
    int ttc; // ? Total Time Counter
    int tlc; // ? Total Limit Counter
    int ttl; // ? Total Time Limit 
    int tll; // ? Total Line Limit
} PCB;

typedef struct memoryContext{
    char M[300][4];
    char R[4];
    char IR[4];
    int IC;
    int C;
    char buffer[41];
    FILE *fReadPtr;
    FILE *fWritePtr;
    int PTR;
} MEMCONTEXT;

typedef struct interrupts{
    int PI;
    int SI;
    int TI;
} INTERRUPTS;

