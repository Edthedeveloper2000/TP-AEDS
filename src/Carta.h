typedef enum{
    CIMA,
    BAIXO
}Posicao;

typedef struct{
    char naipe;
    int valor;
    Posicao posicao;
}Carta;

void criarCarta(Carta* carta, char naipe, int valor, Posicao posicao);
char getNaipe(Carta* carta);
int getValor(Carta* carta);
Posicao getPosicao(Carta* Carta);
void setPosicao(Carta* carta);

int compararNaipesIguais(Carta* carta1, Carta* carta2);
int compararNaipesDiferentes(Carta* carta1, Carta* carta2);

void exibirCarta(Carta* carta);