#ifndef B_TREE_H
#define B_TREE_H

#include "funcoes_escrita.h"
#include "funcoes_leitura.h"
#include "funcoes_operacoes.h"

#define ORDEM 4
#define MAX_CHAVES (ORDEM - 1)
#define MAX_PONTEIROS ORDEM
#define TAMANHO_NO 60
#define TAMANHO_CABECALHO 60

// Estrutura do nó da árvore-B
// typedef struct {
//     int alturaNo;
//     int nroChaves;
//     long long chaves[MAX_CHAVES];
//     int refs[MAX_CHAVES];
//     int ponteiros[MAX_PONTEIROS];
// } BTreeNode;

// Estrutura do nó da árvore-B
void create_indexB_sem_leitura(char *nomeArquivoEntrada, char *nomeArquivoSaida);
#endif
