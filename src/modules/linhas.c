// codigo da funcao
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "linhas.h"
#include "FuncoesAux.h"

struct Linhas Linhas[MAX_LINHAS];
int proximo_id = 1;
int quantidade_linhas = 0;

void salvar_linhas()
{
    FILE *arquivo = fopen("dados/linhas.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nERRO: nao foi possivel abrir o arquivo para gravacao.\n");
        return;
    }

    fprintf(arquivo, "%d\n", proximo_id);

    for (int i = 0; i < quantidade_linhas; i++)
    {
        fprintf(arquivo, "%d;%s;%s\n", Linhas[i].id, Linhas[i].nome, Linhas[i].cor);
    }
    fclose(arquivo);
}

void carregar_linhas()
{
    FILE *arquivo = fopen("dados/linhas.txt", "r");

    quantidade_linhas = 0;
    proximo_id = 1;

    if (arquivo == NULL)
    {
        return;
    }
    if (fscanf(arquivo, "%d\n", &proximo_id) != 1)
    {
        proximo_id = 1;
    }
    while (quantidade_linhas < MAX_LINHAS &&
           fscanf(arquivo, "%d;%49[^;];%19[^\n]\n",
                  &Linhas[quantidade_linhas].id,
                  Linhas[quantidade_linhas].nome,
                  Linhas[quantidade_linhas].cor) == 3)
    {

        quantidade_linhas++;
    }
    fclose(arquivo);
}

void cadastrar_linhas()

{
    int quantidade = 0;

    system("clear");

    printf("====================================================\n");
    printf("                 PAGINA DE CADASTRO                 \n");
    printf("====================================================\n\n");

    if (quantidade_linhas == MAX_LINHAS)
    {
        printf("Limite de cadastro de linhas atingido.\n");
        pausar();
        return;
    }

    int cabe = MAX_LINHAS - quantidade_linhas;

    while (quantidade <= 0 || quantidade > cabe) // verifica se a quantidade nao excede o limite (MAX_LIMITES)
    {

        printf("Informe a quantidade de linhas que deseja cadastrar: ");

        if (scanf("%d", &quantidade) != 1) // verifica se a entrada foi um numero ou não
        {
            limpar_buffer();
            quantidade = 0;
            printf("Entrada invalida. Digite um numero.\n\n");
            continue;
        }

        limpar_buffer();

        if (quantidade <= 0 || quantidade > cabe)
        {
            printf("Quantidade invalida.\n\n");
        }
    }

    system("clear");

    int inicio = quantidade_linhas;

    for (int i = quantidade_linhas; i < quantidade_linhas + quantidade; i++) // cadastra as linhas
    {
        printf("----------------------------------------------------\n");
        printf("               Informações da Linha                 \n");
        printf("----------------------------------------------------\n\n");

        printf("Linha %d:\n", i + 1);
        printf("--------\n");

        Linhas[i].id = proximo_id;
        proximo_id++;

        char nome_valido = 0;

        while (!nome_valido)
        {

            printf("Nome: ");
            fgets(Linhas[i].nome, sizeof(Linhas[i].nome), stdin);

            if (Linhas[i].nome[0] == '\n' || !so_letras(Linhas[i].nome))
            {

                printf("Nome invalido. Digite apenas letras!\n\n");
            }
            else
            {
                remover_quebra(Linhas[i].nome);
                nome_valido = 1;
            }
        }

        char cor_valida = 0;

        while (!cor_valida)
        {

            printf("Cor: ");
            fgets(Linhas[i].cor, sizeof(Linhas[i].cor), stdin);

            if (Linhas[i].cor[0] == '\n' || !so_letras(Linhas[i].cor))
            {
                printf("Cor invalida. Digite apenas letras.\n\n");
            }
            else
            {
                remover_quebra(Linhas[i].cor);
                cor_valida = 1;
            }
        }
        system("clear");
    }

    quantidade_linhas += quantidade;
    salvar_linhas();

    printf("====================================================\n");
    printf("                LINHAS CADASTRADAS                  \n");
    printf("====================================================\n\n");

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");

    for (int i = inicio; i < quantidade_linhas; i++)
    {
        printf("| %-3d | %-25s | %-14s |\n", Linhas[i].id, Linhas[i].nome, Linhas[i].cor);
    }
    printf("+-----+---------------------------+----------------+\n\n");

    pausar();
    system("clear");
}

