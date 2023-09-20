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
Carta getCarta(Lista *lista, int posicao);
void addCartaAoTopo(Lista *lista, Carta *carta);

void retirarCartaDoTopo(Lista *lista);
