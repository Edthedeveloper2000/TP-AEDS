#include "Mesa.h"

void carregarbaralho(Mesa *mesa, Carta *cartas[], int tamanho) {
    for(int i = 0; i< tamanho; i++) {
        addCartaAoTopo(&mesa->baralho, cartas[i]);
    }
};

void carregarBaralhoAleatorio(Mesa *mesa, Carta *cartas[]) {
    for(int i = 0; i< 52; i++) {
        addCartaAoTopo(&mesa->baralho, cartas[i]);
    }
    embaralhar(&mesa->baralho);
}

void exibirMesa(Mesa *mesa) {
    printf("Baralho: ");
    exibirLista(&mesa->baralho, 1);
    printf("\n");
    printf("Descarte: ");
    exibirLista(&mesa->descarte, 1);
    printf("\n");
    printf("Bases: ");
    for(int i=0; i<4; i++) {
        printf("Base %d: ", i);
        exibirLista(&mesa->bases[i], 1);
    }

    printf("Tableau: ");
    for(int i=0; i<7; i++) {
        printf("Coluna %d: ", i);
        exibirLista(&mesa->tableau[i], 1);
    }
 
}

