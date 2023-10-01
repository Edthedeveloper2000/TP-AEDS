#include "Mesa.h"

void iniciar();

// Modo interativo:
void iniciarModoInterativo();
void executarAcao(Mesa *mesa,  int opcao);
void acaoMoverEntreColunasDoTableau(Mesa *mesa);
void acaoMoverDescarteParaTableau(Mesa *mesa);
void acaoMoverDoTableauParaBase(Mesa *mesa);
void acaoMoverDaBaseParaOTableau(Mesa *mesa);

// Modo de arquivo:
void iniciarModoArquivo();