#include <stdio.h> // printf
#include <unistd.h> // fork
#include <signal.h> // kill
#include <sys/types.h> // kill

int main(int argc, char const *argv[])
{
        pid_t pid_parent, pid_cain, pid_abel;
        int fd[2], n, kill_ret; // fd for pipes.

        pid_parent = getpid();
        if ((pid_cain = fork()) != 0)
        {
                // parent side
                if ((pid_abel = fork()) != 0)
                {
                        // parent!
                        printf("I am parent. pid: %i, pid cain: %i, pid abel: %i\n", pid_parent, pid_cain, pid_abel);
                }
                else 
                {

                }
        } 
        else 
        {
                pid_cain = getpid();
                printf("I am Cain, pid: %i\n", pid_cain);
        }

        return 0;
}
