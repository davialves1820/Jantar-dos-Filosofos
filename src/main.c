#include "solucao_deadlock.h"
#include "solucao_semaforo.h"

int main(void) {

    int escolha;

    printf("1- DEADLOCK\n");
    printf("2- SEMAFARO\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        init_deadlock();
    } else if (escolha == 2) {
        init_semaforo();
    } else {
        printf("Opcao invalida\n");
    }

    return 0;
}