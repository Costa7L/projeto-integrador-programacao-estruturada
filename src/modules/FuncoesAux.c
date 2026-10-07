#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void limpar_buffer() /*limpa o buffer deixado pelo scanf*/
{

    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int so_letras(char texto[]) /*verifica se o conteudo digitado foi apenas letras*/
{

    for (int i = 0; texto[i] != '\n' && texto[i] != '\0'; i++)
    {

        if (!isalpha((unsigned char)texto[i]) && texto[i] != ' ')
            return 0;
    }

    return 1;
}

void remover_quebra(char texto[]) /*substitui \n pelo caractere nulo '\0'*/

{

    texto[strcspn(texto, "\n")] = '\0';
}

void pausar()
{

    printf("\nPressione ENTER para continuar...");
    getchar();
}