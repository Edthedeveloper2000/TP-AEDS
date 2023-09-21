#include <lista.h>
typedef struct{
    Lista baralho;
    Lista descarte;
    Lista bases[4];
    Lista tableau[7];
    int pontuacao;
}Mesa;

void inicializar(Mesa *mesa);
void carregarbaralho(Carta *carta[]);
void preparar(Lista *lista,Mesa *mesa);
void verificarvitoria(Mesa *mesa);
