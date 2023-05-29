#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
sem_t S;
int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void* arg)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%100;
        sem_wait(&empty);
        sem_wait(&S);
        buffer[in] = item;
        printf("Producer : Insert Item %d at %d\n",buffer[in],in);
        in = (in+1)%BufferSize;
        sem_post(&S);
        sem_post(&full);
    }
}
void *consumers(void* arg)
{
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        sem_wait(&S);
        int item = buffer[out];
        printf("Consumer: Remove Item %d from %d\n",item, out);
        out = (out+1)%BufferSize;
        sem_post(&S);
        sem_post(&empty);
    }
}

int main()
{

    pthread_t prod, cons;

    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
    sem_init(&S,0,1);

    pthread_create(&prod, NULL, (void *)producer, NULL);
    pthread_create(&cons, NULL, (void *)consumers, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;

}

