#include "funcoes_escrita.h"

//função que imprime de acordo com as especificações da funcionalidade 2
void ImprimeRegistroFunc2(Registro registro) {
    printf("Nome do Jogador: %s\n", registro.nomeJogador);
    printf("Nacionalidade do Jogador: %s\n", registro.nacionalidade);
    printf("Clube do Jogador: %s\n", registro.nomeClube);
    printf("\n");
}

//função que escreve o cabeçalho no inicio do arquvio
void EscreveCabecalho(FILE *arquivo, Cabecalho cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.topo, sizeof(long), 1, arquivo);
    fwrite(&cabecalho.proxByteOffset, sizeof(long), 1, arquivo);
    fwrite(&cabecalho.nroRegArq, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroRegRem, sizeof(int), 1, arquivo);
}

//função que inicia o arquivo binario no modo escrita
FILE *criarArquivoIndice(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }

    char status = '1';
    
    fwrite(&status, sizeof(char), 1, arquivo);

    return arquivo;
}

//função que inicia o arquivo binario no modo escrita binaria e ja escreve o cabacalho
FILE *criarArquivoBinario(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }

    Cabecalho cabecalho = {
        .status = '1',
        .topo = -1,
        .proxByteOffset = 0,
        .nroRegArq = 0,
        .nroRegRem = 0
    };

    EscreveCabecalho(arquivo, cabecalho);

    return arquivo;
}

//função que imprime o cabeçalho para fins de correção
void ImprimeCabecalho(Cabecalho cabecalho) {
    printf("Status: %c\n", cabecalho.status);
    printf("Topo: %ld\n", cabecalho.topo);
    printf("Próximo Byte Offset: %ld\n", cabecalho.proxByteOffset);
    printf("Número de Registros no Arquivo: %d\n", cabecalho.nroRegArq);
    printf("Número de Registros Removidos: %d\n", cabecalho.nroRegRem);
}

//função que imprime o registro completo para fins de correção 
void ImprimeRegistro(Registro registro) {
    printf("Removido: %c\n", registro.removido);
    printf("Tamanho do Registro: %d\n", registro.tamanhoRegistro);
    printf("Prox: %ld\n", registro.Prox);
    printf("ID: %d\n", registro.id);
    printf("Idade: %d\n", registro.idade);
    printf("Tamanho do Nome do Jogador: %d\n", registro.tamNomeJog);
    printf("Nome do Jogador: %s\n", registro.nomeJogador);
    printf("Tamanho da Nacionalidade: %d\n", registro.tamNacionalidade);
    printf("Nacionalidade: %s\n", registro.nacionalidade);
    printf("Tamanho do Nome do Clube: %d\n", registro.tamNomeClube);
    printf("Nome do Clube: %s\n", registro.nomeClube);
}

//função que escreve o registro no arquivo
void EscreveRegistro(FILE *arquivo, Registro registro){
    fwrite(&registro.removido, sizeof(char), 1, arquivo);
    fwrite(&registro.tamanhoRegistro, sizeof(int), 1, arquivo);
    fwrite(&registro.Prox, sizeof(long), 1, arquivo);
    fwrite(&registro.id, sizeof(int), 1, arquivo);
    fwrite(&registro.idade, sizeof(int), 1, arquivo);
    fwrite(&registro.tamNomeJog, sizeof(int), 1, arquivo);
    fwrite(registro.nomeJogador, sizeof(char), registro.tamNomeJog, arquivo);
    fwrite(&registro.tamNacionalidade, sizeof(int), 1, arquivo);
    fwrite(registro.nacionalidade, sizeof(char), registro.tamNacionalidade, arquivo);
    fwrite(&registro.tamNomeClube, sizeof(int), 1, arquivo);
    fwrite(registro.nomeClube, sizeof(char), registro.tamNomeClube, arquivo);
}

void EscreveRegistroIndice(FILE *arquivo, int ID, int byteoffset){
    fwrite(&ID, sizeof(int), 1, arquivo);
    fwrite(&byteoffset, sizeof(int), 1, arquivo);
}