int buscar_posicao(int id)
{
    for (int i = 0; i < quantidade_linhas; i++)
    {
        if (Linhas[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void alterar_linhas()
{
    system("clear");

    printf("====================================================\n");
    printf("                ALTERACAO DE LINHAS                 \n");
    printf("====================================================\n\n");

    int id_linha;

    if (quantidade_linhas == 0)
    {

        printf("Nao existem linhas cadastradas.\n");
        pausar();
        system("clear");
        return;
    }

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");

    for (int i = 0; i < quantidade_linhas; i++)
    {
        printf("| %-3d | %-25s | %-14s |\n", Linhas[i].id, Linhas[i].nome, Linhas[i].cor);
    }
    printf("+-----+---------------------------+----------------+\n\n");

    int posicao = -1;

    while (posicao == -1)
    {

        printf("Informe o ID da linha que deseja alterar (ou 0 para cancelar): ");

        if (scanf("%d", &id_linha) != 1)
        {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero.\n\n");
            continue;
        }
        limpar_buffer();

        if (id_linha == 0)
        {
            printf("\nAlteracao cancelada.\n");
            pausar();
            system("clear");
            return;
        }

        posicao = buscar_posicao(id_linha);
        if (posicao == -1)
        {
            printf("Linha nao encontrada. Verifique o ID.\n\n");
        }
    }

    system("clear");

    char nome_valido = 0;

    while (!nome_valido)
    {

        printf("Novo nome: ");
        fgets(Linhas[posicao].nome, sizeof(Linhas[posicao].nome), stdin);

        if (Linhas[posicao].nome[0] == '\n' || !so_letras(Linhas[posicao].nome))
        {

            printf("Nome invalido. Digite apenas letras!\n\n");
        }
        else
        {
            remover_quebra(Linhas[posicao].nome);
            nome_valido = 1;
        }
    }

    char cor_valida = 0;

    while (!cor_valida)
    {

        printf("Nova cor: ");
        fgets(Linhas[posicao].cor, sizeof(Linhas[posicao].cor), stdin);

        if (Linhas[posicao].cor[0] == '\n' || !so_letras(Linhas[posicao].cor))
        {

            printf("Cor invalida. Digite apenas letras.\n\n");
        }
        else
        {
            remover_quebra(Linhas[posicao].cor);
            cor_valida = 1;
        }
    }
    system("clear");

    salvar_linhas();

    printf("====================================================\n");
    printf("                  LINHA ATUALIZADA                  \n");
    printf("====================================================\n\n");

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3d | %-25s | %-14s |\n", Linhas[posicao].id, Linhas[posicao].nome, Linhas[posicao].cor);
    printf("+-----+---------------------------+----------------+\n\n");

    pausar();
    system("clear");
}

void excluir_linhas()
{
    system("clear");

    printf("====================================================\n");
    printf("                 EXCLUSAO DE LINHAS                 \n");
    printf("====================================================\n\n");

    if (quantidade_linhas == 0)
    {

        printf("Nao existem linhas cadastradas.\n");
        pausar();
        system("clear");
        return;
    }

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");

    for (int i = 0; i < quantidade_linhas; i++)
    {
        printf("| %-3d | %-25s | %-14s |\n", Linhas[i].id, Linhas[i].nome, Linhas[i].cor);
    }
    printf("+-----+---------------------------+----------------+\n\n");

    int id_linha;
    int posicao = -1;

    while (posicao == -1)
    {

        printf("Informe o ID da linha que deseja excluir (ou 0 para cancelar): ");

        if (scanf("%d", &id_linha) != 1)
        {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero.\n\n");
            continue;
        }
        limpar_buffer();

        if (id_linha == 0)
        {
            printf("\nExclusao cancelada.\n");
            pausar();
            system("clear");
            return;
        }

        posicao = buscar_posicao(id_linha);
        if (posicao == -1)
        {
            printf("Linha nao encontrada. Verifique o ID.\n\n");
        }
    }

    system("clear");

    printf("====================================================\n");
    printf("                 LINHA SELECIONADA                  \n");
    printf("====================================================\n\n");

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3d | %-25s | %-14s |\n", Linhas[posicao].id, Linhas[posicao].nome, Linhas[posicao].cor);
    printf("+-----+---------------------------+----------------+\n\n");

    char resposta = 0;

    while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N')
    {

        printf("Tem certeza que deseja excluir essa linha? (s/n): ");
        scanf(" %c", &resposta);
        limpar_buffer();

        if (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N')
        {

            printf("Resposta invalida. Digite S ou N.\n\n");
        }
    }

    if (resposta == 'N' || resposta == 'n')
    {

        printf("\nExclusao cancelada.\n");
        pausar();
        system("clear");
        return;
    }

    for (int i = posicao; i < quantidade_linhas - 1; i++)
    {
        Linhas[i] = Linhas[i + 1];
    }

    quantidade_linhas--;
    salvar_linhas();

    printf("\nLinha excluida com sucesso.\n");

    pausar();
    system("clear");
}

void visualizar_linhas()
{
    system("clear");

    printf("====================================================\n");
    printf("                   LINHAS ATIVAS                    \n");
    printf("====================================================\n\n");

    if (quantidade_linhas == 0)
    {
        printf("Nao existem linhas cadastradas.\n");
        pausar();
        system("clear");
        return;
    }

    printf("+-----+---------------------------+----------------+\n");
    printf("| %-3s | %-25s | %-14s |\n", "ID", "NOME DA LINHA", "COR");
    printf("+-----+---------------------------+----------------+\n");

    for (int i = 0; i < quantidade_linhas; i++)
    {
        printf("| %-3d | %-25s | %-14s |\n", Linhas[i].id, Linhas[i].nome, Linhas[i].cor);
    }
    printf("+-----+---------------------------+----------------+\n");
    printf("Total de linhas: %d\n\n", quantidade_linhas);

    pausar();
    system("clear");
}