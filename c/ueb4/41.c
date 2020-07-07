#include <stdio.h> // printf
#include <unistd.h> // fork
#include <signal.h> // kill
#include <sys/types.h> // kill
#include <string.h>

#define N_WAIT 10
#define N_KILL 3
#define MAX_CHAR 128

int main(int argc, char const *argv[])
{
        pid_t pid_parent, pid_cain, pid_abel;
        int fd[2], n, kill_ret; // fd for pipes.
        char buffer[MAX_CHAR];

        if (pipe(fd) < 0) {
                printf("Pipe Error.\n");
                return 2;
        }

        pid_parent = getpid();
        if ((pid_cain = fork()) != 0)
        {
                // parent side
                if ((pid_abel = fork()) != 0)
                {
                        // parent!
                        printf("I am parent. pid: %i, pid cain: %i, pid abel: %i\n", pid_parent, pid_cain, pid_abel);
                        sleep(N_WAIT);
                        printf("Parent ressurected\n");
                }
                else 
                {
                        // abel
                        pid_abel = getpid();
                        close(fd[0]); // close read pipe.
                        sprintf(buffer, "%d", (int) pid_abel); // int to char -> fit pid abel to buffer.
                        write(fd[1], buffer, strlen(buffer) + 1); // \0 on the end of string often is not counted by sprintf

                        for (int i = 0; i < N_WAIT; i++) 
                        {
                                printf("I am  Abel, pid: %i\n", pid_abel);

                                if (i == N_KILL)
                                {
                                        kill_ret = kill(pid_cain, 1);
                                        if (kill_ret == 0)
                                                printf("Killed my brother..\n");
                                        else 
                                                printf("I can't kill my brother\n");
                                }

                                sleep(1);
                        }
                }
        } 
        else 
        {
                // cain
                pid_cain = getpid();

                close(fd[1]);
                read(fd[0], buffer, MAX_CHAR);
                for (int i = 0; i < N_WAIT; i++)
                {
                        printf("I am Cain, pid: %i, PID Abel: %s -> From pipe\n", pid_cain, buffer);
                        sleep(1);
                }
        }

        return 0;
}