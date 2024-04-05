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
        int w = wait(NULL);
        printf("`wait()` in child: %d\n", w);
    }
    else
    {
        // parent
        int w = wait(NULL);
        printf("`wait()` in parent: %d\n", w);
    }
    
}