#include <stdio.h>
#include <stdlib.h>
#include "Mesa.h"

/**
 * Cria uma mesa com todas as listas vazias
*/
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

int getPontuacao(Mesa *mesa) {
    return mesa->pontuacao;
}

void setPontuacao(Mesa *mesa, int pontuacao) {
    if(mesa->pontuacao + pontuacao < 0) {
        mesa->pontuacao = 0;
    } else {
        mesa->pontuacao+=pontuacao;
    }
}

/**
 * Recebe um vetor e um tamanho para uma quantidade de cartas
 * E adiciona essas cartas ao baralho, preservando a ordem inicial
*/
void carregarBaralho(Mesa *mesa, Carta cartas[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        addCartaAoTopo(&mesa->baralho, &cartas[i]);
    }
}

/**
 * Gera cada uma das 52 cartas do Paciência
 * e salva no vetor passado
*/
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
                criarCarta(&(cartas[i*13 + (j)]), naipe, j+1, BAIXO);
            }
        }
}

/**
 * Cria um baralho de 52 cartas e o embaralha
*/
void carregarBaralhoAleatorio(Mesa *mesa) {
    Carta cartas[52];
    criarBaralho(cartas);
    for(int i = 0; i < 52; i++) {
        addCartaAoTopo(&mesa->baralho, &cartas[i]);
    }
    embaralhar(&mesa->baralho);
}

/**
 * Monta as colunas do tableau, colocando i+1 cartas
 * de acordo com o número da coluna
*/
void preparar(Mesa *mesa) {
    for (int i = 0; i < 7; i++) {
        transferirCartas(&mesa->baralho, &mesa->tableau[i], i + 1);
    }
}

/**
* Move a carta do Topo do baralho (final da lista) para o Descarte
* alterando a Posição que se encontra essa carta
**/
void comprarCarta(Mesa *mesa) {
   if(getTamanho(&mesa->baralho) == 0){
        int tamanho = getTamanho(&mesa->descarte);
        for(int i = 0; i < tamanho; i++){
            Carta cartaAux = getCartaNoTopo(&mesa->descarte);
            addCartaAoTopo(&mesa->baralho, &cartaAux);
            retirarCartaDoTopo(&mesa->descarte, &cartaAux);
        }

    setPontuacao(mesa, -50);
    } else {
        transferirCartas(&mesa->baralho, &mesa->descarte, 1);
    }
}

/**
 * identifica o naipe da carta ao topo do descarte
 * e adiciona na base correspondente se existir
*/
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
    
    getCartaNoTopoSeExistir(&mesa->bases[baseIndice], &cartaBase);
    if(compararNaipesIguais(cartaBase, &cartaDescarte)) {
        transferirCartas(&mesa->descarte, &mesa->bases[baseIndice], 1);
        setPontuacao(mesa, 10);
    } else {
        printf("Movimento inválido\n");
    }
}

/**
 * Se as cartas puderem formar uma sequencia decrescente
 * em valor, e alternada em naipe, transfere a ultima carta
 * do baralho, para a coluna do tableau informada.
*/
void moverDescarteTableau(Mesa *mesa,int indice) {
    Carta *cartaDescarte;
    getCartaNoTopoSeExistir(&mesa->descarte, &cartaDescarte);
    Carta *cartaTableau;
    getCartaNoTopoSeExistir(&mesa->tableau[indice], &cartaTableau);
    
    if(compararNaipesDiferentes( cartaTableau, cartaDescarte)) {
        transferirCartas(&mesa->descarte, &mesa->tableau[indice], 1);
        
        setPontuacao(mesa, 5);
    } else {
        printf("Movimento inválido\n");
    }
}

