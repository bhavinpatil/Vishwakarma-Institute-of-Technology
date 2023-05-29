
#include<stdio.h>

#include<pthread.h>

#define R1_SIZE 3

#define C1_SIZE 2

#define R2_SIZE 2

#define C2_SIZE 3



struct matrix{

    int a[R1_SIZE][C1_SIZE];

    int b[R2_SIZE][C2_SIZE];

}o;


void* matmul(void* input){


    int ans[R1_SIZE][C2_SIZE];

     for(int i=0; i<R1_SIZE; i++){

       for(int j=0; j<C2_SIZE; j++){

       ans[i][j] = 0;

         for(int k=0; k<R2_SIZE; k++){

             ans[i][j] += ((struct matrix*)input)->a[i][k] * ((struct matrix*)input)->b[k][j];

         }

         printf("%d ", ans[i][j]);

       }

       printf("\n");

   }

}


int main(){

    int id;

    pthread_t thread;


    printf("Enter no. of rows and columns in matrix 1: ");
    scanf("%d %d",&R1_SIZE,&C1_SIZE);

    printf("Enter no. of rows and columns in matrix 2: ");
    scanf("%d %d",&R2_SIZE,&C2_SIZE);


    if(C1_SIZE != R2_SIZE){

       printf("Invalid size... Cannot multiply\n");

       exit(0);

    }



   printf("Matrix 1\n");

   for(int i=0; i<R1_SIZE; i++){

       for(int j=0; j<C1_SIZE; j++){

           printf("%d %d -> ", i, j);

           scanf("%d", &o.a[i][j]);

       }

   }

   printf("\nMatrix 2\n");

   for(int i=0; i<R2_SIZE; i++){

       for(int j=0; j<C2_SIZE; j++){

           printf("%d %d -> ", i, j);

           scanf("%d", &o.b[i][j]);

       }

   }


    id = pthread_create(&thread, NULL, matmul, (void*)&o);

    if(id == 0){

        printf("Thread created successfully\n");

    }

    else{

        printf("Error creating thread");

    }



    pthread_join(thread, NULL);

}
