#include <unistd.h>
#include "sys/wait.h"
#include <stdio.h>

int main(void)
{
    int fd[2];
    int status;

    pipe(fd);
    pid_t id;
    // printf("%d", fd[0]);
    // printf("%d", fd[1]);
    // pipe(fd);
    // printf("%d", fd[0]);
    // printf("%d", fd[1]);
    // pipe(fd);
    // printf("%d", fd[0]);
    // printf("%d", fd[1]);
    id = fork();
    if (id == 0)
    {
        printf("child");
        printf("%d\n", fd[0]);
        printf("%d", fd[1]);

    }
    else if (id > 0)
    {
        waitpid(id, &status, WNOHANG);
        printf("parant");
        printf("%d\n", fd[0]);
        printf("%d", fd[1]);
        

    }
}