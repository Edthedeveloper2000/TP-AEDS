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
    lista->ultima->proxima = (Celula *) malloc(sizeof(Celula));
    lista->ultima = lista->ultima->proxima;
    lista->ultima->carta = *carta;
    lista->ultima->proxima = NULL;
};