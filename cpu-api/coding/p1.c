#include <stdio.h>
#include <unistd.h>

int main()
{
    int x = 100;
    int p = fork();
    if (p < 0) {
        printf("fork failed");
    }
    else if (p == 0)
    {
        // child process
        x+=5;
        printf("Child:\t%d\n", x);
    }
    else
    {
        // parent process
        x+=3;
        printf("Parent:\t%d\n", x);
    }
}
