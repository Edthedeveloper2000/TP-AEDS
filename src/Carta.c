#include <stdio.h>
#include "Carta.h"

void criarCarta(Carta *carta, char naipe, int valor, Posicao posicao) {
    carta->naipe = naipe;
    carta->posicao = posicao;
    carta->valor = valor;
}

char getNaipe(Carta *carta) {
    return carta->naipe;
}

int getValor(Carta *carta) {
    return carta->valor;
}

Posicao getPosicao(Carta *carta) {
    return carta->posicao;
}

void setPosicao(Carta *carta) {
    carta->posicao = !carta->posicao;
}

int compararNaipesIguais(Carta *cartaAtual, Carta *proximaCarta) {
    if(cartaAtual == NULL) {
        if(proximaCarta->valor==1){
            return 1;
        } else {
            return 0;
        }
    } 
    
    else if (cartaAtual->naipe == proximaCarta->naipe && proximaCarta->valor == (cartaAtual->valor - 1)) {
        return 1;
    }

    return 0;
} 

int compararNaipesDiferentes( Carta *cartaAtual, Carta *proximaCarta){
    if(cartaAtual == NULL) {
        if(proximaCarta->valor == 13){
            return 1;
        } else {
            return 0;
        }
    }

    if(cartaAtual->naipe == 'C' || cartaAtual->naipe == 'O') {
        if(((proximaCarta->naipe == 'P') && (proximaCarta->valor == cartaAtual->valor - 1)) || ((proximaCarta->naipe == 'E') && (proximaCarta->valor == cartaAtual->valor - 1))) {
            return 1;
        } else {
            return 0;
        }
    } else if (cartaAtual->naipe =='P' || cartaAtual->naipe == 'E') {
        if(((proximaCarta->naipe == 'C') && (proximaCarta->valor == cartaAtual->valor - 1)) || ((proximaCarta->naipe == 'O') && (proximaCarta->valor == cartaAtual->valor - 1))) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
void exibirCarta(Carta *carta) {
    if(carta->posicao == CIMA) { 
        switch (carta->naipe){
        case 'C':
            printf("\033[1;31m");
            printf("[C %d]", carta->valor);
            break;

        case 'P' :
            printf("\033[90m");
            printf("[P %d]", carta->valor);
            break;
            
        case 'E' :
            printf("\033[90m");
            printf("[E %d]", carta->valor);
            break;

        case 'O' :
            printf("\033[1;31m");
            printf("[O %d]", carta->valor);
            break;
            
        default:
            break;
        }

        printf("\033[0m");
    }else{
        printf("[  ]");
    }

    printf(" ");
}
