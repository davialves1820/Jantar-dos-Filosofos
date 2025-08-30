#include "solucao_semaforo.h"

pthread_mutex_t garfos[TAM]; // Cada garfo e representado por um mutex

sem_t garcom; // O semáforo que regula a quantidade máxima de filósofos comendo a qualquer momento.

// Pega o indice do garfo da esquerda
int esquerda(int i) {
    return i;
}

// Pega o indice do garfo da direita
int direita(int i) {
    return (i+1) % TAM;
}

void *vida_filosofo_semaforo(void *arg) {
    int id = *(int*)arg; // Fazendo cast de ponteiro genérico para inteiro

    printf("Filosofo SEMAFARO %d esta pensando...\n", id);
    //sleep(2);

    sem_wait(&garcom); // Pedindo "permissão" para o garçom de modo a garantir que há espaço para todos comerem

    // Se o filósofo recebeu permissão do garçom ele se senta e pega os garfos para comer
    pthread_mutex_lock(&garfos[esquerda(id)]);
    printf("Filosofo SEMAFARO %d pegou o garfo da esquerda\n", id);
    pthread_mutex_lock(&garfos[direita(id)]);
    printf("Filosofo SEMAFARO %d pegou o garfo da direita e esta comendo.\n", id);

    // Come
    printf("Filosofo SEMAFARO %d está comendo!\n", id);
    sleep(2);

    // Devolve os garfos, primeiro o da direita, depois o da esquerda
    pthread_mutex_unlock(&garfos[direita(id)]);
    pthread_mutex_unlock(&garfos[esquerda(id)]);

    // O filósofo avisa ao garçom que terminou de comer e um espaço está livre
    sem_post(&garcom);
    printf("Filosofo SEMAFARO %d terminou de comer, devolveu os garfos e avisou ao garcom.\n", id);

    return NULL;
}

__attribute__((constructor)) // Para chamar essa funcao antes da main
void init_semaforo(void) {
    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    sem_init(&garcom, 0, TAM - 1);

}