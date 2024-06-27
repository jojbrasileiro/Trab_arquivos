#ifndef FUNCOES_LEITURA_H
#define FUNCOES_LEITURA_H

#include "estruturas.h"
#include "funcoes_operacoes.h"

int LeRegistroStdin(Registro *registro);
Registro LerRegistrosRemovidos(FILE *ArquivoBinario, char *SemDados);
FILE *LerArquivoCSV(char *nomeArquivo);
FILE *LerArquivoBinario(char *nomeArquivo);
FILE *LerEscreverArquivoBinario(char *nomeArquivo);
void LerCampoVariado(char **Campo, int *tamanhoCampo, FILE *arquivo, char *SemDados);
void LerCamposVariadosNaoNulos(char **Campo, int tamanho, FILE *arquivo);
void LeCabecalho(FILE *ArquivoBinario, Cabecalho *cabecalho);
Registro LerRegistros(FILE *ArquivoBinario, char *SemDados);
Registro LerRegistrosID(FILE *ArquivoBinario);
int BuscaId(const char *filename, int idBuscado);
void ImprimirListaEspacoDisponivel(EspacoDisponivel *lista);
void ImprimeRegistro(Registro registro);
void ImprimeCabecalho(Cabecalho cabecalho);
void ImprimeRegistroFunc2(Registro registro);

#endif
