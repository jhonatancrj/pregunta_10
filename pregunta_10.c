#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 4  // Número de procesadores
#define N 10 // Número de términos en la serie

typedef struct {
    int start;
    int step;
    int *result;
} ThreadData;

void *generate_series(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start = data->start;
    int step = data->step;
    int *result = data->result;
    
    for (int i = 0; i < N; i++) {
        result[i] = start + i * step;
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[M];
    ThreadData thread_data[M];
    int results[M][N];

    for (int i = 0; i < M; i++) {
        thread_data[i].start = 2 * i + 2; // Comienza con 2, 4, 6, 8...
        thread_data[i].step = M * 2;
        thread_data[i].result = results[i];
        pthread_create(&threads[i], NULL, generate_series, (void *)&thread_data[i]);
    }

    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("La serie generada en M vectores es:\n");
    for (int i = 0; i < M; i++) {
        printf("Procesador %d: ", i);
        for (int j = 0; j < N; j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }

    return 0;
}
