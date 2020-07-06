#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <fcntl.h> // open
#include <unistd.h>
#include <time.h>

#define N_BUFFER 128

int main (int argc, char const *argv[])
{
        char buffer[N_BUFFER], c;
        int nread = N_BUFFER;
        char token;
        int tokenExists = 0;

        // to calculate time passed:
        time_t t_0 = time(NULL), t_1; // t_0 -> time now, t_1 -> time after the io actions is done.
        clock_t tCPU_0 = clock(), tCPU_1;
        float elapsed;

        int in = open("geheim.in", O_RDONLY); 
        int out = open("geheim.out", O_WRONLY);

        // means more than gcc
        if (argc > 1) {

                token = argv[1][1];
                tokenExists = 1;
        }

        while (nread == N_BUFFER) 
        {
                nread = read(in, buffer, N_BUFFER);
                if (tokenExists) {
                        for (int i = 0; i < nread; i++) 
                        {
                                if (buffer[i] == token)
                                {
                                        printf("Token found at %d\n", i);
                                }
                        }
                }
                printf("Token is: %c\n", token);
                write(out, buffer, nread);
        }

        system("cat geheim.out");

        t_1 = time(NULL);
        tCPU_1 = clock();
        elapsed = (float) (tCPU_1 - tCPU_1)/CLOCKS_PER_SEC; // get seconds elapsed
        printf("Dauer: %ld sec, : %f sec\n", (long) t_1 - t_0, elapsed);

        return 0;
}
