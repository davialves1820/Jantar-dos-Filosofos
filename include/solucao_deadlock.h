#ifndef SOLUCAO_DEADLOCK_H
#define SOLUCAO_DEADLOCK_H

#include "filosofo.h"

extern pthread_mutex_t garfos[TAM]; // Cada garfo e representado por um mutex

void *vida_filosofo_deadlock(void *arg); // Funcao principal

// Funcoes auxiliares
int esquerda(int i);
int direita(int i);
void init_deadlock(void);

#endif