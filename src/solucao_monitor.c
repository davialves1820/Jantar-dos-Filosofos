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

static void faminto(int id, int *refeicoes) {
    pthread_mutex_lock(&monitor_mutex);
    // Trancando o monitor para fazer o acesso do estado, de modo a garantir exclusividade mutua e evitar deadlock

    estados[id] = FAMINTO;
    // printf("Filosfo MONITOR %d ficou faminto\n", id);    I/O reduz atrasa as outras threads

    teste(id);

    while(estados[id] != COMENDO) {
        // Destranca o monitor, coloca filosofo na fila e dorme, retomando quando acordado e retrancando monitor
        // Filosofo e acordado quando um de seus vizinhos termina de comer e e sua chance de comer
        pthread_cond_wait(&condicoes[id], &monitor_mutex);
    }

    pthread_mutex_unlock(&monitor_mutex);
    // Destrancando monitor para permitir que outros filosofos consigam comer
    // Sem destrancar apenas um filosofo comeria por vez
    // Devemos manter o monitor trancado apenas quando estivermos alterando estados que podem causar problemas
    // Pegar os garfos e uma açao segura visto que os filosofos vizinhos nao tentarao pega-los

    pegar_garfos(id);

    // Come
    printf("Filosofo %d está comendo!\n", id);
    sleep(2);
    // sleep deve ocorrer com o monitor destrancado para nao inibir filosofos que logicamente conseguiriam comer
    (*refeicoes)++;

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
    int refeicoes = 0;

    while (refeicoes < MAX_REFEICAO) {
        printf("Filosofo MONITOR %d esta pensando...\n", id);
        sleep(1);

        faminto(id, &refeicoes); // O Filosofo ficou faminto

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
    printf("Tempo: %lf\n", tempo);
}

