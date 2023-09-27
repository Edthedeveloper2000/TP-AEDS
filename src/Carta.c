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

int compararNaipesIguais(Carta *carta1, Carta *carta2) {
    if(!carta1) {
        if(carta2->valor==1){
            return 1;
        } else {
            return 0;
        }
    } 
    
    else if (carta1->naipe == carta2->naipe && carta2->valor == (carta1->valor + 1)) {
        return 1;
    }

    return 0;
} 

int compararNaipesDiferentes( Carta *carta1, Carta *carta2){
    if(!carta1) {
        if(carta2->valor==13){
            return 1;
        } else {
            return 0;
        }
    }

    if(carta1->naipe == 'C' || carta1->naipe == 'O') {
        if(((carta2->naipe == 'P') && (carta2->valor == carta1->valor + 1)) || ((carta2->naipe == 'E') && (carta2->valor == carta1->valor + 1))) {
            return 1;
        } else {
            return 0;
        }
    } else if (carta1->naipe =='P' || carta1->naipe == 'E') {
        if(((carta2->naipe == 'C') && (carta2->valor == carta1->valor + 1)) || ((carta2->naipe == 'O') && (carta2->valor == carta1->valor + 1))) {
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
            printf("[C %d]", carta->valor);
            break;

        case 'P' :
            printf("[P %d]", carta->valor);
            break;
            
        case 'E' :
            printf("[E %d]", carta->valor);
            break;

        case 'O' :
            printf("[O %d]", carta->valor);
            break;
            
        default:
            break;
        }
    }else{
        printf("[  ]");
    }

    printf(" ");
}
