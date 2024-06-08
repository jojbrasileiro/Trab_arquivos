#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição da estrutura de cabeçalho
typedef struct
{
    char status;
    long topo;
    long proxByteOffset;
    int nroRegArq;
    int nroRegRem;
} Cabecalho;

// Definição da estrutura de registros
typedef struct
{
    char removido;
    int tamanhoRegistro;
    long Prox;
    int id;
    int idade;
    int tamNomeJog;
    char *nomeJogador;
    int tamNacionalidade;
    char *nacionalidade;
    int tamNomeClube;
    char *nomeClube;
} Registro;

typedef struct
{
    int id;
    int byteOffset;
} Index;

typedef struct EspacoDisponivel
{
    int tamanho;
    long offset;
    struct EspacoDisponivel *prox;
} EspacoDisponivel;

#endif