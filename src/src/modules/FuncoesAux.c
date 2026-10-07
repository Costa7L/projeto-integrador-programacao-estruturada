#include <stdio.h>
#include <stdlib.h>

void limpar_buffer()
{

    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}