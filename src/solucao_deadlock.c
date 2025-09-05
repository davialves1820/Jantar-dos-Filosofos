#include "solucao_deadlock.h"

// Funcao principal de cada thread(filosofo)
void *vida_filosofo_deadlock(void *arg) {
    int id = *(int*)arg; // ID do filosofo

    // Inicializa metricas
    refeicoes[id] = 0; // Inicializa o numero de refeicoes
    tempo_espera[id] = 0.0; // Inicializa o tempo de espera

    while (refeicoes[id] < MAX_REFEICAO) {
        printf("Filosofo DEADLOCK %d esta pensando...\n", id);

        sleep(1);

        // Inicia medicao do tempo de espera
        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);

        pthread_mutex_lock(&garfos[esquerda(id)]);
        printf("Filosofo %d pegou o garfo da esquerda\n", id);

        sleep(1); // Pequena pausa para aumentar a chance de deadlock

        pthread_mutex_lock(&garfos[direita(id)]);
        printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);

        // Mede o tempo de espera para pegar os garfos
        struct timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);
        double espera = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        tempo_espera[id] += espera;

        sleep(2); // Simula tempo para comer
        refeicoes[id]++ ; // Incrementa o numero de refeicoes

        // Devolve os garfos, primeiro o da direita, depois o da esquerda
        pthread_mutex_unlock(&garfos[direita(id)]);
        pthread_mutex_unlock(&garfos[esquerda(id)]);
        
        printf("Filosofo %d terminou de comer e  os garfos.\n", id);
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

    // Calculo e exibicao das metricas
    double media_espera = 0.0;
    int total_refeicoes = 0;
    int starvation = 0;

    for (int i = 0; i < TAM; i++) {
        media_espera += tempo_espera[i] / TAM;
        total_refeicoes += refeicoes[i];
        if (refeicoes[i] < MAX_REFEICAO) {
            starvation++;
        }
    }
    media_espera /= total_refeicoes > 0 ? total_refeicoes : 1;
    
    printf("\n--- Métricas da Solução Deadlock ---\n");
    printf("Tempo de execução total: %lf segundos\n", tempo);
    printf("Quantidade total de refeições: %d (média: %.2f por filósofo)\n", total_refeicoes, (double)total_refeicoes / TAM);
    printf("Tempo de espera médio por refeição: %lf segundos\n", media_espera);
    printf("Quantidade de starvation (filósofos que não comeram %d vezes): %d\n", MAX_REFEICAO, starvation);
}
