enum Posicao{
    CIMA,
    BAIXO
};

typedef struct{
    char naipe;
    int valor;
    Posicao posicao;
}Cartas;