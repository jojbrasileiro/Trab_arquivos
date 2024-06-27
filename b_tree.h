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

void create_indexB(char *nomeArquivoEntrada, char *nomeArquivoSaida);
#endif
