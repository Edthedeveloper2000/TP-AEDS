#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"

void iniciar() {
    int escolha;

    printf("Bem vindo ao Paciência! \n ");
    printf("Escolha uma opção para começar: \n \n ");
    printf("1 - modo interativo \n");
    printf("2 - leitura de arquivo \n");

    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        IniciarModoInterativo();
        break;
    case 2:
        /* code */
        break;
    
    default:
        break;
    }

}

void IniciarModoInterativo() {
    printf("\nModo interativo! Escolha uma das opções abaixo! \n \n");
    Mesa mesa;
    int opcao;
    inicializarMesa(&mesa);
    carregarBaralhoAleatorio(&mesa);
    preparar(&mesa);
    
    do {
        exibirMesa(&mesa);
        printf("1 - Mover carta entre colunas do tableau.\n");
        printf("2 - Mover do tableau para uma base.\n");
        printf("3 - Mover da base para o tableau.\n");
        printf("4 - Comprar uma carta\n");
        printf("5 - Mover do descarte para a base\n");
        printf("6 - Mover do descarte para o tableau\n");
        printf("7 - Sair\n");

        scanf("%d", &opcao);

        executarAcao(&mesa, opcao);
        verificarVitoria(&mesa);

    } while (opcao != 7);
}

void executarAcao(Mesa *mesa,  int opcao) {
    switch (opcao)
    {
    case 1:
        AcaoMoverEntreColunasDoTableau(mesa);
        break;
    case 2:
        AcaoMoverDoTableauParaBase(mesa);
        break;
    case 3:
        AcaoMoverDaBaseParaOTableau(mesa);
        break;
    case 4:
        comprarCarta(mesa);
        break;
    case 5:
        moverDescarteBase(mesa);
        break;
    case 6:
        AcaoMoverDescarteParaTableau(mesa);
        break;
    case 7:
        printf("\nObrigado por jogar conosco. Você ganhará na próxima\n");
        exit(0);
        break;
    default:
        printf("\nOperação inválida. Tente novamente\n");
        break;
    }
}

void AcaoMoverEntreColunasDoTableau(Mesa *mesa) {
    int quantidade, colunaOrigem, colunaDestino;

    printf("\nQuantas cartas deseja mover?\n");
    scanf("%d", &quantidade);

    printf("\nDe qual coluna?\n");
    scanf("%d", &colunaOrigem);

    printf("\nPara qual coluna?\n");
    scanf("%d", &colunaDestino);

    moverColunasDoTableau(mesa, quantidade, colunaOrigem, colunaDestino);
}

 void AcaoMoverDoTableauParaBase(Mesa *mesa) {
    int indice;

    printf("\nDe qual coluna deseja mandar uma carta para a base?\n");
    scanf("%d", &indice);

    moverTableauBase(mesa, indice);
}

void AcaoMoverDaBaseParaOTableau(Mesa *mesa) {
    int indiceBase, indiceTableau;

    printf("\nDe qual base deseja enviar uma carta?\n");
    scanf("%d", &indiceBase);

    printf("\nPara qual coluna do tableau?\n");
    scanf("%d", &indiceTableau);

    moverBaseTableau(mesa, indiceBase, indiceTableau);
}

void AcaoMoverDescarteParaTableau(Mesa *mesa) {
    int indiceTableau;

    printf("\nPara qual coluna deseja enviar uma carta?\n");
    scanf("%d", &indiceTableau);

    moverDescarteTableau(mesa, indiceTableau);
}