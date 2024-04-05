#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 4

typedef struct vec {
    int capacity;
    int size;
    int *ptr;
} vec;

vec new() {
    vec ret = {DEFAULT_CAPACITY, 0, calloc(DEFAULT_CAPACITY, sizeof(int))};
    return ret;
}

vec push(vec self, int i) {
    if (self.size == self.capacity) {
        self.capacity *= 2;
        self.ptr = reallocarray(self.ptr, self.capacity, sizeof(int));
    }
    self.ptr[self.size++] = i;
    return self;
}

vec pop(vec self) {
    if (self.size == 0) {
        return self;
    } else {
        if (self.size <= self.capacity / 4) {
            self.capacity /= 2;
            self.ptr = reallocarray(self.ptr, self.capacity, sizeof(int));
        }
        self.size--;
        return self;
    }
}

int getn(vec self, int i) {
    if (i < 0 || i >= self.size) {
        return NULL;
    } else {
        return self.ptr[i];
    }
}

void printvec(vec self) {
    printf("Vector: Size: %d, Capacity: %d, Values: {", self.size, self.capacity);
    for (int i = 0; i < self.size; i++) {
        printf("%d ", self.ptr[i]);
    }
    printf("}\n");
}

void delete(vec self) {
    free(self.ptr);
}

int main() {

    printf("New Vector:\n");
    vec v = new();
    printvec(v);

    printf("Pushing values:\n");
    v = push(v, 1);
    printvec(v);
    v = push(v, 2);
    printvec(v);
    v = push(v, 3);
    printvec(v);
    v = push(v, 4);
    printvec(v);
    printf("`realloc` should happen here:\n");
    v = push(v, 5);
    printvec(v);
    v = push(v, 6);
    printvec(v);
    v = push(v, 7);
    printvec(v);
    v = push(v, 8);
    printvec(v);

    printf("Popping values:\n");
    v = pop(v);
    printvec(v);
    v = pop(v);
    printvec(v);
    v = pop(v);
    printvec(v);

    printf("Getting values:\n");
    for (size_t i = 0; i < v.size; i++)
    {
        printf("Value at index %d: %d\n", i, getn(v, i));
    }

    printf("Popping all values:\n");
    v = pop(v);
    printvec(v);
    v = pop(v);
    printvec(v);
    v = pop(v);
    printvec(v);
    v = pop(v);
    printvec(v);
    
    
    delete(v);

    return 0;
} 
