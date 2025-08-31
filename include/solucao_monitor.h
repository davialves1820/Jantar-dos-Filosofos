#ifndef TRABALHO_SO_SOLUCAO_MONITOR_H
#define TRABALHO_SO_SOLUCAO_MONITOR_H

#include "filosofo.h"
#include <pthread.h>

typedef  enum {PENSANDO, FAMINTO, COMENDO} estados_t;

extern pthread_mutex_t monitor_mutex;
extern pthread_cond_t condicoes[TAM];
extern estados_t estados[TAM];

void *vida_filosofo_monitor(void *arg);

void init_monitor(void);

#endif //TRABALHO_SO_SOLUCAO_MONITOR_H