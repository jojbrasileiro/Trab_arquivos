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

void inicializaNo(BTreeNode *node);
void AtualizaFilho(BTreeNode *node);
void inicializaCabecalho(Header *header);
void escreveCabecalhoB(FILE *arquivo, Header *header);
void ImprimeCabecalhoB(Header *Header);
void leCabecalhoB(FILE *arquivo, Header *header);
void escreveNo(FILE *arquivo, BTreeNode *node, int RRN);
BTreeNode leNo(FILE *arquivo, int RRN);
void imprimirNo(BTreeNode *no);
int conta_cria(BTreeNode *no);
dados split(BTreeNode *esquerda, dados dadosInsercao, BTreeNode *direita);
dados insereNaoCheio(FILE *arquivo, Header *header, BTreeNode *no_atual, dados dadosInsercao);
void insere(FILE *arquivo, Header *header, int chave, long byteOffSet);
long busca_TreeB(FILE* ArquivoIndex, int noAtual, int id);
void create_indexB(char *nomeArquivoEntrada, char *nomeArquivoSaida);
#endif
