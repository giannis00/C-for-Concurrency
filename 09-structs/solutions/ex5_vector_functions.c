#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *data;
    int size;
} Vector;

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
    v->data = NULL;
    v->size = 0;
}

void vector_fill(Vector *v, double value)
{
    for (int i = 0; i < v->size; i++) {
        v->data[i] = value;
    }
}

double vector_dot(const Vector *a, const Vector *b)
{
    if (a->size != b->size) {
        return 0.0;
    }
    double dot = 0.0;
    for (int i = 0; i < a->size; i++) {
        dot += a->data[i] * b->data[i];
    }
    return dot;
}

int main(void)
{
    Vector a = vector_create(4);
    Vector b = vector_create(4);
    if (a.data == NULL || b.data == NULL) {
        vector_free(&a);
        vector_free(&b);
        return 1;
    }

    vector_fill(&a, 3.0);
    vector_fill(&b, 0.5);
    printf("Dot product: %.1f\n", vector_dot(&a, &b));

    vector_free(&a);
    vector_free(&b);
    return 0;
}
