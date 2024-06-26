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

typedef struct
{
    int alturaNo;
    int nroChaves;
    int c1;
    long pr1;
    int c2;
    long pr2;
    int c3;
    long pr3;
    int p1;
    int p2;
    int p3;
    int p4;
    int RRNAtual;
} BTreeNode;

// Estrutura do cabeçalho do arquivo de índice
typedef struct
{
    char status;
    int noRaiz;
    int proxRRN;
    int nroChaves;
    char lixo[47];
} Header;

typedef struct
{
    int chave;
    long byteOffSet;
    int RRNEsquerda;
    int RRNDireita;
    int AlturaNo;
} dados;
#endif