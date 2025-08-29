#ifndef FILOSOFO_H
#define FILOSOFO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define TAM 5 // Define o numero de filosofos(threads)

void *vida_filosofo(void *arg); // Estrutura para qualquer solucao

#endif