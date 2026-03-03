#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Variáveis globais para os recursos
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
        
        // Simula o tempo de pensamento
        usleep(rand() % 500);

        // Tenta pegar o garfo da ESQUERDA
        printf("Filósofo %d tentando pegar garfo ESQUERDO (%d)...\n", id, left);
        pthread_mutex_lock(&forks[left]);
        printf("Filósofo %d pegou o garfo ESQUERDO (%d)\n", id, left);

        // ATRASO PROPOSITAL: Garante que todos peguem o primeiro garfo antes de tentarem o segundo.
        // Isso força o deadlock de forma consistente.
        usleep(10000); 

        // Tenta pegar o garfo da DIREITA
        printf("Filósofo %d tentando pegar garfo DIREITO (%d)...\n", id, right);
        pthread_mutex_lock(&forks[right]); // O deadlock acontece aqui
        
        printf("Filósofo %d pegou o garfo DIREITO (%d) e está COMENDO\n", id, right);

        // Libera os garfos
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero_de_filosofos>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    if (N < 2) {
        printf("O número de filósofos deve ser pelo menos 2.\n");
        return 1;
    }

    // Alocação dinâmica conforme sugerido no rascunho
    forks = malloc(N * sizeof(pthread_mutex_t));
    philosophers = malloc(N * sizeof(pthread_t));
    ids = malloc(N * sizeof(int));

    // Inicializa os mutexes (garfos)
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Cria as threads dos filósofos
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Espera as threads (o programa travará em deadlock antes disso)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Limpeza (boa prática, embora o deadlock impeça de chegar aqui)
    free(forks);
    free(philosophers);
    free(ids);

    return 0;
}
