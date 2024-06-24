#ifndef SELECT_WHERE_H
#define SELECT_WHERE_H

#include "funcoes_leitura.h"
#include "funcoes_escrita.h"
#include "funcoes_operacoes.h"

void zera_registro(Registro *registro);

int determina_campo(char *campo, Registro *registro);

int compararRegistros(Registro *registro1, Registro *registro2);

void select_where(char *nomeArquivoEntrada);


#endif
