#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <math.h>
#include <stdio.h>


#define LARGURA_TELA 400
#define ALTURA_TELA 400
#define TAMANHO_CELULA 50

SDL_Window *janela;
SDL_Renderer *renderizador;

int tabuleiro[8][8] = {
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 2, 0, 2, 0, 2, 0},
    {0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0}
};

int jogador_atual = 1;
int captura_na_ultima_jogada = 0;


void desenhar_circulo(int x, int y, int raio);
void desenhar_circulo_dama(int x, int y, int raio, SDL_Color cor);
void desenhar_tabuleiro();
int pode_mover(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino);
void realizar_movimento(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino);
void verificar_promocao(int linha, int coluna);
void realizar_captura(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino);
void verificar_captura_obrigatoria(int linha, int coluna);
int pode_capturar(int linha, int coluna);
int verificar_vitoria();

void lidar_com_clique(int x, int y) {
    int linha = y / TAMANHO_CELULA;
    int coluna = x / TAMANHO_CELULA;



    if (linha >= 0 && linha < 8 && coluna >= 0 && coluna < 8) {
        static int selecionada = 0;
        static int linha_origem, coluna_origem;

        if (!selecionada) {

            if (tabuleiro[linha][coluna] == jogador_atual || tabuleiro[linha][coluna] == jogador_atual + 2) {
                selecionada = 1;
                linha_origem = linha;
                coluna_origem = coluna;

            }
        } else {

            if (pode_mover(linha_origem, coluna_origem, linha, coluna)) {
                realizar_movimento(linha_origem, coluna_origem, linha, coluna);
                verificar_promocao(linha, coluna);
                verificar_captura_obrigatoria(linha, coluna);
                jogador_atual = (jogador_atual == 1) ? 2 : 1;
            }
            else
              {
              printf("Não é possível mover\n");
              }
            selecionada = 0;
        }
    }
}

int pode_capturar(int linha, int coluna) {

    if (tabuleiro[linha][coluna] == jogador_atual + 2) {

        if (coluna >= 2 && linha >= 2 && tabuleiro[linha - 1][coluna - 1] != 0 &&
            tabuleiro[linha - 2][coluna - 2] == 0) {
            return 1;
        }


        if (coluna <= 5 && linha >= 2 && tabuleiro[linha - 1][coluna + 1] != 0 &&
            tabuleiro[linha - 2][coluna + 2] == 0) {
            return 1;
        }


        if (coluna >= 2 && linha <= 5 && tabuleiro[linha + 1][coluna - 1] != 0 &&
            tabuleiro[linha + 2][coluna - 2] == 0) {
            return 1;
        }


        if (coluna <= 5 && linha <= 5 && tabuleiro[linha + 1][coluna + 1] != 0 &&
            tabuleiro[linha + 2][coluna + 2] == 0) {
            return 1;
        }

    } else {

        if (jogador_atual == 2) {
            if (coluna >= 2 && linha - 2 >= 0 && tabuleiro[linha - 1][coluna - 1] == 1 && tabuleiro[linha - 2][coluna - 2] == 0) {
                return 1;
            }


            if (coluna + 2 < 8 && linha - 2 >= 0 && tabuleiro[linha - 1][coluna + 1] == 1 && tabuleiro[linha - 2][coluna + 2] == 0) {
                return 1;
            }
        } else if (jogador_atual == 1) {

            if (coluna >= 2 && linha + 2 < 8 && tabuleiro[linha + 1][coluna - 1] == 2 && tabuleiro[linha + 2][coluna - 2] == 0) {
                return 1;
            }


            if (coluna + 2 < 8 && linha + 2 < 8 && tabuleiro[linha + 1][coluna + 1] == 2 && tabuleiro[linha + 2][coluna + 2] == 0) {
                return 1;
            }
        }
    }

    return 0;
}

