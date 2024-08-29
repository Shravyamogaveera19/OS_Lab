#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
    pid_t my_pid,child_pid,parent_pid;
    child_pid =fork();
    if(child_pid < 0)
    {
        printf("Fork not executed properly");
        return 0;
    }
    if(child_pid ==0)
    {
        printf("[CHILD] This is child process");
        my_pid=getpid();
        parent_pid=getppid();
        printf("[CHILD] My pid is:%d",my_pid);
        printf("[CHILD] My parent pid is:%d",parent_pid);
        printf("[CHILD] Exiting");
        exit(0);
    }
    else{
        printf("[PARENT] This is Parent process");
        my_pid=getpid();
        parent_pid=getppid();
        printf("[PARENT] My pid is:%d",my_pid);
        printf("[PARENT] My parent pid is:%d",parent_pid);
        printf("[PARENT] sleeping for 10 seconds\n");
        sleep(10);
        printf("[PARENT] The child process with pid:%d has ended but it still has an entry in process table",child_pid);
        printf("[PARENT]It is a Zombie Process");
    }
}