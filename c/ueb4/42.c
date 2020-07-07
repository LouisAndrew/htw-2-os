#include <stdio.h> // printf
#include <unistd.h> // fork, read, close
#include <sys/wait.h> // wait
#include <stdlib.h> // abs
#include <string.h> // strlen

#define DIM_MATRIX 10
#define MAX_CHAR 16

struct client_server 
{
        int fd[DIM_MATRIX][2];
        pid_t pid_row[DIM_MATRIX];

        int n;
        float result;
};

void server (struct client_server *);
void client (struct client_server *);
float calculate (int n);

int main(int argc, char const *argv[])
{
        struct client_server cs, *pcs;
        int i;
        pcs -> result = 0;

        for (i = 0; i < DIM_MATRIX; i++)
        {
                if (pipe(pcs -> fd[i]) < 0)
                {
                        printf("Error on creating pipe\n");
                        return 2;
                }

                pcs -> n = i;
                pcs -> pid_row[i] = fork();
                if (pcs -> pid_row[i] == 0) // create client side
                {
                        client(pcs);
                } 
                else if (pcs -> pid_row > 0) // create server side
                {
                        server(pcs);
                }
                else 
                {
                        printf("Error on fork %d\n", i);
                        return 2;
                }
        }

        printf("Dim Matrix: %i, Sum: %.0f, check: %.0f\n", DIM_MATRIX, pcs -> result, DIM_MATRIX * (DIM_MATRIX + 1) / 2.0);

        return 0;
}

void client (struct client_server *pcs)
{
        char buffer[MAX_CHAR];
        int n = pcs -> n;
        sprintf(buffer, "%.0f\0", calculate(n)); // put the result inside buffer

        close(pcs -> fd[n][0]);
        write(pcs -> fd[n][1], buffer, strlen(buffer) + 1);

        exit (0);
}

void server (struct client_server *pcs)
{
        char buffer[MAX_CHAR];
        int status_wait;
        float temp;

        int n = pcs -> n;

        close(pcs -> fd[n][1]);
        read(pcs -> fd[n][0], buffer, MAX_CHAR);
        waitpid(pcs -> pid_row[n], &status_wait, 0); // waiting for pid. pid from pcs.pid_row[n], assign the status code to status_wait and expects exit code 0

        sscanf(buffer, "%f", &temp); // assign content of buffer to temp.
        pcs -> result += temp;
}

float calculate (int n)
{
        float A[DIM_MATRIX][DIM_MATRIX], v[DIM_MATRIX], result;
        int i,j;

        // creating the matrix
        for ( j=0;j<DIM_MATRIX;j++)
        {
                for ( i=0;i<DIM_MATRIX;i++)
                {
                        A[j][i]= (float)abs((n-i));
                }
                v[j] = 0.0;
        }

        v[0] = (float) DIM_MATRIX/(DIM_MATRIX-1);
        v[DIM_MATRIX-1] = 1.0/(DIM_MATRIX-1);
        result = 0.0;

        for ( i=0; i< DIM_MATRIX; i++)
        {
                result = result + A[n][i]*v[i];
        }

        return(result);
}
