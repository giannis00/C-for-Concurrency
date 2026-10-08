#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *data;                // a block on the heap
    int size;                    // how many elements the block has
} Vector;

// returns a zero-filled vector; data is NULL if the allocation failed
Vector vector_create(int size)
{
    Vector v;
    v.data = calloc(size, sizeof(double));
    v.size = (v.data != NULL) ? size : 0;
    return v;
}

void vector_free(Vector *v)
{
    free(v->data);
    v->data = NULL;              // the vector no longer owns a block
    v->size = 0;
}

double vector_sum(const Vector *v)
{
    double total = 0.0;
    for (int i = 0; i < v->size; i++) {
        total += v->data[i];
    }
    return total;
}

int main(void)
{
    Vector v = vector_create(5);
    if (v.data == NULL) {
        return 1;
    }

    for (int i = 0; i < v.size; i++) {
        v.data[i] = 1.5 * i;
    }
    printf("%d elements, sum %.1f\n", v.size, vector_sum(&v));

    vector_free(&v);
    return 0;
}
