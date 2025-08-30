#include "solucao_deadlock.h"

// Funcao principal de cada thread(filosofo)
void *vida_filosofo_deadlock(void *arg) {
    int id = *(int*)arg; // ID do filosofo

    while (1) {
        printf("Filosofo %d esta pensando...\n", id);

        pthread_mutex_lock(&garfos[esquerda(id)]);
        printf("Filosofo %d pegou o garfo da esquerda\n", id);

        pthread_mutex_lock(&garfos[direita(id)]);
        printf("Filosofo %d pegou o garfo da direita e esta comendo.\n", id);

        sleep(2); // Simula tempo para comer

        // Devolve os garfos, primeiro o da direita, depois o da esquerda
        pthread_mutex_unlock(&garfos[direita(id)]);
        pthread_mutex_unlock(&garfos[esquerda(id)]);
        
        printf("Filosofo %d terminou de comer e devolveu os garfos.\n", id);
    }

    return NULL;
}

// Inicializa todos os mutexes
__attribute__((constructor)) // Para chamar essa funcao antes da main
void init_deadlock(void) {
    for (int i = 0; i < TAM; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }
}
