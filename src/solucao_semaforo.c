#include "solucao_semaforo.h"

sem_t garcom; // O semáforo que regula a quantidade máxima de filósofos comendo a qualquer momento.

void *vida_filosofo_semaforo(void *arg) {
    int id = *(int*)arg; // Fazendo cast de ponteiro genérico para inteiro

    // Inicializa métricas
    refeicoes[id] = 0;
    tempo_espera[id] = 0.0;
    bloqueios[id] = 0;

    while (refeicoes[id] < MAX_REFEICAO) {
        printf("Filosofo SEMAFORO %d esta pensando...\n", id);
        sleep(1);

        // Inicia medicao do tempo de espera
        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);

        int val;
        sem_getvalue(&garcom, &val);
        if (val == 0) bloqueios[id]++;
        sem_wait(&garcom); // Pedindo "permissão" para o garçom de modo a garantir que há espaço para todos comerem

        // Se o filósofo recebeu permissão do garçom ele se senta e pega os garfos para comer
        pthread_mutex_lock(&garfos[esquerda(id)]);
        printf("Filosofo %d pegou o garfo da esquerda\n", id);
        pthread_mutex_lock(&garfos[direita(id)]);
        printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);

        // Mede o tempo de espera para pegar os garfos
        struct timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);
        double espera = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        tempo_espera[id] += espera;

        // Come
        sleep(2);
        refeicoes[id]++ ; // Incrementa o numero de refeicoes

        // Devolve os garfos, primeiro o da direita, depois o da esquerda
        pthread_mutex_unlock(&garfos[direita(id)]);
        pthread_mutex_unlock(&garfos[esquerda(id)]);

        // O filósofo avisa ao garçom que terminou de comer e um espaço está livre
        sem_post(&garcom);
        printf("Filosofo %d terminou de comer e devolveu os garfos.\n", id);

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

    sem_init(&garcom, 0, TAM -1); // Garantindo que no maximo TAM - 1 filosofos tentem comer ao mesmo tempo evitamos a espera circular

    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, vida_filosofo_semaforo, &ids[i]);
    }

    // Espera todas as threads finalizarem
    for (int i = 0; i < TAM; i++) {
        pthread_join(filosofos[i], NULL);
    }

    sem_destroy(&garcom);
   
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Calculo e exibicao das metricas
    double media_espera = 0.0;
    int total_refeicoes = 0;
    int total_bloqueios = 0;
    int starvation = 0;

    for (int i = 0; i < TAM; i++) {
        media_espera += tempo_espera[i] / TAM;
        total_refeicoes += refeicoes[i];
        total_bloqueios += bloqueios[i];
        if (refeicoes[i] < MAX_REFEICAO) {
            starvation++;
        }
    }
    media_espera /= total_refeicoes > 0 ? total_refeicoes : 1;
    
    printf("\n--- Métricas da Solução Semáforo ---\n");
    printf("Tempo de execução total: %lf segundos\n", tempo);
    printf("Quantidade total de refeições: %d (média: %.2f por filósofo)\n", total_refeicoes, (double)total_refeicoes / TAM);
    printf("Tempo de espera médio por refeição: %lf segundos\n", media_espera);
    printf("Quantidade de starvation (filósofos que não comeram %d vezes): %d\n", MAX_REFEICAO, starvation);
    printf("Número total de bloqueios: %d\n", total_bloqueios);

    printf("Todos os filosofos comeram %d vezes, fim da execucao.\n", MAX_REFEICAO);
}