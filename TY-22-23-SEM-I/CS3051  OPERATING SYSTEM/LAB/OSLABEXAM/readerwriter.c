#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex,wrt;

int readcount = 0;
int cnt = 1;

void *writer(void *arg){
    int num = (int)arg;

    pthread_mutex_lock(&wrt);
    printf("\n Writer %d is in critical section\n",num);
    printf("\n Writer %d have written data as %d\n",num,++cnt);
    sleep(1);
    pthread_mutex_unlock(&wrt);
    printf("\n Writer %d leaves the critical section\n",num);

}

void * reader(void *arg){
    int num = (int)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);

    if(readcount == 1){
        pthread_mutex_lock(&wrt);
    }

    printf("\n Reader %d is in critical section\n",num);
    printf("\n Reader %d read data as %d\n",num,cnt);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);

    printf("\n Reader %d leaves the critical section\n",num);

    if(readcount == 0){
        pthread_mutex_unlock(&wrt);
    }

}

int main()
{
    pthread_t r[4],w[3];
    pthread_mutex_init(&wrt,NULL);
    pthread_mutex_init(&mutex,NULL);

    for(int i=0;i<4;i++){
        pthread_create(&r[i],NULL,reader,(void *)i+1);
    }

    for(int j=0;j<3;j++){
        pthread_create(&w[j],NULL,writer,(void *)j+1);
    }

    for(int i=0;i<4;i++){
        pthread_join(r[i],NULL);
    }

    for(int j=0;j<3;j++){
        pthread_join(w[j],NULL);
    }



    return 0;
}
