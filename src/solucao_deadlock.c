#include "solucao_deadlock.h"

// Funcao principal de cada thread(filosofo)
void *vida_filosofo_deadlock(void *arg) {
    int id = *(int*)arg; // ID do filosofo
    int refeicoes = 0;

    while (refeicoes < MAX_REFEICAO) {
        printf("Filosofo DEADLOCK %d esta pensando...\n", id);

        sleep(1);

        pthread_mutex_lock(&garfos[esquerda(id)]);
        printf("Filosofo %d pegou o garfo da esquerda\n", id);

        pthread_mutex_lock(&garfos[direita(id)]);
        printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);

        sleep(2); // Simula tempo para comer
        refeicoes++;

        // Devolve os garfos, primeiro o da direita, depois o da esquerda
        pthread_mutex_unlock(&garfos[direita(id)]);
        pthread_mutex_unlock(&garfos[esquerda(id)]);
        
        printf("Filosofo %d terminou de comer e devolveu os garfos.\n", id);
    }

    return NULL;
}

void init_deadlock(void) {
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    pthread_t filosofos[TAM];
    int ids[TAM];

    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, vida_filosofo_deadlock, &ids[i]);
    }

    // Espera as threads terminarem(nunca ocorre nesse caso)
    for (int i = 0; i < TAM; i++) {
        pthread_join(filosofos[i], NULL);
    }

    printf("Todos os filosofos comeram uma vez, fim da execucao.\n");
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo: %lf\n", tempo);
}
