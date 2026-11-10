#include <stdio.h>
#include <stdlib.h>

#include "estacoes.h"
#include "FuncoesAux.h"

estacao estacoes[MAX_ESTACOES];
int proximo_id_estacao = 1;
int quantidade_estacao = 0;

void salvar_estacoes()
{
    FILE *arquivo = fopen("dados/estacoes.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nERRO: Não foi possivel abrir o arquivo para gravação.\n");
        return;
    }

    fprintf(arquivo, "%d\n", proximo_id_estacao);

    for (int i = 0; i < quantidade_estacao; i++)
    {

        fprintf(arquivo, "%d;%s\n", estacoes[i].id, estacoes[i].nome);
    }

    fclose(arquivo);
}

void carregar_estacoes()
{

    FILE *arquivo = fopen("dados/estacoes.txt", "r");

    quantidade_estacao = 0;
    proximo_id_estacao = 1;

    if (arquivo == NULL)
    {
        return;
    }

    if (fscanf(arquivo, "%d\n", &proximo_id_estacao) != 1)
    {
        proximo_id_estacao = 1;
    }

    while (quantidade_estacao < MAX_ESTACOES && fscanf(arquivo, "%d;%49[^\n]\n", &estacoes[quantidade_estacao].id, estacoes[quantidade_estacao].nome) == 2)
    {
        quantidade_estacao++;
    }
    fclose(arquivo);
}

void cadastrar_estacoes()
{

    int quantidadeEst = 0;

    system("clear");

    printf("====================================================\n");
    printf("            PAGINA DE CADASTRO (ESTACOES)           \n");
    printf("====================================================\n");

    if (quantidade_estacao >= MAX_ESTACOES)
    {
        printf("Limite de cadastro de estacoes atingido.\n");
        pausar();
        return;
    }

    int cabeEst = MAX_ESTACOES - quantidade_estacao;

    while (quantidadeEst <= 0 || quantidadeEst > cabeEst)
    {

        printf("Informe a quantidade de estacoes que deseja cadastrar: ");

        if (scanf("%d", &quantidadeEst) != 1)
        {

            limpar_buffer();
            quantidadeEst = 0;
            printf("Entrada invalida. Digite um numero.\n\n");
            continue;
        }
        limpar_buffer();

        if (quantidadeEst <= 0 || quantidadeEst > cabeEst)
        {
            printf("Quantidade invalida.\n\n");
        }
    }

    system("clear");

    int inicio = quantidade_estacao;

    for (int i = quantidade_estacao; i < quantidade_estacao + quantidadeEst; i++)
    {
        printf("----------------------------------------------------\n");
        printf("            Informacoes das estacoes            \n");
        printf("----------------------------------------------------\n\n");

        printf("Estacao %d:\n", i + 1);
        printf("--------\n");

        estacoes[i].id = proximo_id_estacao;
        proximo_id_estacao++;

        char nome_valido = 0;

        while (!nome_valido)
        {

            printf("Nome: ");
            fgets(estacoes[i].nome, sizeof(estacoes[i].nome), stdin);

            if (estacoes[i].nome[0] == '\n' || !so_letras(estacoes[i].nome))
            {
                printf("Nome invalido. Digite apenas letras!\n\n");
            }
            else
            {
                remover_quebra(estacoes[i].nome);
                nome_valido = 1;
            }
        }
        system("clear");
    }

    quantidade_estacao += quantidadeEst;
    salvar_estacoes();
    printf("====================================================\n");
    printf("            ESTACOES CADASTRADAS            \n");
    printf("====================================================\n\n");

    printf("+-----+------------------------+\n");
    printf("| %-3s | %-25s |\n", "ID", "NOME DA ESTACAO");
    printf("+-----+------------------------+\n");

    for (int i = inicio; i < quantidade_estacao; i++)
    {

        printf("| %-3d | %-25s |\n", estacoes[i].id, estacoes[i].nome);
    }

    printf("+-----+------------------------+\n");

    pausar();
    system("clear");
}