int pode_mover(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino) {

    printf("Debug: Verificando movimento de (%d, %d) para (%d, %d)\n", linha_origem, coluna_origem, linha_destino, coluna_destino);


    if (linha_destino < 0 || linha_destino >= 8 || coluna_destino < 0 || coluna_destino >= 8) {
        return 0;
    }


    if (tabuleiro[linha_destino][coluna_destino] != 0) {
        return 0;
    }



    if (pode_capturar(linha_origem, coluna_origem)) {

        if ((abs(linha_destino - linha_origem) == 2) && (abs(coluna_destino - coluna_origem) == 2)) {

            return 1;
        } else {

            return 0;
        }
    }


    int peca_selecionada = tabuleiro[linha_origem][coluna_origem];

    printf("Debug: Peça selecionada: Jogador %d\n", peca_selecionada);


    int direcao = (jogador_atual == 1) ? 1 : -1;

    if (linha_destino == linha_origem + direcao && (coluna_destino == coluna_origem - 1 || coluna_destino == coluna_origem + 1)) {
        printf("Debug: Movimento permitido para frente (uma casa)\n");
        return 1;
    }


    if (tabuleiro[linha_origem][coluna_origem] == jogador_atual + 2) {
        peca_selecionada = tabuleiro[linha_origem][coluna_origem];
    }


    if (peca_selecionada == 3 || peca_selecionada == 4) {
        printf("Debug: Verificando movimento para damas\n");
    }


   if ((peca_selecionada == 3 || peca_selecionada == 4) && abs(linha_destino - linha_origem) == 2 &&
    (abs(coluna_destino - coluna_origem) == 2)) {
    printf("Debug: Movimento permitido para trás (duas casas, somente para damas)\n");
    return 1;
    }



   if ((peca_selecionada == 3 || peca_selecionada == 4) && (abs(linha_destino - linha_origem) == 1) && (abs(coluna_destino - coluna_origem) == 1)) {
    printf("Debug: Movimento permitido para frente ou para trás (uma casa, somente para damas)\n");
     return 1;
     } else {
     printf("Debug: Condição específica para damas não atendida\n");
  }



    printf("Debug: Movimento NÃO permitido\n");

    return 0;
}

void realizar_movimento(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino) {

    if (pode_capturar(linha_origem, coluna_origem)) {
        realizar_captura(linha_origem, coluna_origem, linha_destino, coluna_destino);
    } else {

        tabuleiro[linha_destino][coluna_destino] = tabuleiro[linha_origem][coluna_origem];
        tabuleiro[linha_origem][coluna_origem] = 0;
    }
}

void verificar_promocao(int linha, int coluna) {

    if (tabuleiro[linha][coluna] != jogador_atual + 2) {
        if ((jogador_atual == 1 && linha == 7) || (jogador_atual == 2 && linha == 0)) {

            tabuleiro[linha][coluna] = jogador_atual + 2;
            printf("Debug: Peça promovida para dama - Nova peça: %d\n", tabuleiro[linha][coluna]);
        }
    }
}


void realizar_captura(int linha_origem, int coluna_origem, int linha_destino, int coluna_destino) {

    int linha_captura = (linha_origem + linha_destino) / 2;
    int coluna_captura = (coluna_origem + coluna_destino) / 2;
    tabuleiro[linha_captura][coluna_captura] = 0;


    tabuleiro[linha_destino][coluna_destino] = tabuleiro[linha_origem][coluna_origem];
    tabuleiro[linha_origem][coluna_origem] = 0;


    captura_na_ultima_jogada = 1;
}

void verificar_captura_obrigatoria(int linha, int coluna) {

    if (captura_na_ultima_jogada) {
        if (pode_capturar(linha, coluna)) {
            realizar_captura(linha, coluna, linha + 2, coluna - 2);
            jogador_atual = (jogador_atual == 1) ? 2 : 1;
        }

        captura_na_ultima_jogada = 0;
    }
}

