#include "solucao_semaforo.h"

sem_t garcom; // O semáforo que regula a quantidade máxima de filósofos comendo a qualquer momento.

void *vida_filosofo_semaforo(void *arg) {
    int id = *(int*)arg; // Fazendo cast de ponteiro genérico para inteiro
    int refeicoes = 0;

    while (refeicoes < MAX_REFEICAO) {
        printf("Filosofo SEMAFARO %d esta pensando...\n", id);
        sleep(1);

        sem_wait(&garcom); // Pedindo "permissão" para o garçom de modo a garantir que há espaço para todos comerem

        // Se o filósofo recebeu permissão do garçom ele se senta e pega os garfos para comer
        pthread_mutex_lock(&garfos[esquerda(id)]);
        printf("Filosofo %d pegou o garfo da esquerda\n", id);
        pthread_mutex_lock(&garfos[direita(id)]);
        printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);

        // Come
        printf("Filosofo %d está comendo!\n", id);
        sleep(2);
        refeicoes++;

        // Devolve os garfos, primeiro o da direita, depois o da esquerda
        pthread_mutex_unlock(&garfos[direita(id)]);
        pthread_mutex_unlock(&garfos[esquerda(id)]);

        // O filósofo avisa ao garçom que terminou de comer e um espaço está livre
        sem_post(&garcom);
        printf("Filosofo %d terminou de comer, devolveu os garfos e avisou ao garcom.\n", id);

    }

    
    return NULL;
}

void init_semaforo(void) {
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    pthread_t filosofos[TAM];
    int ids[TAM];

    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    sem_init(&garcom, 0, TAM -1); 

    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, vida_filosofo_semaforo, &ids[i]);
    }

    // Espera as threads terminarem(nunca ocorre nesse caso)
    for (int i = 0; i < TAM; i++) {
        pthread_join(filosofos[i], NULL);
    }

    sem_destroy(&garcom);
    printf("Todos os filosofos comeram uma vez, fim da execucao.\n");

    printf("Todos os filosofos comeram uma vez, fim da execucao.\n");
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo: %lf\n", tempo);
}