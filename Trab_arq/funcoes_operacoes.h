#ifndef FUNCOES_OPERACOES_H
#define FUNCOES_OPERACOES_H

#include "estruturas.h"

int VerificaNulo(char **Campo, char *string);
int AlocaCamposVariados(char **Campo, char *token);
void binarioNaTela(char *nomeArquivoBinario);
void processarCampoInt(Registro *registro, char *token, int *campo);
void processarCampoString(Registro *registro, char *token, int *tamanhoCampo, char **campo);
void scan_quote_string(char *str);
void zera_registro(Registro *registro);
int determina_campo(char *campo, Registro *registro);
int compararRegistros(Registro *registro1, Registro *registro2);

#endif