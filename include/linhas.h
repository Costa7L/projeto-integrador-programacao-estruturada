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

void salvar_linhas();
void carregar_linhas();
void cadastrar_linhas();
int buscar_posicao(int id);
void alterar_linhas();
void excluir_linhas();
void visualizar_linhas();

#endif // linhas_h_include