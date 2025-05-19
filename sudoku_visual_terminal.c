//Ronny Gabryel Colatino de Souza
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

int jogada_valida(int grid[9][9], int linha, int coluna, int valor) {
    for (int i = 0; i < 9; i++) {
        if (grid[linha][i] == valor || grid[i][coluna] == valor)
            return 0;
    }
    int bi = (linha / 3) * 3, bj = (coluna / 3) * 3;
    for (int i = bi; i < bi + 3; i++) {
        for (int j = bj; j < bj + 3; j++) {
            if (grid[i][j] == valor)
                return 0;
        }
    }
    return 1;
}

void desenhar_tabuleiro(int grid[9][9]) {
    clear();
    box(stdscr, 0, 0);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int y = 1 + i * 2;
            int x = 2 + j * 4;
            mvprintw(y, x, "%d", grid[i][j]);
        }
        if (i % 3 == 2 && i != 8) {
            int y = 1 + i * 2 + 1;
            mvhline(y, 1, ACS_HLINE, 9 * 4 - 1);
        }
    }
    for (int k = 1; k <= 2; k++) {
        int x = k * 3 * 4 + 1;
        mvvline(1, x, ACS_VLINE, 9 * 2 - 1);
    }

    refresh();
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int escolha = 0;
    char nome[50];

    mvprintw(2, 2, "Digite seu nome: ");
    refresh();
    echo();
    mvgetnstr(2, 20, nome, 49);
    noecho();

    struct Sudoku {
        int grid[9][9];
        int fixo[9][9];
    } jogo;

    int facil[9][9] = {
        {4, 0, 0, 0, 0, 0, 9, 6, 0},
        {7, 0, 3, 4, 0, 0, 0, 0, 5},
        {0, 2, 0, 0, 0, 1, 0, 0, 4},
        {0, 0, 0, 8, 3, 0, 4, 0, 6},
        {0, 9, 6, 0, 0, 3, 0, 1, 0},
        {0, 0, 4, 1, 0, 6, 7, 5, 3},
        {0, 7, 2, 9, 8, 0, 5, 0, 0},
        {8, 0, 1, 0, 0, 7, 0, 4, 0},
        {5, 0, 0, 0, 1, 3, 8, 2, 7}
    };

    int dificil[9][9] = {
        {0, 0, 8, 9, 1, 0, 4, 0, 7},
        {0, 0, 0, 0, 0, 7, 0, 0, 5},
        {1, 0, 7, 2, 5, 4, 0, 0, 0},
        {4, 7, 0, 0, 9, 0, 2, 5, 6},
        {8, 0, 0, 0, 2, 8, 0, 0, 9},
        {0, 2, 0, 0, 0, 5, 8, 0, 1},
        {6, 0, 5, 0, 7, 0, 1, 3, 2},
        {0, 1, 9, 5, 3, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 5, 9, 0}
    };

    int especialista[9][9] = {
        {0, 6, 2, 5, 0, 0, 0, 0, 0},
        {7, 5, 0, 0, 0, 0, 1, 2, 0},
        {0, 0, 0, 2, 4, 0, 0, 7, 5},
        {5, 4, 7, 0, 0, 0, 3, 8, 6},
        {6, 0, 0, 0, 8, 3, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 0, 0, 6, 0, 4, 5, 0},
        {0, 0, 0, 8, 0, 0, 0, 1, 0},
        {2, 0, 5, 3, 0, 0, 8, 0, 9}
    };

    while (escolha != 5) {
        clear();
        box(stdscr, 0, 0);
        mvprintw(2, 2, "- Jogo Sudoku - Selecione a dificuldade -");
        mvprintw(4, 4, "1 - Facil");
        mvprintw(5, 4, "2 - Dificil");
        mvprintw(6, 4, "3 - Especialista");
        mvprintw(7, 4, "4 - Regras do Sudoku");
        mvprintw(8, 4, "5 - Fechar o jogo");
        mvprintw(10, 2, "Escolha uma opcao: ");
        refresh();
        scanw("%d", &escolha);

        int (*nivel)[9] = NULL;
        switch (escolha) {
            case 1: nivel = facil; break;
            case 2: nivel = dificil; break;
            case 3: nivel = especialista; break;
            case 4:
                clear();
                box(stdscr, 0, 0);
                mvprintw(2, 2, "========== REGRAS DO SUDOKU ==========");
                mvprintw(4, 4, "1. Preencha todas as celulas com numeros de 1 a 9 sem repetir.");
                mvprintw(5, 4, "2. Cada linha, coluna e bloco 3x3 deve conter todos os numeros.");
                mvprintw(7, 2, "Pressione qualquer tecla para voltar...");
                refresh();
                getch();
                continue;
            case 5:
                clear();
                box(stdscr, 0, 0);
                mvprintw(2, 2, "O jogo foi fechado. Ate mais!");
                refresh();
                getch();
                break;
            default:
                mvprintw(12, 2, "Opcao invalida! Pressione qualquer tecla...");
                refresh();
                getch();
                continue;
        }

        if (nivel) {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) {
                    jogo.grid[i][j] = nivel[i][j];
                    jogo.fixo[i][j] = nivel[i][j];
                }

            int linha, coluna, valor;
            while (1) {
                desenhar_tabuleiro(jogo.grid);

                mvprintw(20, 2, "%s, digite linha (1-9) ou 0 sair: ", nome);
                refresh(); scanw("%d", &linha);
                if (linha == 0) break;

                mvprintw(21, 2, "Digite coluna (1-9) ou 0 sair:      ");
                refresh(); scanw("%d", &coluna);
                if (coluna == 0) break;

                mvprintw(22, 2, "Digite valor (1-9) ou 0 sair:       ");
                refresh(); scanw("%d", &valor);
                if (valor == 0) break;

                if (linha<1||linha>9||coluna<1||coluna>9||valor<1||valor>9) {
                    mvprintw(24, 2, "Fora do intervalo! tecla para continuar...");
                    getch(); continue;
                }
                if (jogo.fixo[linha-1][coluna-1]!=0) {
                    mvprintw(24, 2, "Posicao fixa! tecla para continuar...");
                    getch(); continue;
                }
                if (!jogada_valida(jogo.grid, linha-1, coluna-1, valor)) {
                    mvprintw(24, 2, "Jogada invalida! tecla para continuar...");
                    getch(); continue;
                }

                jogo.grid[linha-1][coluna-1] = valor;

                int cheio = 1;
                for (int i = 0; i < 9 && cheio; i++)
                    for (int j = 0; j < 9; j++)
                        if (jogo.grid[i][j] == 0) { cheio = 0; break; }
                if (cheio) {
                    desenhar_tabuleiro(jogo.grid);
                    mvprintw(24, 2, "Parabens, %s! Sudoku completo.", nome);
                    mvprintw(25, 2, "Pressione qualquer tecla...");
                    getch();
                    break;
                }
            }
        }
    }

    endwin();
    return 0;
}