/***
* Move a carta do Tableu para a Base, no caso cada indice da base representa um naipe
**/
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
    getCartaNoTopoSeExistir(&mesa->bases[baseIndice], &cartaBase);

    if(compararNaipesIguais(cartaBase, &cartaTableau)) {
        transferirCartas(&mesa->tableau[indice], &mesa->bases[baseIndice], 1);

       setPontuacao(mesa, 10);
    }
    
    revelarCartaTableau(mesa, &mesa->tableau[indice]);
}
/**
*   Move a cara do topo(ultima da lista) da base para um tableau
**/
void moverBaseTableau(Mesa *mesa, int indiceBase, int indiceTableau) {
    Carta cartaTableau = getCartaNoTopo(&mesa->tableau[indiceTableau]);
    Carta cartaBase = getCartaNoTopo(&mesa->bases[indiceBase]);
    if(compararNaipesDiferentes(&cartaTableau, &cartaBase)) {
        transferirCartas(&mesa->bases[indiceBase], &mesa->tableau[indiceTableau], 1);

        setPontuacao(mesa, -15);
    }
}

/**
 * Se as cartas puderem formar uma sequência alternada em naipe e
 * decrescente em valor, move a quantidade indicada de items de uma coluna 
 * para a outra.
*/
void moverColunasDoTableau(Mesa *mesa, int quantidade, int indiceObtidas, int indiceReceber){
    Carta *cartaTopoReceber;
    if(cartaTopoReceber == NULL) {
        printf("Carta não encontrada\n");
        return;
    }
    getCartaNoTopoSeExistir(&mesa->tableau[indiceReceber], &cartaTopoReceber);

     // Posicao da carta mais abaixo na pilha que será transferida
    int posicao =  getTamanho(&mesa->tableau[indiceObtidas]) - quantidade;
     
    Carta cartaBaixoTransferir = getCarta(&mesa->tableau[indiceObtidas], posicao);
    
    if(compararNaipesDiferentes(cartaTopoReceber, &cartaBaixoTransferir)) {
        transferirCartas(&mesa->tableau[indiceObtidas], &mesa->tableau[indiceReceber], quantidade);
        revelarCartaTableau(mesa,&mesa->tableau[indiceObtidas]);
    }
}

/**
 * Executa o movimento de virar a nova carta ao topo
 * de uma coluna para cima.
*/
void revelarCartaTableau(Mesa *mesa, Lista *coluna) {
    Carta novaCartaNoTopo = getCartaNoTopo(coluna);
    if(novaCartaNoTopo.posicao == BAIXO) {
        novaCartaNoTopo.posicao = CIMA;
        coluna->ultima->carta = novaCartaNoTopo;
        setPontuacao(mesa, 5);
    }
}
/**
* Exibe a Mesa do jogo com as respectivas cartas e listas
**/
void exibirMesa(Mesa *mesa) {
    printf("Pontuação atual: %d \n", getPontuacao(mesa) );
    printf("Baralho: ");
    exibirLista(&mesa->baralho, NENHUM);
    printf("\n");
    printf("Descarte: ");
    exibirLista(&mesa->descarte, TODOS);
    printf("\n");
    for(int i = 0; i < 4; i++) {
        printf("Base %d: ", i+1);
        exibirLista(&mesa->bases[i], TODOS);
        printf("\n");
    }

    for(int i = 0; i < 7; i++) {
        printf("Coluna %d: ", i+1);
        exibirLista(&mesa->tableau[i], SOMENTE_TOPO);
        printf("\n");
    }
 
}

/**
 * Finaliza o jogo e exibe o resultado final
 * se cada base estiver completa.
*/
void verificarVitoria(Mesa* mesa){
    int count = 0;
    for (int i = 0; i < 4 ; i++){
        Carta ultimaDaBase = getCartaNoTopo(&mesa->bases[i]);
        int valorUltimaDaBase = getValor(&ultimaDaBase);
        if(valorUltimaDaBase == 13){
            count++;
        }
        if(count == 4){
            printf("\n\nVitoria!!!\nPontuação Total: %d\n\n", getPontuacao(mesa));
            printf("Mesa final:\n\n");
            printf("\n-----------------------------------------------------\n");
            exibirMesa(mesa);
            printf("\n-----------------------------------------------------\n");
            exit(0);
        }
    }
}