#include <stdio.h>
#include <stdlib.h>
#include "Mesa.h"

void inicializarMesa(Mesa *mesa){
    mesa->pontuacao = 0;
    criarLista(&mesa->baralho);
    criarLista(&mesa->descarte);
    
    for(int i = 0; i < 4; i++) {
        criarLista(&mesa->bases[i]);
    }

    for(int j = 0; j < 7; j++) {
        criarLista(&mesa->tableau[j]);
    }
}

void carregarBaralho(Mesa *mesa, Carta *cartas[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        addCartaAoTopo(&mesa->baralho, cartas[i]);
    }
}

void criarBaralho(Carta cartas[]){
    char naipe;
    for (int i = 0; i<4; i++){
            switch (i){
            case 0:
                naipe = 'C';
                break;
            case 1:
                naipe = 'P';
                break;
            case 2:
                naipe = 'O';
                break;
            case 3:
                naipe = 'E';
            default:
                break;
            }
            for(int j = 0; j <13; j++){
                criarCarta(&(cartas[i*13 + (j)]), naipe, j+1, CIMA);
            }
        }
}
void carregarBaralhoAleatorio(Mesa *mesa) {
    Carta cartas[52];
    criarBaralho(cartas);
    for(int i = 0; i < 52; i++) {
        addCartaAoTopo(&mesa->baralho, &cartas[i]);
    }
    embaralhar(&mesa->baralho);
}

void preparar(Mesa *mesa) {
    for (int i = 0; i < 7; i++) {
        transferirCartas(&mesa->baralho, &mesa->tableau[i], i + 1);
    }
}


void comprarCarta(Mesa *mesa) {
    if(getTamanho(&mesa->baralho) == 0){
        transferirCartas(&mesa->descarte, &mesa->baralho, getTamanho(&mesa->descarte));
        mesa->pontuacao -= 50;
    } else {
        transferirCartas(&mesa->baralho, &mesa->descarte, 1);
    }
}

void moverDescarteBase(Mesa *mesa) {
    Carta cartaDescarte = getCartaNoTopo(&mesa->descarte);
    int baseIndice;
    switch (cartaDescarte.naipe)
    {
    case 'C':
        baseIndice = 0;
        break;
    case 'P' :
        baseIndice = 1;
        break;
    case 'O' :
        baseIndice = 2;
        break;
    case 'E' :
        baseIndice = 3;
        break;
    
    default:
        break;
    }
    
    Carta *cartaBase;
    
    if(verificarListaVazia(&mesa->bases[baseIndice])) {
        cartaBase = NULL;
    } else {
        *cartaBase = getCartaNoTopo(&mesa->bases[baseIndice]);
    }
    exibirCarta(&cartaBase);
    if(compararNaipesIguais(cartaBase, &cartaDescarte)) {
        transferirCartas(&mesa->descarte, &mesa->bases[baseIndice], 1);
        
        mesa->pontuacao += 10;
    } else {
        printf("Movimento inválido\n");
    }
}

void moverDescarteTableau(Mesa *mesa,int indice) {
    Carta cartaDescarte = getCartaNoTopo(&mesa->descarte);
    Carta cartaTableau = getCartaNoTopo(&mesa->tableau[indice]);
    
    if(compararNaipesDiferentes( &cartaTableau, &cartaDescarte)) {
        transferirCartas(&mesa->descarte, &mesa->tableau[indice], 1);
        
        mesa->pontuacao += 5;
    } else {
        printf("Movimento inválido\n");
    }
}

void moverTableauBase(Mesa *mesa, int indice) {
    Carta cartaTableau = getCartaNoTopo(&mesa->tableau[indice]);
    int baseIndice;
    switch (cartaTableau.naipe)
    {
    case 'C':
        baseIndice = 0;
        break;
    case 'P' :
        baseIndice = 1;
        break;
    case 'O' :
        baseIndice = 2;
        break;
    case 'E' :
        baseIndice = 3;
        break;
    
    default:
        break;
    }
    
    Carta *cartaBase;
    if(verificarListaVazia(&mesa->bases[baseIndice])) {
        cartaBase = NULL;
    } else {
        *cartaBase = getCartaNoTopo(&mesa->bases[baseIndice]);
    }

    if(compararNaipesIguais(cartaBase, &cartaTableau)) {
        transferirCartas(&mesa->tableau[indice], &mesa->bases[baseIndice], 1);

        mesa->pontuacao += 10;
    }
    
    revelarCartaTableau(mesa, &mesa->tableau[indice]);
}

void moverBaseTableau(Mesa *mesa, int indiceBase, int indiceTableau) {
    Carta cartaTableau = getCartaNoTopo(&mesa->tableau[indiceTableau]);
    Carta cartaBase = getCartaNoTopo(&mesa->bases[indiceBase]);

    if(compararNaipesDiferentes(&cartaTableau, &cartaBase)) {
        transferirCartas(&mesa->bases[indiceBase], &mesa->tableau[indiceTableau], 1);

        mesa->pontuacao -= 15;
    }
}

void moverColunasDoTableau(Mesa *mesa, int quantidade, int indiceObtidas, int indiceReceber){
     Carta cartaTopoReceber = getCartaNoTopo(&mesa->tableau[indiceReceber]);

     // Posicao da carta mais abaixo na pilha que será transferida
     int posicao =  getTamanho(&mesa->tableau[indiceObtidas]) - quantidade;

     Carta cartaBaixoTransferir = getCarta(&mesa->tableau[indiceObtidas], posicao);
     
    if(compararNaipesDiferentes(&cartaTopoReceber, &cartaBaixoTransferir)) {
        transferirCartas(&mesa->tableau[indiceObtidas], &mesa->tableau[indiceReceber], quantidade);
        revelarCartaTableau(mesa,&mesa->tableau[indiceObtidas]);
    }
}

void revelarCartaTableau(Mesa *mesa, Lista *coluna) {
    Carta novaCartaNoTopo = getCartaNoTopo(coluna);
    if(novaCartaNoTopo.posicao == BAIXO) {
        novaCartaNoTopo.posicao = CIMA;
        coluna->ultima->carta = novaCartaNoTopo;
        mesa->pontuacao+=5;
    }
}

void exibirMesa(Mesa *mesa) {
    printf("Baralho: ");
    exibirLista(&mesa->baralho, 1);
    printf("\n\n");
    printf("Descarte: ");
    exibirLista(&mesa->descarte, 1);
    printf("\n\n");
    printf("Bases: ");
    for(int i = 0; i < 4; i++) {
        printf("Base %d: ", i);
        exibirLista(&mesa->bases[i], 1);
        printf("\n");
    }

    printf("Tableau: ");
    for(int i = 0; i < 7; i++) {
        printf("Coluna %d: ", i);
        exibirLista(&mesa->tableau[i], 1);
        printf("\n");
    }
 
}

void verificarVitoria(Mesa* mesa){
    int count = 0;
    for (int i = 0; i < 4 ; i++){
        Carta ultimaDaBase = getCartaNoTopo(&mesa->bases[i]);
        int valorUltimaDaBase = getValor(&ultimaDaBase);
        if(valorUltimaDaBase == 13){
            count++;
        }
    if(count == 4){
        printf("Vitoria!!!\nPontuação Total: %d", mesa->pontuacao);
        exit(0);
    }
    }
}