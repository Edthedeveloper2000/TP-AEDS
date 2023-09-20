#include "Lista.h"
#include <stdlib.h>

void criarLista(Lista *lista){
    lista->primeira = (Celula*) malloc(sizeof(Celula));
    lista->ultima = lista->primeira;
    lista->primeira->proxima = NULL;
}

int getTamanho(Lista* lista){
    Celula* aux;
    int tamanhoLista;
    aux = lista->primeira;
    while(aux != NULL){
        aux = aux->proxima;
        tamanhoLista++;
    }
    return (tamanhoLista);
}

int verificarListaVAZIA(Lista* lista){
    return (lista->primeira == lista->ultima);
};


Carta getCartaNoTopo(Lista *lista) {
    return lista->ultima->carta;
};

Carta getCarta(Lista *lista, int posicao) {
    int contador = 0;
    Celula *celulaAtual = lista->primeira->proxima;
    while(contador != posicao) {
        celulaAtual = celulaAtual->proxima;
        contador++;
    }

    return celulaAtual->carta;
};
void addCartaAoTopo(Lista *lista, Carta *carta) {
    if(verificarListaVAZIA(lista)){
        lista->ultima = (Celula*) malloc(sizeof(Celula));
        lista->primeira = lista->ultima;
    }else{
        lista->ultima->proxima = (Celula *) malloc(sizeof(Celula));
        lista->ultima = lista->ultima->proxima;
        lista->ultima->carta = *carta;
        lista->ultima->proxima = NULL;
    }
};

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