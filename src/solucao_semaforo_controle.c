#include "solucao_semaforo_controle.h"

// Garçom: semáforo que regula a quantidade máxima 
// de filósofos comendo a qualquer momento.
sem_t garcom_controle;

void *vida_filosofo_semaforo_controle(void *arg) {
    int id = *(int*)arg; // Fazendo cast de ponteiro genérico para inteiro

    // Inicializa métricas para cada filósofo
    refeicoes[id] = 0;
    tempo_espera[id] = 0.0;
    bloqueios[id] = 0;

    time_t inicio = time(NULL);
    while (difftime(time(NULL), inicio) < TEMPO_MAXIMO) {
        printf("Filosofo SEMAFORO_CONTROLE %d esta pensando...\n", id);
        sleep(1);

        // -- Seção Crítica--
        // Inicia medição do tempo de espera.
        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);

        int val;
        sem_getvalue(&garcom_controle, &val);
        if (val == 0) bloqueios[id]++;
        sem_wait(&garcom_controle); // Pedindo "permissão" para o garçom de modo a garantir que há espaço para todos comerem

        // Pegar garfos com ordem diferente para ímpares (quebra ciclo para evitar deadlock e starvation)
        // Os mutexes garantem que os garfos são recursos exclusivos.
        if (id % 2 == 0) {
            pthread_mutex_lock(&garfos[esquerda(id)]);
            printf("Filosofo %d pegou o garfo da esquerda\n", id);
            pthread_mutex_lock(&garfos[direita(id)]);
            printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);
        } else {
            pthread_mutex_lock(&garfos[direita(id)]);
            printf("Filosofo %d pegou o garfo da direita\n", id);
            pthread_mutex_lock(&garfos[esquerda(id)]);
            printf("Filosofo %d pegou o garfo da esquerda e esta comendo.\n", id);
        }

        // Mede o tempo total de espera para pegar os garfos
        struct timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);
        double espera = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        tempo_espera[id] += espera;

        // Come
        int tempo_comendo = (rand() % 5) + 1; // Aleatório entre 1 e 5 segundos
        sleep(tempo_comendo);
        refeicoes[id]++ ; // Incrementa o numero de refeicoes

        // -- Fim da Seção Crítica --

        // Devolve os garfos na ordem inversa
        if (id % 2 == 0) {
            pthread_mutex_unlock(&garfos[direita(id)]);
            pthread_mutex_unlock(&garfos[esquerda(id)]);
        } else {
            pthread_mutex_unlock(&garfos[esquerda(id)]);
            pthread_mutex_unlock(&garfos[direita(id)]);
        }

        // O filósofo avisa ao garçom que terminou de comer e um espaço está livre
        sem_post(&garcom_controle);
        printf("Filosofo %d terminou de comer e devolveu os garfos.\n", id);

    }

    return NULL;

}

void init_semaforo_controle(void) {
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    pthread_t filosofos[TAM];
    int ids[TAM];

    // Inicializa os mutexes que representam os garfos.
    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    // Inicializa o semáforo do garçom com valor TAM-1
    // Garante pelo menos um garfo livre -> quebra espera circular.
    sem_init(&garcom_controle, 0, TAM - 1); 

    // Cria as threads (filósofos)
    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, vida_filosofo_semaforo_controle, &ids[i]);
    }

    // Espera todas as threads finalizarem.
    for (int i = 0; i < TAM; i++) {
        pthread_join(filosofos[i], NULL);
    }

    // Destroi o semáforo do garçom
    sem_destroy(&garcom_controle); 

    // Calcula o tempo total de execução
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Metrica para saber se houve starvation
    double limite_espera = 3; // Em segundos

    // Calculo e exibicao das metricas
    double media_espera = 0.0;
    int total_refeicoes = 0;
    int total_bloqueios = 0;
    int starvation = 0;

    printf("\n--- Relatório Individual dos Filósofos ---\n");
    for (int i = 0; i < TAM; i++) {
        double espera_media = tempo_espera[i] / (refeicoes[i] > 0 ? refeicoes[i] : 1);
        media_espera += espera_media / TAM;
        total_refeicoes += refeicoes[i];
        total_bloqueios += bloqueios[i];

        printf("Filosofo %d: Refeições = %d, Espera média = %.2lf s, Bloqueios = %d", i, refeicoes[i], espera_media, bloqueios[i]);

        if (espera_media >= limite_espera) {
            starvation++;
            printf(" <-- Potencial starvation");
        }
        printf("\n");
    }
    
    // Exibe as métricas
    printf("\n--- Métricas da Solução Semáforo com Controle ---\n");
    printf("Tempo de execução total: %lf segundos\n", tempo);
    printf("Quantidade total de refeições: %d (média: %.2f por filósofo)\n", total_refeicoes, (double)total_refeicoes / TAM);
    printf("Tempo de espera médio por refeição: %lf segundos\n", media_espera);
    printf("Quantidade de starvation: %d\n", starvation);
    printf("Número total de bloqueios: %d\n", total_bloqueios);
}