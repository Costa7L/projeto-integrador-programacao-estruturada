#ifndef linhas_h_include
#define linhas_h_include

#define MAX_LINHAS 20

struct Linhas
{

    int id;
    char nome[50];
    char cor[20];
};

extern struct Linhas Linhas[MAX_LINHAS];

extern int quantidade_linhas;

void cadastrar_linhas();

#endif // linhas_h_include