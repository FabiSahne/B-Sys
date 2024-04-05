#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p = fork();
    if (p < 0)
    {
        printf("fork failed");
    }
    else if (p == 0)
    {
        // child
        close(STDOUT_FILENO);
        printf("This should not print\n");
    }
    else
    {
        // parent
        wait(NULL);
        printf("This should print\n");
    }
    
}