#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 4

void vecNew(vec *v) {
    v->capacity = DEFAULT_CAPACITY;
    v->size = 0;
    v->elements = calloc(DEFAULT_CAPACITY, sizeof(int));
}

void vecDelete(vec *v) {
    v->capacity = 0;
    v->size = 0;
    free(v->elements);
}

void vecPush(vec *v, int value) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->elements = reallocarray(v->elements, v->capacity, sizeof(int));
    }
    v->elements[v->size++] = value;
}

int vecPop(vec *v) {
    if (v->size == 0) {
        return NULL;
    } else {
        return v->elements[--v->size];
    }
}

int vecGet(vec *v, int index) {
    if (index < 0 || index >= v->size) {
        return NULL;
    } else {
        return v->elements[index];
    }
}

void vecSet(vec *v, int index, int value) {
    if (index >= 0 && index < v->size) {
        v->elements[index] = value;
    }
}

void vecPrint(vec *v) {
    printf("Vector: { Size: %d, Capacity: %d, Elements: { ", v->size, v->capacity);
    for (int i = 0; i < v->size; i++) {
        printf("%d ", v->elements[i]);
    }
    printf(" }\n");
}
