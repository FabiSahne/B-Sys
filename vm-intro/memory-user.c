#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(1);
    }

    // print PID for use with pmap
    printf("PID: %d\n", getpid());
    
    // number of megabytes to allocate
    size_t mb = atoi(argv[1]);
    if (mb == 0) {        
        exit(1);
    }

    // allocate memory
    int *array = (int*) malloc(mb*1024*1024);
    if (array == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        exit(1);
    }
    printf("Allocated %zu MB\n", mb);

    // loop indefinitely and mutate the array.
    size_t i = 0;
    while (1)
    {
        if (i == mb*1024*1024/sizeof(int))
        {
            i = 0;
        }
        array[i] += 1;
        i += 1;
    }
}
