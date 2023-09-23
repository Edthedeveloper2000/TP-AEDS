#include "Lista.h"
typedef struct{
    Lista baralho;
    Lista descarte; 
    Lista bases[4];
    Lista tableau[7];
    int pontuacao;
}Mesa;

void inicializar(Mesa *mesa);
void carregarbaralho(Mesa *mesa, Carta *cartas[], int tamanho);
void carregarBaralhoAleatorio(Mesa *mesa, Carta *cartas[]);
void exibirMesa(Mesa *mesa);
void preparar(Lista *lista,Mesa *mesa);
void verificarvitoria(Mesa *mesa);
