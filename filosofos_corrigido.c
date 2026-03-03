#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int N;
pthread_mutex_t *forks;
pthread_t *philosophers;
int *ids;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Filósofo %d está pensando...\n", id);
        usleep(rand() % 500);

        // ESTRATÉGIA: Filósofos pares pegam Esquerda -> Direita
        // Filósofos ímpares pegam Direita -> Esquerda (Inversão de recurso)
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        printf("Filósofo %d está COMENDO usando garfos %d e %d\n", id, left, right);
        usleep(rand() % 500); // Simula o tempo comendo

        // Liberação
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
        
        printf("Filósofo %d terminou de comer e soltou os garfos.\n", id);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero_de_filosofos>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    if (N < 2) return 1;

    forks = malloc(N * sizeof(pthread_mutex_t));
    philosophers = malloc(N * sizeof(pthread_t));
    ids = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
