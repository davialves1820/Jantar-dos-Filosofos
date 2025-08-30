#ifndef SOLUCAO_SEMAFORO_H
#define SOLUCAO_SEMAFORO_H

#include "filosofo.h"
#include <semaphore.h>

extern pthread_mutex_t garfos[TAM]; // Cada garfo e representado por um mutex
extern sem_t garcom;                // semaforo global

void *vida_filosofo_semaforo(void *arg);

// Funcoes auxiliares
int esquerda(int i);
int direita(int i);
void init_semaforo(void);

#endif //SOLUCAO_SEMAFORO_H