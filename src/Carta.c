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
    if(carta1 == NULL) {
        if(carta2->valor==13){
            return 1;
        } else {
            return 0;
        }
    }

    if(carta1->naipe == 'c' || carta1->naipe == 'o') {
        if(((carta2->naipe == 'p') && (carta2->valor == carta1->valor + 1)) || ((carta2->naipe == 'e') && (carta2->valor == carta1->valor + 1))) {
            return 1;
        } else {
            return 0;
        }
    } else if (carta1->naipe =='p' || carta1->naipe == 'e') {
        if(((carta2->naipe == 'c') && (carta2->valor == carta1->valor + 1)) || ((carta2->naipe == 'o') && (carta2->valor == carta1->valor + 1))) {
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
        case 'c':
            printf("[♥️ %d]", carta->valor);
            break;

        case 'p' :
            printf("[♣️ %d]", carta->valor);
            break;
            
        case 'e' :
            printf("[♠️ %d]", carta->valor);
            break;

        case 'o' :
            printf("[♦️ %d]", carta->valor);
            break;
            
        default:
            break;
        }
    }else{
        printf("[  ]");
    }

    printf(" ");
}
