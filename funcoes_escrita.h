#ifndef FUNCOES_ESCRITA_H
#define FUNCOES_ESCRITA_H

#include "estruturas.h"

void EscreveLixo(FILE *arquivo, int num);
void EscreveCabecalho(FILE *arquivo, Cabecalho cabecalho);
FILE *CriarArquivoIndice(char *nomeArquivo);
FILE *CriarArquivoBinario(char *nomeArquivo);
FILE *CriarArquivoIndiceB(char *nomeArquivo);
FILE *LerArquivoIndiceB(char *nomeArquivo);
void EscreveRegistro(FILE *arquivo, Registro registro);
void EscreveRegistroIndice(FILE *arquivo, int ID, int byteoffset);
void RemoveRegistro(FILE *arquivo, int tam, long int byteOffSet);
void InserirEspacoDisponivel(EspacoDisponivel **lista, int tamanho, long offset);
void LiberarListaEspacoDisponivel(EspacoDisponivel *lista);
void AtualizaCabecalho(FILE *ArquivoBinario, Cabecalho cabecalho, long int byteOffSet, int remocoes);

#endif
