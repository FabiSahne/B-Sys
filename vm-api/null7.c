#include <stdio.h>

#include "vec.h"

int main() {

    printf("New Vector:\n");
    vec ve;
    vec *v = &ve;

    vecNew(v);

    vecPrint(v);

    printf("Pushing values:\n");
    vecPush(v, 1);
    vecPrint(v);
    vecPush(v, 2);
    vecPrint(v);
    vecPush(v, 3);
    vecPrint(v);
    vecPush(v, 4);
    vecPrint(v);
    printf("`realloc` should happen here:\n");
    vecPush(v, 5);
    vecPrint(v);
    vecPush(v, 6);
    vecPrint(v);
    vecPush(v, 7);
    vecPrint(v);
    vecPush(v, 8);
    vecPrint(v);

    printf("Popping values:\n");
    vecPop(v);
    vecPrint(v);
    vecPop(v);
    vecPrint(v);
    vecPop(v);
    vecPrint(v);

    printf("Getting values:\n");
    for (int i = 0; i < v->size; i++)
    {
        printf("Value at index %d: %d\n", i, vecGet(v, i));
    }

    printf("Popping all values:\n");
    vecPop(v);
    vecPrint(v);
    vecPop(v);
    vecPrint(v);
    vecPop(v);
    vecPrint(v);
    vecPop(v);
    vecPrint(v);
    
    
    vecDelete(v);

    return 0;
} 
