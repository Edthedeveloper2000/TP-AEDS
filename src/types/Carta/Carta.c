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

int compararNapiesIguais(Carta *carta1, Carta *carta2) {
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


