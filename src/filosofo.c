#include "filosofo.h"

pthread_mutex_t garfos[TAM]; // Cada garfo e representado por um mutex

// Pega o indice do garfo da esquerda
int esquerda(int i) {
    return i;
}

// Pega o indice do garfo da direita
int direita(int i) {
    return (i+1) % TAM;
}