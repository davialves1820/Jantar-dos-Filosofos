#include "solucao_deadlock.h"
#include "solucao_semaforo.h"
#include "solucao_monitor.h"

int main(void) {

    int escolha;

    printf("1- DEADLOCK\n");
    printf("2- MONITOR\n");
    printf("2- SEMAFORO\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            init_deadlock();
            break;

        case 2:
            init_monitor();
            break;

        case 3:
            init_semaforo();
            break;

        default:
            printf("Opcao invalida\n");
    }

    return 0;
}