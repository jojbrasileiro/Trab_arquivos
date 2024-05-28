#ifndef FUNCOES_LEITURA_H
#define FUNCOES_LEITURA_H

#include "estruturas.h"

FILE *lerArquivoCSV(char *nomeArquivo);
FILE *lerArquivoBinario(char *nomeArquivo);
FILE *lerEscreverArquivoBinario(char *nomeArquivo);
void LerCampoVariado(char **Campo, int *tamanhoCampo, FILE *arquivo, char* SemDados);
void LerCamposVariadosNaoNulos(char **Campo, int tamanho, FILE *arquivo);
void LeCabecalho(FILE *ArquivoBinario, Cabecalho *cabecalho);
Registro Ler_registros(FILE *ArquivoBinario, char *SemDados);
Registro Ler_registros_ID(FILE *ArquivoBinario);

#endif
