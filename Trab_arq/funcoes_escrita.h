#ifndef FUNCOES_ESCRITA_H
#define FUNCOES_ESCRITA_H

#include "estruturas.h"

void ImprimeRegistroFunc2(Registro registro);
void EscreveCabecalho(FILE *arquivo, Cabecalho cabecalho);
FILE *criarArquivoIndice(char *nomeArquivo);
FILE *criarArquivoBinario(char *nomeArquivo);
void ImprimeCabecalho(Cabecalho cabecalho);
void ImprimeRegistro(Registro registro);
void EscreveRegistro(FILE *arquivo, Registro registro);
void EscreveRegistroIndice(FILE *arquivo, int ID, int byteoffset);
void RemoveRegistro(FILE *arquivo,int tam_reg,Cabecalho Cabecalho);
#endif
