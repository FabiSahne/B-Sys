typedef struct vec {
    int *elements;
    int size;
    int capacity;
} vec;

void vecNew(vec *v);
void vecDelete(vec *v);
void vecPush(vec *v, int value);
int vecPop(vec *v);
int vecGet(vec *v, int index);
void vecSet(vec *v, int index, int value);
void vecPrint(vec* v);
