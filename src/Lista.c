#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

void criarLista(Lista *lista){
    lista->primeira = (Celula*) malloc(sizeof(Celula));
    lista->ultima = lista->primeira;
    lista->primeira->proxima = NULL;
}

int getTamanho(Lista* lista){
    Celula* aux;
    int tamanhoLista = 0;
    aux = lista->primeira;
    while(aux != NULL){
        aux = aux->proxima;
        tamanhoLista++;
    }
    return (tamanhoLista);
}

int verificarListaVAZIA(Lista* lista){
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

void addCartaAoTopo(Lista *lista, Carta *carta) {
        lista->ultima->proxima = (Celula *) malloc(sizeof(Celula));
        lista->ultima = lista->ultima->proxima;
        lista->ultima->carta = *carta;
        lista->ultima->proxima = NULL;
}

int retirarCartaDoTopo(Lista *lista, Carta *carta) {
    Celula *ultimaCelula = lista->primeira->proxima;
    Celula *penultimaCelula = lista->primeira;

    if(verificarListaVAZIA(lista)) {
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


void transferirCartas(Lista *lista1, Lista *lista2, int quantidade){ 
   Carta *cartas[quantidade];
   for(int i = 0; i == quantidade; i++) {
        Carta carta;
        retirarCartaDoTopo(lista1, &carta);
        cartas[i] = &carta;
   } 

   for(int j = quantidade; (j = 0) ; j--) {
        addCartaAoTopo(lista2, cartas[j]);
   }
}


void exibirLista(Lista* lista, int mostrarTodas){
    if(verificarListaVAZIA(lista)){
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