#include <stdio.h>
#include "Carta.h"

// Cria a Carta com o Naipe e Valor passados
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

// Altera a Posição  da carta, se CIMA vira BAIXO, se BAIXO vira CIMA 
void setPosicao(Carta *carta) {
    carta->posicao = !carta->posicao;
}

/**
 * Compara duas cartas, verificando se possuem o mesmo naipe
 * e se a segunda é a próxima em valor em relação a primeira
*/
int compararNaipesIguais(Carta *cartaAtual, Carta *proximaCarta) {
    if(cartaAtual == NULL) {
        if(proximaCarta->valor==1){
            return 1;
        } else {
            return 0;
        }
    } 
    
    else if (cartaAtual->naipe == proximaCarta->naipe && proximaCarta->valor == (cartaAtual->valor + 1)) {
        return 1;
    }

    return 0;
} 


/**
 * Compara a carta ao topo da coluna destino com a carta mais abaixo da pilha que será movida
 * para verificar se atendem a uma sequencia descrescente em valor e alternada em naipe.
*/
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

// Exibe a carta na tela com seu respectivo Valor, Naipe e Posiçao
void exibirCarta(Carta *carta) {
    if(carta->posicao == CIMA) { 
        switch (carta->naipe){
        case 'C':
            printf("\033[1;31m");
            printf("[♥ %d]", carta->valor);
            break;

        case 'P' :
            printf("\033[90m");
            printf("[♣ %d]", carta->valor);
            break;
            
        case 'E' :
            printf("\033[90m");
            printf("[♠ %d]", carta->valor);
            break;

        case 'O' :
            printf("\033[1;31m");
            printf("[♦ %d]", carta->valor);
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
