#ifndef SOLUCAO_SEMAFORO_CONTROLE_H
#define SOLUCAO_SEMAFORO_CONTROLE_H

#include "filosofo.h"
#include <semaphore.h>

extern sem_t garcom_controle; // semaforo global

void *vida_filosofo_semaforo_controle(void *arg);

void init_semaforo_controle(void);

#endif //SOLUCAO_SEMAFORO_CONTROLE_H