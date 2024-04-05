#include <stdio.h>
#include <stdlib.h>

int main() {

    int *array = malloc(100*sizeof(int));
    free(array);

    printf("Value of `array[50]` after `free`: %d\n", array[50]);

    return 0;
} 
