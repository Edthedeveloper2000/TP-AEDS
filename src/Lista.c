#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

Carta getCarta(Lista *lista, int posicao) {
    int contador = 0;
    Celula *celulaAtual = lista->primeira->proxima;
    while(contador != posicao) {
        celulaAtual = celulaAtual->proxima;
        contador++;
    }

    return celulaAtual->carta;
}

Celula * getCelula(Lista *lista, int posicao) {
    int contador = 0;
    Celula *celulaAtual = lista->primeira->proxima;
    while(contador != posicao) {
        celulaAtual = celulaAtual->proxima;
        contador++;
    }

    return celulaAtual;
}

void addCartaAoTopo(Lista *lista, Carta *carta) {
    lista->ultima->proxima = (Celula *) malloc(sizeof(Celula));
    lista->ultima = lista->ultima->proxima;
    lista->ultima->carta = *carta;
    lista->ultima->proxima = NULL;
}

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

void transferirCartas(Lista* listaOrigem, Lista* listaDestino, int quantidade) {
    int tamanhoOrigem = (getTamanho(listaOrigem) + 1);

    if ((quantidade > (tamanhoOrigem - 1)) || quantidade <= 0) {
        printf("Quantidade inválida de cartas para mover.\n");
        return;
    }
    int posicaoPrimeiraCarta = tamanhoOrigem - quantidade;
    Celula* anterior = NULL;
    Celula* atual = listaOrigem->primeira;
    for (int i = 0; i < posicaoPrimeiraCarta; i++) {
        anterior = atual;
        atual = atual->proxima;
    }

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

    if(verificarListaVazia(listaOrigem)) {
        listaOrigem->primeira->proxima = NULL;
        listaOrigem->ultima->proxima = NULL;
    }
}


void embaralhar(Lista *lista) {
    int cont;
    int tamanho = getTamanho(lista);

    if (tamanho <= 1) {
        // Não é necessário embaralhar uma lista com 0 ou 1 elemento
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

void exibirLista(Lista* lista, int mostrarTodas){
    if(verificarListaVazia(lista)){
        printf("Lista Vazia");
    } else {
        if(mostrarTodas) {
            Celula* aux;
            aux = lista->primeira->proxima;
            while(aux != NULL){
                Carta cartaAtual = aux->carta;
                exibirCarta(&cartaAtual);
                aux = aux->proxima;
            }
            free(aux);
        } else {
            Carta carta = getCartaNoTopo(lista);
            exibirCarta(&carta);
        }
    }
}