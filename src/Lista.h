#include "Carta.h"

typedef struct Celula {
    Carta carta;
    struct Celula * proxima;
} Celula;

typedef struct  {
    Celula * primeira;
    Celula * ultima;
} Lista;


void criarLista(Lista *lista);
int getTamanho(Lista *lista);  
int verificarListaVazia(Lista *lista);
 

Carta getCartaNoTopo(Lista *lista);
void getCartaNoTopoSeExistir(Lista *lista, Carta ** carta);
Carta getCarta(Lista *lista, int posicao);
void addCartaAoTopo(Lista *lista, Carta *carta);
void addCartaEmPosicaoQualquer(Lista *lista, Carta *carta, int posicao);

int retirarCartaDoTopo(Lista *lista, Carta *carta);
void transferirCartas(Lista *lista1, Lista *lista2, int quantidade);
void embaralhar(Lista *lista);

void exibirLista(Lista* lista, int mostrarTodas);