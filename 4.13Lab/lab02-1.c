#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* runner(void* param); 


int main(int argc, char *argv[])
{
    int Num = 8;
    pthread_t threads[Num];//num of threads
    int thread_num[Num];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    //creating multiple thread
    for(int i=0; i <Num; i++)
    {
        thread_num[i] =i;
        pthread_create(&threads[i], &attr, runner, &thread_num[i]);
    }
        
    //to get out the thread numbber

    for(int i = 0; i<Num; i++)
    {
        pthread_join(threads[i], NULL);
        //thread_num[i] = i;
        //pthread_create(&threads[i], &attr, runner, argv[1]);
    }
    //pthread_join(tid, NULL);
    return 0;
    //printf("I am thread %d\n", pthread_tid);
}

void* runner(void* param)
{
    int *num = (int *)param;
    printf("I am thread %d\n", *num);
    pthread_exit(0);
}
