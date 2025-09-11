#include "solucao_monitor.h"

pthread_mutex_t monitor_mutex;
pthread_cond_t condicoes[TAM];
estados_t estados[TAM];

// Funcoes auxiliares para melhorar a legibilidade nos usos dos testes
int filosofo_esquerda(int i) {
    return (i + TAM - 1) % TAM;
}
int filosofo_direita(int i) {
    return (i + 1) % TAM;
}

// Essa funcao testa se os filosofos vizinhos estao comendo e libera o filosofo para comer caso nao estejam
// Como realiza troca de estado deve ocorrer com mutex do monitor TRANCADO
static void teste(int id) {
    if (estados[id] == FAMINTO &&
        estados[filosofo_esquerda(id)] != COMENDO &&
        estados[filosofo_direita(id)] != COMENDO) {
            estados[id] = COMENDO;
            pthread_cond_signal(&condicoes[id]);    // Sinaliza que a condiçao foi atingida e o filosofo pode comer
        }
}

void pegar_garfos(int id) {
    // Filosofo foi liberado para comer e pega seus garfos

    pthread_mutex_lock(&garfos[esquerda(id)]);
    printf("Filosofo %d pegou o garfo da esquerda\n", id);

    pthread_mutex_lock(&garfos[direita(id)]);
    printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);
}

void devolver_garfos(int id) {
    // Filosofo devolve os garfos, primeiro o da direita, depois o da esquerda
    pthread_mutex_unlock(&garfos[direita(id)]);
    pthread_mutex_unlock(&garfos[esquerda(id)]);

    printf("Filosofo %d terminou de comer e devolveu os garfos.\n", id);
}

static void faminto(int id) {
    // Inicia medicao do tempo de espera
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_mutex_lock(&monitor_mutex);
    // Trancando o monitor para fazer o acesso do estado, de modo a garantir exclusividade mutua e evitar deadlock

    estados[id] = FAMINTO;
    // printf("Filosfo MONITOR %d ficou faminto\n", id);    I/O reduz atrasa as outras threads

    teste(id);

    while(estados[id] != COMENDO) {
        // Destranca o monitor, coloca filosofo na fila e dorme, retomando quando acordado e retrancando monitor
        // Filosofo e acordado quando um de seus vizinhos termina de comer e e sua chance de comer
        bloqueios[id]++; // Incrementa o numero de bloqueios do filosofo
        pthread_cond_wait(&condicoes[id], &monitor_mutex);
    }

    pthread_mutex_unlock(&monitor_mutex);
    // Destrancando monitor para permitir que outros filosofos consigam comer
    // Sem destrancar apenas um filosofo comeria por vez
    // Devemos manter o monitor trancado apenas quando estivermos alterando estados que podem causar problemas
    // Pegar os garfos e uma açao segura visto que os filosofos vizinhos nao tentarao pega-los

    // Mede o tempo de espera para pegar os garfos
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double espera = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    tempo_espera[id] += espera;

    pegar_garfos(id);

    // Come
    sleep(2);
    // sleep deve ocorrer com o monitor destrancado para nao inibir filosofos que logicamente conseguiriam comer
    refeicoes[id]++; // Incrementa o numero de refeicoes

    // O filosofo comeu agora ira devolver os garfos, voltar a pensar e avisar seus vizinhos

    pthread_mutex_lock(&monitor_mutex);    // Para garantir segurança na alteraçao de estados novamente e trancado

    devolver_garfos(id);

    estados[id] = PENSANDO; // Filosofo esta satisfeito e volta a pensar

    // Filosofo tenta acordar seus vizinhos
    teste(filosofo_esquerda(id));
    teste(filosofo_direita(id));

    pthread_mutex_unlock(&monitor_mutex);
}

void *vida_filosofo_monitor(void *arg) {
    int id = *(int *)arg;
    
    // Inicializa métricas
    refeicoes[id] = 0;
    tempo_espera[id] = 0.0;
    bloqueios[id] = 0;
    
    time_t inicio = time(NULL);
    while (difftime(time(NULL), inicio) < TEMPO_MAXIMO) {
        printf("Filosofo MONITOR %d esta pensando...\n", id);
        sleep(1);

        faminto(id); // O Filosofo ficou faminto

    }

    return NULL;
}

void init_monitor(void){
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    pthread_t filosofos[TAM];
    int ids[TAM];

    pthread_mutex_init(&monitor_mutex, NULL);

    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
        pthread_cond_init(&condicoes[i], NULL);
    }

    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, vida_filosofo_monitor, &ids[i]);
    }

    // Espera as threads terminarem (pode ocorrer starvation)
    for (int i = 0; i < TAM; i++) {
        pthread_join(filosofos[i], NULL);
    }

    pthread_mutex_destroy(&monitor_mutex);

    for (int i = 0; i < TAM; i++) {
        pthread_cond_destroy(&condicoes[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    // Metricas para saber se ouve starvation
    double limite_espera = 3; // Em segundos
    int limite_bloqueios = 20;


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

        if (espera_media >= limite_espera || bloqueios[i] > limite_bloqueios) {
            starvation++;
            printf(" <-- Potencial starvation");
        }
        printf("\n");
    }
    

    printf("\n--- Métricas da Solução Monitor ---\n");
    printf("Tempo de execução total: %lf segundos\n", tempo);
    printf("Quantidade total de refeições: %d (média: %.2f por filósofo)\n", total_refeicoes, (double)total_refeicoes / TAM);
    printf("Tempo de espera médio por refeição: %lf segundos\n", media_espera);
    printf("Quantidade de starvation: %d\n", starvation);
    printf("Número total de bloqueios: %d\n", total_bloqueios);
}