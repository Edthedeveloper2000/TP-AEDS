#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * Gera uma lista encadeada com cabeça, vazia
*/
void criarLista(Lista *lista){
    lista->primeira = (Celula*) malloc(sizeof(Celula));
    lista->ultima = lista->primeira;
    lista->primeira->proxima = NULL;
}

int getTamanho(Lista* lista){
    Celula* aux;
    int tamanhoLista = 0;
    aux = lista->primeira->proxima;
    while(aux != NULL){
        aux = aux->proxima;
        tamanhoLista++;
    }
    return (tamanhoLista);
}

int verificarListaVazia(Lista* lista){
    return (lista->primeira == lista->ultima);
}


Carta getCartaNoTopo(Lista *lista) {
    return lista->ultima->carta;
}

void getCartaNoTopoSeExistir(Lista *lista, Carta **carta) {
    if (verificarListaVazia(lista)) {
        *carta = NULL; // Modifica o ponteiro original para apontar para NULL
    } else {
        *carta = &(lista->ultima->carta); // Modifica o ponteiro original para apontar para a carta no topo
    }
}

// Obtem a carta presente em uma posição qualquer da lista
Carta getCarta(Lista *lista, int posicao) {
    int contador = 0;
    Celula *celulaAtual = lista->primeira->proxima;
    while(contador != posicao) {
        celulaAtual = celulaAtual->proxima;
        contador++;
    }

    return celulaAtual->carta;
}

/**
 * Obtem a célula numa dada posição
*/
Celula * getCelula(Lista *lista, int posicao) {
    int contador = 0;
    Celula *celulaAtual = lista->primeira->proxima;
    while(contador != posicao) {
        celulaAtual = celulaAtual->proxima;
        contador++;
    }

    return celulaAtual;
}
// Adiciona uma carta no Topo do baralho (Fim da lista)
void addCartaAoTopo(Lista *lista, Carta *carta) {
    lista->ultima->proxima = (Celula *) malloc(sizeof(Celula));
    lista->ultima = lista->ultima->proxima;
    lista->ultima->carta = *carta;
    lista->ultima->proxima = NULL;
}

// Adiciona uma Carta em uma Posição qualquer na lista
void addCartaEmPosicaoQualquer(Lista *lista, Carta *carta, int posicao) {
    Celula *atual = lista->primeira->proxima;
    Celula *aux = atual;

    if(!verificarListaVazia(lista) && posicao >1) {
        int cont = 0;
        while (atual != NULL && cont < posicao - 1) {
        aux = atual;
        atual = atual->proxima;
        cont++;
    }
    } else {
        aux = lista->primeira;
    }
    
    Celula *celulaTemp = aux->proxima;
    aux->proxima = (Celula *)malloc(sizeof(Celula));
    aux->proxima->carta = *carta;
    aux->proxima->proxima = celulaTemp;

    free(aux);
}
// Remove a ultima carta da lista
int retirarCartaDoTopo(Lista *lista, Carta *carta) {
    Celula *ultimaCelula = lista->primeira->proxima;
    Celula *penultimaCelula = lista->primeira;

    if(verificarListaVazia(lista)) {
        return 0;
    }
    *carta = lista->ultima->carta;

    while(ultimaCelula->proxima != NULL) {
        penultimaCelula = ultimaCelula;
        ultimaCelula = ultimaCelula->proxima;
    }

    penultimaCelula->proxima = NULL;
    lista->ultima = penultimaCelula;

    free(ultimaCelula);

    return 1;
}

/**
 * Transfere uma quantidade dada de cartas da lista 1 para a lista 2
 * preserb=vando a ordem dos elementos
*/
void transferirCartas(Lista* listaOrigem, Lista* listaDestino, int quantidade) {
    int tamanhoOrigem = (getTamanho(listaOrigem) + 1);
    // Verificação para ver se a quantidade de cartas a serem tranferidas é válida
    if ((quantidade > (tamanhoOrigem - 1)) || quantidade <= 0) {
        printf("Quantidade inválida de cartas para mover.\n");
        return;
    }
    
    /**
    * Percorre a lista até chegar na primeira carta a ser transferida para a a lista de destino
    * e armazena a posição anterior da primeira que será transferida
    **/
    int posicaoPrimeiraCarta = tamanhoOrigem - quantidade;
    Celula* anterior = NULL;
    Celula* atual = listaOrigem->primeira;
    for (int i = 0; i < posicaoPrimeiraCarta; i++) {
        anterior = atual;
        atual = atual->proxima;
    }

    /**
    * Percorre a lista de origem adicionando item por item na lista de destino
    * começa pela carta obtida pela variavel "atual"
    **/
    for (int i = 0; i < quantidade; i++) {
        if(atual == NULL){
            break;
        }
        Celula* proxima = atual->proxima;
        Carta carta = atual->carta;
        addCartaAoTopo(listaDestino, &carta);
        free(atual);
        atual = proxima;
    }

    if (anterior) {
        anterior->proxima = atual;
    } else {
        listaOrigem->primeira = atual;
    }

    listaOrigem->ultima = (anterior != NULL) ? anterior : listaOrigem->primeira->proxima;

    // Verifica se a lista de Origem ficou vazia após a transferencia
    if(verificarListaVazia(listaOrigem)) {
        listaOrigem->primeira->proxima = NULL;
        listaOrigem->ultima->proxima = NULL;
    }
}


/**
 * Embaralha uma lista percorrendo cada elemento e trocando
 * o conteúdo de sua célula com o de outra cuja posição é 
 * gerada aleatoriamente.
*/
void embaralhar(Lista *lista) {
    int cont;
    int tamanho = getTamanho(lista);

    if (tamanho <= 1) {
        return;
    }

    srand(time(NULL));

    for (cont = 0; cont < tamanho; cont++) {
        int posicaoAleatoria = rand() % tamanho;
        Celula *celulaAleatoria = getCelula(lista, posicaoAleatoria);
        Celula *celulaAtual = getCelula(lista, cont);
        Carta cartaAleatoria = getCarta(lista, posicaoAleatoria);
        Carta cartaAtual = getCarta(lista, cont);

        // Trocar as cartas entre as células
        celulaAleatoria->carta = cartaAtual;
        celulaAtual->carta = cartaAleatoria;
    }
}

/**
 * Exibe a lista em três tipos de visualização
 * @param Visualizar visualizar:
 * - SOMENTE_TOPO: mostra todas para baixo, exceto a do topo
 * - TODOS: mostra todas para cima
 * - NENHUM: mostra todas para baixo
*/
void exibirLista(Lista* lista, Visualizar visualizar){
    if(verificarListaVazia(lista)){
        printf("Lista Vazia");
    } else{
        if(visualizar == TODOS){
           Celula* aux = lista->primeira->proxima;
            while (aux != NULL){
                    aux->carta.posicao = CIMA;
                exibirCarta(aux);
                aux = aux->proxima; 
            }
            free(aux);       
        } 
        else if (visualizar == SOMENTE_TOPO){
            Celula* aux = lista->primeira->proxima;
            while (aux != NULL){
                if(aux->proxima == NULL){
                    aux->carta.posicao = CIMA;
                }
                exibirCarta(aux);
                aux = aux->proxima; 
            }
            free(aux);       
        } else {
            Celula* aux = lista->primeira->proxima;
            while (aux != NULL){
                aux->carta.posicao = BAIXO;
                exibirCarta(aux);
                aux = aux->proxima; 
            }
            free(aux);  
        }
    }
}