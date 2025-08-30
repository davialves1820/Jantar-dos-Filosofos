#include "solucao_deadlock.h"
#include "solucao_semaforo.h"

int main(void) {

    pthread_t threads[TAM];
    int ids[TAM];

    // Criacao das threads (Filosofos)
    for (int i = 0; i < TAM; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, vida_filosofo_semaforo, &ids[i]);
    }

    // Avisa no terminal quando ocorrer o deadlock
    //sleep(10);
    //printf("Se voce esta vendo esta mensagem e nada mais aconteceu, provavelmente houve um deadlock.\n");

    // Espera as threads terminarem(nunca ocorre nesse caso)
    for (int i = 0; i < TAM; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("SEMAFARO TERMINOU A EXECUCAO\n");
    
    return 0;
}