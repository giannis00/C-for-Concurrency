#include <stdio.h>

#define N 10
#define WORKERS 4

typedef struct {
    const double *data;   // where this worker's part begins
    int count;            // how many elements it has
    double result;        // filled in by the worker
} Task;

void run_task(Task *t)
{
    t->result = 0.0;
    for (int i = 0; i < t->count; i++) {
        t->result += t->data[i];
    }
}

int main(void)
{
    double values[N];
    for (int i = 0; i < N; i++) {
        values[i] = i + 1;
    }

    Task tasks[WORKERS];
    int chunk = N / WORKERS;

    for (int w = 0; w < WORKERS; w++) {          // 1. describe the jobs
        int start = w * chunk;
        tasks[w].data  = values + start;
        tasks[w].count = (w == WORKERS - 1) ? N - start : chunk;
    }

    for (int w = 0; w < WORKERS; w++) {          // 2. do the jobs
        run_task(&tasks[w]);
    }

    double total = 0.0;
    for (int w = 0; w < WORKERS; w++) {          // 3. collect the results
        printf("Worker %d: %d elements, sum %.0f\n",
               w, tasks[w].count, tasks[w].result);
        total += tasks[w].result;
    }
    printf("Total: %.0f\n", total);
    return 0;
}
