#include "funcoes_escrita.h"

// função que completa a diferença de tamanho dos arquivos com lixo
void EscreveLixo(FILE *arquivo, int num)
{
    for (int i = 0; i < num; i++)
    {
        fwrite("$", sizeof(char), 1, arquivo);
    }
}

// função que imprime de acordo com as especificações da funcionalidade 2
void ImprimeRegistroFunc2(Registro registro)
{
    printf("Nome do Jogador: %s\n", registro.nomeJogador);
    printf("Nacionalidade do Jogador: %s\n", registro.nacionalidade);
    printf("Clube do Jogador: %s\n", registro.nomeClube);
    printf("\n");
}

// função que escreve o cabeçalho no inicio do arquvio
void EscreveCabecalho(FILE *arquivo, Cabecalho cabecalho)
{
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.topo, sizeof(long), 1, arquivo);
    fwrite(&cabecalho.proxByteOffset, sizeof(long), 1, arquivo);
    fwrite(&cabecalho.nroRegArq, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroRegRem, sizeof(int), 1, arquivo);
}

// função que inicia o arquivo binario no modo escrita
FILE *CriarArquivoIndice(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }

    char status = '1';

    fwrite(&status, sizeof(char), 1, arquivo);

    return arquivo;
}

// função que inicia o arquivo binario no modo escrita
FILE *CriarArquivoIndiceB(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb+");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }

    char status = '1';

    fwrite(&status, sizeof(char), 1, arquivo);

    return arquivo;
}

FILE *LerArquivoIndiceB(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
    }

    return arquivo;
}

// função que inicia o arquivo binario no modo escrita binaria e ja escreve o cabacalho
FILE *CriarArquivoBinario(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(1);
    }

    Cabecalho cabecalho = {
        .status = '1',
        .topo = -1,
        .proxByteOffset = 0,
        .nroRegArq = 0,
        .nroRegRem = 0};

    EscreveCabecalho(arquivo, cabecalho);

    return arquivo;
}
// Função que escreve no arquivo de indice
void EscreveRegistroIndice(FILE *arquivo, int ID, int byteoffset)
{
    fwrite(&ID, sizeof(int), 1, arquivo);
    fwrite(&byteoffset, sizeof(int), 1, arquivo);
}

// Funçaõ que remove lógicamente o registro
void RemoveRegistro(FILE *arquivo, int tam, long int byteOffSet)
{
    char removido = '1';
    fwrite(&removido, sizeof(char), 1, arquivo);
    fwrite(&tam, sizeof(int), 1, arquivo);
    fwrite(&byteOffSet, sizeof(long), 1, arquivo);
}

// Função para inserir um espaço na lista de espaços disponíveis
void InserirEspacoDisponivel(EspacoDisponivel **lista, int tamanho, long offset)
{
    EspacoDisponivel *novo = (EspacoDisponivel *)malloc(sizeof(EspacoDisponivel));
    novo->tamanho = tamanho;
    novo->offset = offset;
    novo->prox = NULL;

    if (*lista == NULL || (*lista)->tamanho > tamanho)
    {
        novo->prox = *lista;
        *lista = novo;
    }
    else
    {
        EspacoDisponivel *atual = *lista;
        while (atual->prox != NULL && atual->prox->tamanho <= tamanho)
        {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

// Função para liberar a memória da lista de espaços disponíveis
void LiberarListaEspacoDisponivel(EspacoDisponivel *lista)
{
    EspacoDisponivel *atual = lista;
    while (atual != NULL)
    {
        EspacoDisponivel *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

// Função para atualizar o cabeçalho depois da remoção
void AtualizaCabecalho(FILE *ArquivoBinario, Cabecalho cabecalho, long int byteOffSet, int remocoes)
{
    cabecalho.topo = byteOffSet;
    cabecalho.nroRegArq -= remocoes;
    cabecalho.nroRegRem += remocoes;
    EscreveCabecalho(ArquivoBinario, cabecalho);
}
// função que escreve o registro no arquivo
void EscreveRegistro(FILE *arquivo, Registro registro)
{
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