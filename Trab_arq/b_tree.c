#include "b_tree.h"

// Função para inicializar um novo nó da árvore-B
void inicializaNo(BTreeNode *node)
{
    node->alturaNo = 0;
    node->nroChaves = 0;
    node->c1 = -1;
    node->pr1 = -1;
    node->c2 = -1;
    node->pr2 = -1;
    node->c2 = -1;
    node->pr3 = -1;
    node->p1 = -1;
    node->p2 = -1;
    node->p3 = -1;
    node->p4 = -1;
}

// Função para inicializar o cabeçalho
void inicializaCabecalho(Header *header)
{
    header->status = '0';
    header->noRaiz = -1;
    header->proxRRN = 0;
    header->nroChaves = 0;
    memset(header->lixo, '$', 47);
}
// Função para escrever o cabeçalho no arquivo indicie
void escreveCabecalhoB(FILE *arquivo, Header *header)
{
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&header->status, sizeof(char), 1, arquivo);
    fwrite(&header->noRaiz, sizeof(int), 1, arquivo);
    fwrite(&header->proxRRN, sizeof(int), 1, arquivo);
    fwrite(&header->nroChaves, sizeof(int), 1, arquivo);
    fwrite(&header->lixo, sizeof(char), 47, arquivo);
}
// Função para imprimir o cabeçalho do arquivo indicie
void ImprimeCabecalhoB(Header *Header)
{
    printf("Status: %c\n", Header->status);
    printf("Nó raiz: %d\n", Header->noRaiz);
    printf("Próximo RRN: %d\n", Header->proxRRN);
    printf("Número de Chaves: %d\n", Header->nroChaves);
    printf("Tam dos Demais Bytes: %ld\n\n", strlen(Header->lixo));
}
// Função para ler o cabeçalho do arquivo indicie
void leCabecalhoB(FILE *arquivo, Header *header)
{
    fseek(arquivo, 0, SEEK_SET);
    fread(&header->status, sizeof(char), 1, arquivo);
    fread(&header->noRaiz, sizeof(int), 1, arquivo);
    fread(&header->proxRRN, sizeof(int), 1, arquivo);
    fread(&header->nroChaves, sizeof(int), 1, arquivo);
    fread(&header->lixo, sizeof(char), 47, arquivo);
}

// Função para escrever um nó no arquivo
void escreveNo(FILE *arquivo, BTreeNode node, int RRN)
{
    fseek(arquivo, TAMANHO_CABECALHO + RRN * TAMANHO_NO, SEEK_SET);
    fwrite(&node.alturaNo, sizeof(int), 1, arquivo);
    fwrite(&node.nroChaves, sizeof(int), 1, arquivo);
    fwrite(&node.c1, sizeof(int), 1, arquivo);
    fwrite(&node.pr1, sizeof(long), 1, arquivo);
    fwrite(&node.c2, sizeof(int), 1, arquivo);
    fwrite(&node.pr2, sizeof(long), 1, arquivo);
    fwrite(&node.c3, sizeof(int), 1, arquivo);
    fwrite(&node.pr3, sizeof(long), 1, arquivo);
    fwrite(&node.p1, sizeof(int), 1, arquivo);
    fwrite(&node.p2, sizeof(int), 1, arquivo);
    fwrite(&node.p3, sizeof(int), 1, arquivo);
    fwrite(&node.p4, sizeof(int), 1, arquivo);
}

// Função para ler um nó do arquivo
void leNo(FILE *arquivo, BTreeNode *node, int RRN)
{
    fseek(arquivo, TAMANHO_CABECALHO + RRN * TAMANHO_NO, SEEK_SET);
    printf("ByteOffSet Inicial Antes de ler o no inserido indice:%ld\n\n", ftell(arquivo));
    fread(&node->alturaNo, sizeof(int), 1, arquivo);
    fread(&node->nroChaves, sizeof(int), 1, arquivo);
    printf("ByteOffSet Inicial Antes de ler a chave 1:%ld\n\n", ftell(arquivo));
    fread(&node->c1, sizeof(int), 1, arquivo);
    printf("Chave C1: %d\n\n", node->c1);
    fread(&node->pr1, sizeof(long), 1, arquivo);
    fread(&node->c2, sizeof(int), 1, arquivo);
    fread(&node->pr2, sizeof(long), 1, arquivo);
    fread(&node->c3, sizeof(int), 1, arquivo);
    fread(&node->pr3, sizeof(long), 1, arquivo);
    fread(&node->p1, sizeof(int), 1, arquivo);
    fread(&node->p2, sizeof(int), 1, arquivo);
    fread(&node->p3, sizeof(int), 1, arquivo);
    fread(&node->p4, sizeof(int), 1, arquivo);
}
// Função para imprimir o nó
void imprimirNo(BTreeNode *no)
{
    printf("Altura do nó: %d\n", no->alturaNo);
    printf("Número de chaves: %d\n", no->nroChaves);

    printf("Chave 1: %d, Ref 1: %ld\n", no->c1, no->pr1);
    printf("Chave 2: %d, Ref 2: %ld\n", no->c2, no->pr2);
    printf("Chave 3: %d, Ref 3: %ld\n", no->c3, no->pr3);

    printf("Ponteiro 1: %d\n", no->p1);
    printf("Ponteiro 2: %d\n", no->p2);
    printf("Ponteiro 3: %d\n", no->p3);
    printf("Ponteiro 4: %d\n", no->p4);
}

