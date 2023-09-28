#include "Lista.h"
typedef struct{
    Lista baralho;
    Lista descarte; 
    Lista bases[4];
    Lista tableau[7];
    int pontuacao;
}Mesa;

void inicializarMesa(Mesa *mesa);
void carregarBaralho(Mesa *mesa, Carta *cartas[], int tamanho);
void criarBaralho(Carta *cartas);
void carregarBaralhoAleatorio(Mesa *mesa);
void exibirMesa(Mesa *mesa);
void preparar(Mesa *mesa);
void verificarVitoria(Mesa *mesa);
void comprarCarta(Mesa *mesa);
void moverDescarteBase(Mesa *mesa);
void moverDescarteTableau(Mesa *mesa,int indice);
void moverTableauBase(Mesa *mesa, int indice);
void moverBaseTableau(Mesa *mesa, int indiceBase, int indiceTableau);
void moverColunasDoTableau(Mesa *mesa, int quantidade, int indiceObtidas, int indiceReceber);
void revelarCartaTableau(Mesa *mesa, Lista *lista);

