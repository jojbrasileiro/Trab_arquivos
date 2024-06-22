#ifndef B_TREE_H
#define B_TREE_H

#include "funcoes_escrita.h"
#include "funcoes_leitura.h"
#include "funcoes_operacoes.h"

#define ORDEM 4
#define MAX_CHAVES (ORDEM - 1)
#define MAX_PONTEIROS ORDEM
#define TAMANHO_NO (sizeof(BTreeNode))
#define TAMANHO_CABECALHO 60

// Estrutura do nó da árvore-B
// typedef struct {
//     int alturaNo;
//     int nroChaves;
//     long long chaves[MAX_CHAVES];
//     int refs[MAX_CHAVES];
//     int ponteiros[MAX_PONTEIROS];
// } BTreeNode;
typedef struct
{
    int alturaNo;
    int nroChaves;
    int c1;
    long int pr1;
    int c2;
    long int pr2;
    int c3;
    long int pr3;
    int p1;
    int p2;
    int p3;
    int p4;
} BTreeNode;

// Estrutura do cabeçalho do arquivo de índice
typedef struct
{
    char status;
    int noRaiz;
    int proxRRN;
    int nroChaves;
    char lixo[47];
} Header;

// Estrutura do nó da árvore-B
void create_indexB_sem_leitura(char *nomeArquivoEntrada, char *nomeArquivoSaida);
#endif