int verificar_vitoria() {
    int pecas_jogador1 = 0;
    int pecas_jogador2 = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j] == 1 || tabuleiro[i][j] == 3) {
                pecas_jogador1++;
            } else if (tabuleiro[i][j] == 2 || tabuleiro[i][j] == 4) {
                pecas_jogador2++;
            }
        }
    }

    if (pecas_jogador1 == 0) {
        printf("Jogador 2 é o vencedor!\n");
        return 1;
    } else if (pecas_jogador2 == 0) {
        printf("Jogador 1 é o vencedor!\n");
        return 1;
    }

    return 0;
}


void desenhar_circulo(int x, int y, int raio) {
    int i;
    int num_segmentos = 100;
    double theta = 2 * M_PI / num_segmentos;
    double c = cos(theta);
    double s = sin(theta);
    double t;

    double x1 = raio;
    double y1 = 0;

    for (i = 0; i < num_segmentos; i++) {
        SDL_RenderDrawLine(renderizador, x + x1, y + y1, x + x1, y + y1);
        t = x1;
        x1 = c * x1 - s * y1;
        y1 = s * t + c * y1;
    }
}

void desenhar_circulo_dama(int x, int y, int raio, SDL_Color cor) {
    SDL_SetRenderDrawColor(renderizador, cor.r, cor.g, cor.b, cor.a);

    filledCircleRGBA(renderizador, x, y, raio, cor.r, cor.g, cor.b, cor.a);
}

void desenhar_tabuleiro() {
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
    SDL_RenderClear(renderizador);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); // Quadrado branco
            } else {
                SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); // Quadrado preto
            }

            SDL_Rect rect = {j * TAMANHO_CELULA, i * TAMANHO_CELULA, TAMANHO_CELULA, TAMANHO_CELULA};
            SDL_RenderFillRect(renderizador, &rect);

            if (tabuleiro[i][j] == 1) {
                SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255); // Peça vermelha
                desenhar_circulo(j * TAMANHO_CELULA + TAMANHO_CELULA / 2, i * TAMANHO_CELULA + TAMANHO_CELULA / 2, TAMANHO_CELULA / 2 - 5);
            } else if (tabuleiro[i][j] == 2) {
                SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 255); // Peça azul
                desenhar_circulo(j * TAMANHO_CELULA + TAMANHO_CELULA / 2, i * TAMANHO_CELULA + TAMANHO_CELULA / 2, TAMANHO_CELULA / 2 - 5);
	       } else if (tabuleiro[i][j] == 3) {
	            SDL_Color corDama = {255, 0, 0, 255};
        	    desenhar_circulo_dama(j * TAMANHO_CELULA + TAMANHO_CELULA / 2, i * TAMANHO_CELULA + TAMANHO_CELULA / 2, TAMANHO_CELULA / 2 - 5, corDama);
        	} else if (tabuleiro[i][j] == 4) {
        	    SDL_Color corDama = {0, 0, 255, 255};
        	    desenhar_circulo_dama(j * TAMANHO_CELULA + TAMANHO_CELULA / 2, i * TAMANHO_CELULA + TAMANHO_CELULA / 2, TAMANHO_CELULA / 2 - 5, corDama);
        	}
        }
    }

    SDL_RenderPresent(renderizador);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    janela = SDL_CreateWindow("Jogo de Damas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGURA_TELA, ALTURA_TELA, SDL_WINDOW_SHOWN);
    if (janela == NULL) {
        fprintf(stderr, "Erro ao criar janela: %s\n", SDL_GetError());
        return 1;
    }

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderizador == NULL) {
        fprintf(stderr, "Erro ao criar renderer: %s\n", SDL_GetError());
        return 1;
    }

    int sair = 0;
    SDL_Event evento;

    printf("\n[JOGO DE DAMAS]\n\nAlgoritmos I\nby Izabella Cordeiro Araujo\n");
    printf("\nBoa Sorte :)\n\n");


    while (!sair) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                sair = 1;
            } else if (evento.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                lidar_com_clique(x, y);
            }
        }

        desenhar_tabuleiro();

        if (verificar_vitoria())
          {
          sair = 1;
          }

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
