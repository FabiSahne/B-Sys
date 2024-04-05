#include <stdio.h>
#include <stdlib.h>

int main() {

    int *array = malloc(100*sizeof(int));

    printf("Accessing `array[100]`:\n");
    array[100] = 0;

    free(array);
    return 0;
} 
