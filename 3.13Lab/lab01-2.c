#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[] ) {
    pid_t pid;//for the process id
    int is_child = 0;
    int child_num = 0;

    //FROM COMMAND LINE WE GET N
    int N = atoi(argv[1]);
    //int *data = malloc(sizeof(int) * 100);

    //printf("Before Fork\n");
    int *data = mmap ( NULL, 100 * sizeof(int),
             PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0 );

    if (data == (int*)-1) 
    {
        printf("mmap failed!\n");
        return 0;
    }

    pid = fork();//creates the child
    is_child = (pid == 0);//checks if its the child

    for (int i = 0; !is_child && i < N - 1; i++) 
    {
        pid = fork();
        is_child = (pid == 0);
        child_num++;
    }

    pid = getpid();//get its own pid

    //printf("After Fork: %d\n", pid);
    if (is_child) 
    {
        printf("Hi, I am JMH-%d\n", pid);
        srand(pid);
        int ranNum = rand() % 10000;//0-9999
        printf("Random number is %d. \n", ranNum);
        data[child_num] = ranNum;
    }

    if (!is_child) 
    {
        for (int i = 0; i < N; i++) 
        {
            wait(NULL);
        }

        //printf("%d waited on all my children.\n", pid);
        //printf("My children's ids are:");

        int BiggestNum = data[0];
        for (int i = 0; i < N; i++) 
        {
            if(data[i] >BiggestNum)
            {
                BiggestNum = data[i];
            }
        }

        printf("Highest random number is %d\n", BiggestNum);
    }
}