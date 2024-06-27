#ifndef INSERT_INTO
#define INSERT_INTO

#include "funcoes_escrita.h"
#include "funcoes_leitura.h"
#include "funcoes_operacoes.h"
#include "create_index.h"
#include "b_tree.h"

int insert_into(char *nomeArquivoEntrada, char *nomeArquivoSaida);
int insert_intoB(char *nomeArquivoEntrada, char *nomeArquivoIndice);

#endif