int buscar_posicao_estacoes(int id)
{

    for (int i = 0; i < quantidade_estacao; i++)
    {

        if (estacoes[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void alterar_estacoes()
{

    system("clear");

    printf("=================================================\n");
    printf("            ALTERAÇÃO DE ESTAÇÕES           \n");
    printf("=================================================\n\n");

    int id_estacoes;

    if (quantidade_estacao == 0)
    {
        printf("Não existem estações cadastradas.\n");
        pausar();
        system("clear");
        return;
    }

    printf("+-----+------------------------------\n");
    printf("| %-3s | %-25s |\n", "ID", "ESTAÇÕES");
    printf("+-----+------------------------------\n");

    for (int i = 0; i < quantidade_estacao; i++)
    {
        printf("| %-3d | %-25s |\n", estacoes[i].id, estacoes[i].nome);
    }
    printf("+-----+------------------------------\n\n");

    int posicao = -1;

    while (posicao == -1)
    {
        printf("Informe o Id da estação que deseja alterar (ou 0 para cancelar): ");

        if (scanf("%d", &id_estacoes) != 1)
        {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero.\n\n");
            continue;
        }
        limpar_buffer();

        if (id_estacoes == 0)
        {
            printf("\nAlteração cancelada.\n");
            pausar();
            system("clear");
            return;
        }

        posicao = buscar_posicao_estacoes(id_estacoes);

        if (posicao == -1)
        {
            printf("Linha não encontrada. Verifique o ID.\n\n");
        }
    }

    system("clear");

    char nome_valido = 0;

    while (!nome_valido)
    {
        printf("novo nome: ");
        fgets(estacoes[posicao].nome, sizeof(estacoes[posicao].nome), stdin);

        if (estacoes[posicao].nome[0] == '\n' || !so_letras(estacoes[posicao].nome))
        {

            printf("Nome inválido. Digite apenas letras!\n\n");
        }
        else
        {
            remover_quebra(estacoes[posicao].nome);
            nome_valido = 1;
        }
    }
    system("clear");
    salvar_estacoes();

    printf("=================================================\n");
    printf("            ESTAÇÕES CADASTRADAS            \n");
    printf("=================================================\n");

    printf("+-----+------------------------------+\n");
    printf("| %-3s | %-25s |\n", "ID", "ESTAÇÕES");
    printf("+-----+------------------------------+\n");
    printf("| %-3d | %-25s |\n", estacoes[posicao].id, estacoes[posicao].nome);
    printf("+-----+------------------------------+\n\n");

    pausar();
    system("clear");
}

void excluir_estacoes()
{

    system("clear");

    printf("=================================================\n");
    printf("            EXCLUSÃO DE ESTAÇÕES            \n");
    printf("=================================================\n\n");

    if (quantidade_estacao == 0)
    {
        printf("Não existem linhas cadastradas.\n");
        pausar();
        system("clear");
        return;
    }
    printf("+-----+------------------------------+\n");
    printf("| %-3s | %-25s |\n", "ID", "ESTAÇÕES");
    printf("+-----+------------------------------+\n");

    for (int i = 0; i < quantidade_estacao; i++)
    {
        printf("| %-3d | %-25s |\n", estacoes[i].id, estacoes[i].nome);
    }
    printf("+-----+------------------------------+\n\n");

    int id_estacoes;
    int posicao = -1;

    while (posicao == -1)
    {

        printf("Informe o ID da estação que deseja excluir (ou 0 para cancelar): ");

        if (scanf("%d", &id_estacoes) != 1)
        {
            limpar_buffer();
            printf("entrada Invalida. Digite um numero.\n\n");
            continue;
        }
        limpar_buffer();

        if (id_estacoes == 0)
        {
            printf("\nExclusao cancelada.\n");
            pausar();
            system("clear");
            return;
        }

        posicao = buscar_posicao_estacoes(id_estacoes);

        if (posicao == -1)
        {
            printf("Linha nao encontrada. Verifique o ID.\n\n");
        }
    }

    system("clear");

    printf("=================================================\n");
    printf("            ESTAÇÃO SELECIONADA             \n");
    printf("================================================\n\n");

    printf("+-----+------------------------------+\n");
    printf("| %-3s | %-25s |\n", "ID", "ESTAÇÕES");
    printf("+-----+-----------------------------+\n");
    printf("| %-3d | %-25s |\n", estacoes[posicao].id, estacoes[posicao].nome);
    printf("+-----+-----------------------------+\n\n");

    char resposta = 0;

    while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N')
    {

        printf("Tem certeza que deseja excluir essa estação? [S/N]: ");
        scanf("%c", &resposta);
        limpar_buffer();

        if (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N')
        {
            printf("Resposta invalida. Digite S ou N.\n\n");
        }
    }
    if (resposta == 'N' || resposta == 'n')
    {
        printf("\nExclusão cancelada.\n");
        pausar();
        system("clear");
        return;
    }

    for (int i = posicao; i < quantidade_estacao - 1; i++)
    {
        estacoes[i] = estacoes[i + 1];
    }

    quantidade_estacao--;
    salvar_estacoes();

    printf("\nEstação excluida com sucesso.\n");

    pausar();
    system("clear");
}

void visualizar_estacoes()
{

    system("clear");

    printf("================================================\n");
    printf("            ESTAÇÕES ATIVAS             \n");
    printf("================================================\n\n");

    if (quantidade_estacao == 0)
    {
        printf("Não existem estações cadastradas.\n");
        pausar();
        system("clear");
        return;
    }

    printf("+-----+------------------------------+\n");
    printf("| %-3s | %-25s |\n", "ID", "ESTAÇÕES");
    printf("+-----+------------------------------+\n");

    for (int i = 0; i < quantidade_estacao; i++)
    {
        printf("| %-3d | %-25s |\n", estacoes[i].id, estacoes[i].nome);
    }
    printf("+-----+------------------------------+\n");
    printf("Total de estacoes: %d\n\n", quantidade_estacao);

    pausar();
    system("clear");
}
