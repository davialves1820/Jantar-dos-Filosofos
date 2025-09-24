#include "solucao_deadlock.h"
#include "solucao_semaforo.h"
#include "solucao_monitor.h"
#include "solucao_semaforo_controle.h"
#include <stdio.h>

// Definições globais para métricas (definidas aqui para evitar múltiplas definições)
int refeicoes[TAM] = {0};
double tempo_espera[TAM] = {0.0};
int bloqueios[TAM] = {0};

int main(void) {

    int escolha;
    
    do {
        printf("\n");
        printf("   .-.  .--.  .-. .-. .---.  .--.  .----.    .----.  .----.  .----.   .----..-..-.    .----.  .----. .----. .----..----.  .----.\n");
        printf(".-.| | / {} \\ |  `| |{_   _}/ {} \\ | {}  }   | {}  \\/  {}  \\{ {__     | {_  | || |   /  {}  \\{ {__  /  {}  \\| {_ /  {}  \\{ {__  \n");
        printf("| {} |/  /\\  \\| |\\  |  | | /  /\\  \\| .-. \\   |     /\\      /.-._} }   | |   | || `--.\\      /.-._} }\\      /| |  \\      /.-._} }\n");
        printf("`----'`-'  `-'`-' `-'  `-' `-'  `-'`-' `-'   `----'  `----' `----'    `-'   `-'`----' `----' `----'  `----' `-'   `----' `----'\n");
        printf("\n");
        printf("========================================\n");
        printf("  1 - Deadlock\n");
        printf("  2 - Monitor\n");
        printf("  3 - Semáforo\n");
        printf("  4 - Semáforo com Controle\n");
        printf("  0 - Sair\n");
        printf("========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                init_deadlock();
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n'); // Limpa buffer
                getchar();
                break;

            case 2:
                init_monitor();
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n');
                getchar();
                break;

            case 3:
                init_semaforo();
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n');
                getchar();
                break;

            case 4:
                init_semaforo_controle();
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n');
                getchar();
                break;

            case 0:
                printf("\nTchau :)\n");
                break;
            
            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n');
                getchar();
        }
    } while (escolha != 0);
    

    return 0;
}