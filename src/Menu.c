#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"
#include <string.h>

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
        iniciarModoInterativo();
        break;
    case 2:
        iniciarModoArquivo();
        break;
    
    default:
        break;
    }

}

// MODO INTERATIVO:

void iniciarModoInterativo() {
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
        acaoMoverEntreColunasDoTableau(mesa);
        break;
    case 2:
        acaoMoverDoTableauParaBase(mesa);
        break;
    case 3:
        acaoMoverDaBaseParaOTableau(mesa);
        break;
    case 4:
        comprarCarta(mesa);
        break;
    case 5:
        moverDescarteBase(mesa);
        break;
    case 6:
        acaoMoverDescarteParaTableau(mesa);
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

void acaoMoverEntreColunasDoTableau(Mesa *mesa) {
    int quantidade, colunaOrigem, colunaDestino;

    printf("\nQuantas cartas deseja mover?\n");
    scanf("%d", &quantidade);

    if(quantidade <= 0 || quantidade > 13){
        printf("A Quantidade é inválida\n");
        return;
    }
    
    printf("\nDe qual coluna?\n");
    scanf("%d", &colunaOrigem);
    
    if(colunaOrigem < 0 || colunaOrigem > 6){
        printf("A coluna não existe\n");
        return;  
    }
    printf("\nPara qual coluna?\n");
    scanf("%d", &colunaDestino);

    if(colunaDestino < 0 || colunaDestino > 6) {
        printf("A coluna não existe\n");
        return;
    }


    moverColunasDoTableau(mesa, quantidade, colunaOrigem, colunaDestino);
}

 void acaoMoverDoTableauParaBase(Mesa *mesa) {
    int indice;

    printf("\nDe qual coluna deseja mandar uma carta para a base?\n");
    scanf("%d", &indice);
    
    if(indice < 0 || indice >6) {
        printf("A coluna não existe\n");
        return;
    }

    moverTableauBase(mesa, indice);
}

void acaoMoverDaBaseParaOTableau(Mesa *mesa) {
    int indiceBase, indiceTableau;

    printf("\nDe qual base deseja enviar uma carta?\n");
    scanf("%d", &indiceBase);

    if(indiceBase < 0 || indiceBase > 3){
        printf("A base não existe\n");
        return;
    }
    
    printf("\nPara qual coluna do tableau?\n");
    scanf("%d", &indiceTableau);

    if( indiceTableau < 0 || indiceTableau > 6){
        printf("A coluna não existe\n");
        return;
    }

    moverBaseTableau(mesa, indiceBase, indiceTableau);
}

void acaoMoverDescarteParaTableau(Mesa *mesa) {
    int indiceTableau;

    printf("\nPara qual coluna deseja enviar uma carta?\n");
    scanf("%d", &indiceTableau);
    
    if(indiceTableau < 0 || indiceTableau > 6) {
        printf("A coluna não existe\n");
        return;
    }

    moverDescarteTableau(mesa, indiceTableau);
}

// MODO DE ARQUIVO:

void iniciarModoArquivo() {
    Mesa mesa;
    char nomeArquivo[250];
    FILE * arquivo;
    int quantidadeCartas;
    
    inicializarMesa(&mesa);

    printf("Informe o caminho do arquivo: \n");
    scanf("%s", nomeArquivo);
    
    arquivo =  fopen(nomeArquivo,  "r");
    if(arquivo == NULL){
        printf("Falha ao iniciar o arquivo");
        exit(1);
    }

    fscanf(arquivo,"%d", &quantidadeCartas);

    if(quantidadeCartas >= 28 && quantidadeCartas <= 52){
        Carta* cartas = malloc(quantidadeCartas * sizeof(Carta));
        int tamanhoBaralho = quantidadeCartas - 28;
        
        for(int i = 0; i < tamanhoBaralho; i++){
            Carta aux;
            char naipe;
            int valor;
            fscanf(arquivo, " (%d %c) ", &valor, &naipe);
            criarCarta(&aux, naipe, valor, CIMA);
            cartas[i] = aux;
        }
        
        carregarBaralho(&mesa, cartas, tamanhoBaralho);

        for(int i = 6; i>=0; i--) {
            Carta aux;
            char naipe;
            int valor;
            for(int j =0; j<=i; j++) {
                fscanf(arquivo, " (%d %c) ", &valor, &naipe);
                criarCarta(&aux ,naipe, valor, CIMA);
                addCartaAoTopo(&mesa.tableau[i], &aux);
            }
        }

        printf("\n-----------------------------------------------------\n");
        printf("\nInício\n");
        exibirMesa(&mesa);
        printf("\n-----------------------------------------------------\n");

        char comando[3];
        int quantidade;
        int indiceTableuOrigem;
        int indiceTableuDestino;
        while (fscanf(arquivo, "%s", comando) == 1) {
            if (strcmp(comando, "TB") == 0) {
                fscanf(arquivo, " %d", &indiceTableuOrigem);
                moverTableauBase(&mesa, indiceTableuOrigem);
            
            } else if (strcmp(comando, "BT") == 0) {
                char naipe;
                int indiceTableau;
                fscanf(arquivo, " %c %d", &naipe, &indiceTableau );
                int baseIndice;
                 switch (naipe){
                    case 'C':
                        baseIndice = 0;
                        break;
                    case 'P' :
                        baseIndice = 1;
                        break;
                    case 'O' :
                        baseIndice = 2;
                        break;
                    case 'E' :
                        baseIndice = 3;
                        break;
                    
                    default:
                        break;
                    }

                    moverBaseTableau(&mesa, baseIndice, indiceTableau);
                    
            } else if (strcmp(comando, "CC") == 0) {
                comprarCarta(&mesa);
            
            } else if (strcmp(comando, "DB") == 0) {
                moverDescarteBase(&mesa);
            
            } else if (strcmp(comando, "TT") == 0) {
                fscanf(arquivo, " %d %d %d", &quantidade, &indiceTableuOrigem, &indiceTableuDestino);
                moverColunasDoTableau(&mesa, quantidade, indiceTableuOrigem, indiceTableuDestino);
            
            } else if (strcmp(comando, "DT") == 0) {
                fscanf(arquivo, " %d", &indiceTableuDestino);
                moverDescarteTableau(&mesa, indiceTableuDestino);
            }
             else if (strcmp(comando, "X") == 0) {
                printf("Encerrado");
                exit(0);
                break;
            }
           
           verificarVitoria(&mesa);
        }
        free(cartas);
    }else{
        printf("\nQuantidade de Cartas inválidas");
    }

    fclose(arquivo);
}