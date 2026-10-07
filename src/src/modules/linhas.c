// codigo da funcao
#include <stdio.h>
#include <stdlib.h>
#include "linhas.h"
#include "FuncoesAux.h"

struct Linhas Linhas[MAX_LINHAS];

void cadastrar_linhas()
{
    int quantidade = 0;

    while (quantidade <= 0 || quantidade > MAX_LINHAS) // verifica se a quantidade nao excede o limite (MAX_LIMITES)
    {

        printf("\ninforme a quantidade de linhas que deseja cadastrar: ");

        if (scanf("%d", &quantidade) != 1) // verifica se a entrada foi um numero ou não
        {
            limpar_buffer();
            quantidade = 0;
            printf("Entrada invalida. Digite um numero.\n");
            continue;
        }

        limpar_buffer();

        if (quantidade <= 0 || quantidade > MAX_LINHAS)
        {
            printf("Quantidade invalida.\n");
        }
    }

    system("clear");

    for (int i = 0; i < quantidade; i++) // cadastra as linhas
    {
        printf("\nInformações da linha: \n\n");

        printf("Linha %d:\n\n", i + 1);

        int id_valido = 0;

        while (!id_valido) // valida se foi inserido um tipo inteiro ou nao
        {

            printf("id: ");

            if (scanf("%d", &Linhas[i].id) == 1)
            {

                id_valido = 1;
            }
            else
            {
                limpar_buffer();
                printf("Entrada invalida. Digite um numero.\n");
            }
        }

        limpar_buffer();

        char nome_valido = 0;

        while (!nome_valido)
        {

            printf("Nome: ");
            fgets(Linhas[i].nome, sizeof(Linhas[i].nome), stdin);

            if (Linhas[i].nome[0] == '\n')
            {

                printf("Nome invalido. Digite um nome.\n");
            }
            else
            {
                nome_valido = 1;
            }
        }

        char cor_valida = 0;

        while (!cor_valida)
        {

            printf("Cor: ");
            fgets(Linhas[i].cor, sizeof(Linhas[i].cor), stdin);

            if (Linhas[i].cor[0] == '\n')
            {
                printf("Cor invalida. Digite uma cor valida.\n");
            }
            else
            {
                cor_valida = 1;
            }
        }
        system("clear");
    }

    printf("LINHAS CADASTRADAS.\n\n"); // informa as linhas cadastradas

    for (int i = 0; i < quantidade; i++)
    {

        printf("Linha %d\n", i + 1);

        printf("ID: %d\n", Linhas[i].id);
        printf("NOME: %s", Linhas[i].nome);
        printf("COR: %s\n", Linhas[i].cor);
    }
}