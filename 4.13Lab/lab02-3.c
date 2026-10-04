#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

void* runner(void* param); 
int isPrime(long n);

struct thread_info
{//infor for each thread
    long startingNum;
    long endNum;
    int count;
};

//shared variable for the group/chunks
long nextNum = 2;
long maxNum;
int chunkSize;
pthread_mutex_t lock;

int main(int argc, char *argv[])
{
    int Num = atoi(argv[1]);//num of thre
    long Num2 = atol(argv[2]);//for second num inoput
    int chunksSize = atoi(argv[3]);
    pthread_t threads[Num];//array of threads
    //int thread_num[Num];
    struct thread_info thread_info[Num];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    maxNum = Num2;
    chunkSize = chunksSize;
    pthread_mutex_init(&lock, NULL);

    //creating multiple thread
    for(int i=0; i <Num; i++)
    {
        //thread_info[i].startingNum = 2 + i * (Num2 -1) / Num;
        //thread_info[i].endNum = 2 + (i + 1) * (Num2 -1) / Num;
        thread_info[i].count = 0;
        //thread_num[i] =i;
        pthread_create(&threads[i], &attr, runner, &thread_info[i]);
    }
        
    //to wait  thread to finish
    for(int i = 0; i<Num; i++)
    {
        pthread_join(threads[i], NULL);
        //thread_num[i] = i;
        //pthread_create(&threads[i], &attr, runner, argv[1]);
    }

    int total =0;
    
    for(int i =0; i<Num; i++)
    {
        total += thread_info[i].count;
    }

    printf("Num of Prime Numbers: %d\n", total);
    //pthread_join(tid, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
    //printf("I am thread %d\n", pthread_tid);
}

void* runner(void* param)
{
    struct thread_info *info = (struct thread_info *)param;

    while(1)
    {
        long startingNum;
        long endNum;

        pthread_mutex_lock(&lock);//before getting the grouo lock it

        //if all num are used we unclok
        if(nextNum > maxNum)
        {
            pthread_mutex_unlock(&lock);
            break;
        }

        //we will get next group and make sure it doesnt go past M if
        startingNum = nextNum;
        endNum = nextNum + chunkSize - 1;

        if(endNum > maxNum)
        {
            endNum = maxNum;
        }

        //move to next group and unlock after
        nextNum = endNum + 1;
        pthread_mutex_unlock(&lock);

        for(long i = startingNum; i<=endNum; i++)
        {
            if(isPrime(i))
            {
                info ->count++;
            }
        }
    }
    

    pthread_exit(0);
}

int isPrime(long n) {  

    if (n == 2 || n == 3) 
    {
        return 1;
    }  

    if (n < 2 || (n % 2) == 0) 
    {
        return 0;
    }  

    for (int i = 3; i < sqrt((double)n) + 1; i+=2) 
    {  
        if ((n % i) == 0) 
        {
            return 0; 
        }  
    }  

    return 1;  
}