// Função para dividir um nó (split)
// MAX_CHAVES=3
void split(BTreeNode *pai, int pos, BTreeNode *filho, BTreeNode *novoFilho)
{
    // int meio = MAX_CHAVES / 2;
    // novoFilho->alturaNo = filho->alturaNo;
    // novoFilho->nroChaves = meio;

    // novoFilho->c1 = filho->c3;
    // novoFilho->pr1 = filho->pr3;

    // if (filho->alturaNo != 0)
    // {
    //     novoFilho->p1 = filho->p3;
    // }

    // pai->c1 = filho->c2;
    // pai->pr1 = filho->pr2;
    // pai->p1 =
}

// Função para inserir uma chave em um nó não cheio
void insereNaoCheio(FILE *arquivo, Header *header, BTreeNode *no, int chave, long byteOffSet)
{
    int i = no->nroChaves - 1;
    if (no->alturaNo == 0)
    {
        if (i >= 0 && chave < no->c2)
        {
            printf("Chave: %d menor que %d\n\n", chave, no->c2);
            no->c3 = no->c2;
            no->pr3 = no->pr2;
        }

        printf("Inserindo Chave: %d em c2\n", chave);
        no->c2 = chave;
        no->pr2 = byteOffSet;
        no->nroChaves++;
    }
    // else
    // {
    //     while (i >= 0 && chave < no->chaves[i])
    //     {
    //         i--;
    //     }
    //     i++;
    //     BTreeNode filho;
    //     leNo(arquivo, &filho, no->ponteiros[i]);
    //     if (filho.nroChaves == MAX_CHAVES)
    //     {
    //         BTreeNode novoFilho;
    //         long long promoveChave;
    //         int promoveRef;
    //         split(no, i, &filho, &novoFilho, &promoveChave, &promoveRef);
    //         escreveNo(arquivo, &filho, no->ponteiros[i]);
    //         escreveNo(arquivo, &novoFilho, header->proxRRN);
    //         header->proxRRN++;
    //         if (chave > promoveChave)
    //         {
    //             i++;
    //             filho = novoFilho;
    //         }
    //     }
    //     insereNaoCheio(arquivo, header, &filho, chave, ref);
    // }
}

// Função para inserir uma chave na árvore-B
void insere(FILE *arquivo, Header *header, int chave, long byteOffSet)
{
    // Caso não exista Raiz cria o nó raiz
    if (header->noRaiz == -1)
    {
        // printf("ByteOffSet Inicial do indice:%ld\n\n", ftell(arquivo));
        BTreeNode raiz;
        inicializaNo(&raiz);
        raiz.c1 = chave;
        raiz.pr1 = byteOffSet;
        raiz.nroChaves = 1;
        escreveNo(arquivo, raiz, header->proxRRN);
        header->noRaiz = header->proxRRN;
        header->proxRRN++;
        // printf("RRN da Raiz = %d\n\n", header->noRaiz);
        // printf("RRN = %d\n\n", header->proxRRN);
        imprimirNo(&raiz);
        // printf("ByteOffSet Após escrever a raiz do indice:%ld\n\n", ftell(arquivo));
    }
    else
    {
        BTreeNode raiz;
        inicializaNo(&raiz);
        leNo(arquivo, &raiz, header->noRaiz);
        imprimirNo(&raiz);
        if (raiz.nroChaves == MAX_CHAVES)
        {
            printf("Nó cheio\n");
            // BTreeNode novaRaiz, novoFilho;
            // inicializaNo(&novaRaiz);
            // inicializaNo(&novoFilho);
            // novaRaiz.alturaNo = raiz.alturaNo + 1;
            // novaRaiz.p1 = header->noRaiz;
            // split(&novaRaiz, 0, &raiz, &novoFilho);
            // escreveNo(arquivo, &raiz, header->noRaiz);
            // escreveNo(arquivo, &novoFilho, header->proxRRN);
            // header->proxRRN++;
            // header->noRaiz = header->proxRRN;
            // insereNaoCheio(arquivo, header, &novaRaiz, chave, byteOffSet);
            // escreveNo(arquivo, &novaRaiz, header->noRaiz);
        }
        else
        {
            insereNaoCheio(arquivo, header, &raiz, chave, byteOffSet);
            imprimirNo(&raiz);
            escreveNo(arquivo, raiz, header->noRaiz);
        }
    }
    header->nroChaves++;

    // ImprimeCabecalhoB(header);

    escreveCabecalhoB(arquivo, header);
}

void create_indexB_sem_leitura(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    // arquivo inicializado
    FILE *ArquivoBinario = LerArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndice = CriarArquivoIndice(nomeArquivoSaida);

    Cabecalho cabecalho;

    Header header;
    inicializaCabecalho(&header);

    escreveCabecalhoB(ArquivoIndice, &header);
    printf("ByteOffSet após escrever o cabecalho no indice:%ld\n\n", ftell(ArquivoIndice));
    LeCabecalho(ArquivoBinario, &cabecalho);

    if (cabecalho.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    // string para o caso de um campo ser nulo
    Registro registro;
    int byteoffset;

    // itera por todos os registros do arquivo
    // for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
    for (int i = 0; i < 2; i++)
    {
        registro.id = -1;
        // faz a leitura e armazena o registro atual
        byteoffset = ftell(ArquivoBinario);

        registro = LerRegistrosID(ArquivoBinario);
        printf("Id: %d\n", registro.id);
        printf("ByteOffSet: %d\n\n", byteoffset);
        // verifica se o registro esta removido
        if (registro.id == -1)
        {
            printf("Falha no processamento do arquivo.\n");
            return;
        }
        if (registro.removido == '0')
        {
            insere(ArquivoIndice, &header, registro.id, byteoffset);
        }
    }

    // caso não hajam registros no arquivo
    if (cabecalho.nroRegArq == 0)
    {
        printf("Registro inexistente.\n\n");
    }

    fclose(ArquivoBinario);
    fclose(ArquivoIndice);
    // binarioNaTela(nomeArquivoSaida);
}