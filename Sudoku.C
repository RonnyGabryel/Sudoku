#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int escolha = 0;
    char nome[50];
    
    printf("Digite seu nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    struct Sudoku {
        int grid[9][9];
        int fixo[9][9]; 
    };

    struct Sudoku jogo;

    int facil[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int dificil[9][9] = {
        {0, 0, 0, 0, 7, 0, 0, 9, 0},
        {0, 0, 0, 5, 0, 0, 0, 0, 2},
        {0, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 3, 0, 1, 0, 0},
        {0, 0, 0, 7, 0, 8, 0, 0, 0},
        {0, 0, 9, 0, 6, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 7, 0, 0},
        {6, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 8, 0, 0, 2, 0, 0, 0, 0}
    };

    int especialista[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {4, 0, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 2, 0, 0, 3, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 0},
        {0, 0, 0, 5, 0, 3, 0, 0, 0},
        {0, 8, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 7, 0, 0, 2, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 9},
        {0, 2, 0, 0, 0, 0, 0, 0, 0}
    };

    while (escolha != 5) {
        printf("\n- Jogo Sudoku Selecione a dificuldade -\n");
        printf("1 - Facil\n2 - Dificil\n3 - Especialista\n4 - Regras do Sudoku\n5 - Fechar o jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();

        int (*nivel)[9] = NULL;

        switch (escolha) {
            case 1:
                nivel = facil;
                break;
            case 2:
                nivel = dificil;
                break;
            case 3:
                nivel = especialista;
                break;
            case 4:
                printf("\n========== REGRAS DO SUDOKU ==========\n");
                printf("1. Preencha todas as celulas com numeros de 1 a 9 sem repetir.\n");
                printf("2. Cada linha, coluna e bloco 3x3 deve conter todos os numeros de 1 a 9.\n");
                printf("=======================================\n");
                printf("\nPressione Enter para voltar ao menu");
                getchar();
                continue;
            case 5:
                printf("\nO jogo foi fechado.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                printf("\nPressione Enter para voltar ao menu");
                getchar();
                continue;
        }

        if (nivel) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    jogo.grid[i][j] = nivel[i][j];
                    jogo.fixo[i][j] = nivel[i][j];
                }
            }

            int linha, coluna, valor;
            while (1) {
                printf("\n======= Tabuleiro Sudoku =======\n");
                for (int i = 0; i < 9; i++) {
                    if (i % 3 == 0 && i != 0) printf("---------------------\n");
                    for (int j = 0; j < 9; j++) {
                        if (j % 3 == 0 && j != 0) printf(" | ");
                        printf("%d ", jogo.grid[i][j]);
                    }
                    printf("\n");
                }
                printf("\n%s, digite a linha (1-9), coluna (1-9) e valor (1-9)0: ", nome);
                
                int valid_input = 0;
                while (!valid_input) {
                    if (scanf("%d %d %d", &linha, &coluna, &valor) != 3) {
                        printf("\nEntrada invalida! Por favor, insira três números inteiros.\n");
                        getchar(); // Limpa o buffer
                        continue;
                    }
                    
                    if (linha < 1 || linha > 9 || coluna < 1 || coluna > 9 || valor < 1 || valor > 9) {
                        printf("\nValores fora do intervalo! A linha e coluna devem ser entre 1 e 9, e o valor entre 1 e 9.\n");
                    } else {
                        valid_input = 1;
                    }
                }

                if (linha == 0 || coluna == 0 || valor == 0) break;
                if (jogo.fixo[linha-1][coluna-1] != 0) {
                    printf("\nNao pode alterar esse numero!\n");
                } else {
                    jogo.grid[linha-1][coluna-1] = valor;
                }
            }
        }

        system("clear"); // Usar "cls" no Windows
    }
    return 0;
}
