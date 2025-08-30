#ifndef SOLUCAO_SEMAFORO_H
#define SOLUCAO_SEMAFORO_H

#include "filosofo.h"
#include <semaphore.h>

extern sem_t garcom; // semaforo global

void *vida_filosofo_semaforo(void *arg);

void init_semaforo(void);

#endif //SOLUCAO_SEMAFORO_H