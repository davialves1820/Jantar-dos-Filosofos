#ifndef FILOSOFO_H
#define FILOSOFO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define TAM 5 // Define o numero de filosofos(threads)
#define MAX_REFEICAO 2

extern pthread_mutex_t garfos[TAM]; // Cada garfo e representado por um mutex

void *vida_filosofo(void *arg); // Estrutura para qualquer solucao

// Funcoes auxiliares
int esquerda(int i);
int direita(int i);

#endif //FILOSOFO_H