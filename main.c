#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "linhas.h"
#include "estacoes.h"
#include "FuncoesAux.h"

int main()
{
    setlocale(LC_ALL, "");
    /*carregar_linhas();
    cadastrar_linhas();
    alterar_linhas();
    excluir_linhas();
    visualizar_linhas();*/

    carregar_estacoes();
    cadastrar_estacoes();
    alterar_estacoes();
    excluir_estacoes();
    visualizar_estacoes();
}