#ifndef FUNCOES_LEITURA_H
#define FUNCOES_LEITURA_H

#include "estruturas.h"
#include "ordenacao_busca.h"
#include "funcoes_operacoes.h"

int le_registro_stdin(Registro *registro);
Registro Ler_registros_removidos(FILE *ArquivoBinario, char *SemDados);
FILE *lerArquivoCSV(char *nomeArquivo);
FILE *lerArquivoBinario(char *nomeArquivo);
FILE *lerEscreverArquivoBinario(char *nomeArquivo);
void LerCampoVariado(char **Campo, int *tamanhoCampo, FILE *arquivo, char* SemDados);
void LerCamposVariadosNaoNulos(char **Campo, int tamanho, FILE *arquivo);
void LeCabecalho(FILE *ArquivoBinario, Cabecalho *cabecalho);
Registro Ler_registros(FILE *ArquivoBinario, char *SemDados);
Registro Ler_registros_ID(FILE *ArquivoBinario);
Registro Ler_registros_debug(FILE *ArquivoBinario, char *SemDados);
int verifica_id_Repetido(int *lista_ids, int lista_tam, int id_procurado);

#endif
