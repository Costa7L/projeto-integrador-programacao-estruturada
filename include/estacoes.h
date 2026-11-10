#ifndef estacoes_h_include
#define estacoes_h_include

#define MAX_ESTACOES 35

typedef struct
{

    int id;
    char nome[50];

} estacao;

void salvar_estacoes();
void carregar_estacoes();
void cadastrar_estacoes();
int buscar_posicao_estacoes(int id);
void alterar_estacoes();
void excluir_estacoes();
void visualizar_estacoes();

#endif // estacoes_h_includes