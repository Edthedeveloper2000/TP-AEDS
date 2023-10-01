#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Menu.h"
int main() {
    /**
     * Configuração do padrão UTF-8 na aplicação
    */
    setlocale(LC_ALL, "en_US.utf8");
    
    iniciar();
}