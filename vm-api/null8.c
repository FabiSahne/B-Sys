#include <stdio.h>
#include <stdlib.h>

int main() {

    int *array = malloc(100*sizeof(int));

    free(&array[50]);
    return 0;
} 
