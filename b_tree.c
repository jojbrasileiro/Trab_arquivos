#include "b_tree.h"
int contador = 0;
// Função para inicializar um novo nó da árvore-B
void inicializaNo(BTreeNode *node)
{
    node->alturaNo = 0;
    node->nroChaves = 0;
    node->c1 = -1;
    node->pr1 = -1;
    node->c2 = -1;
    node->pr2 = -1;
    node->c3 = -1;
    node->pr3 = -1;
    node->p1 = -1;
    node->p2 = -1;
    node->p3 = -1;
    node->p4 = -1;
}

void AtualizaFilho(BTreeNode *node)
{
    node->c2 = -1;
    node->pr2 = -1;
    node->c3 = -1;
    node->pr3 = -1;
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
BTreeNode leNo(FILE *arquivo, int RRN)
{
    BTreeNode no;
    // printf("RRN %d\n", RRN);
    fseek(arquivo, TAMANHO_CABECALHO + RRN * TAMANHO_NO, SEEK_SET);
    fread(&no.alturaNo, sizeof(int), 1, arquivo);
    fread(&no.nroChaves, sizeof(int), 1, arquivo);
    fread(&no.c1, sizeof(int), 1, arquivo);
    fread(&no.pr1, sizeof(long), 1, arquivo);
    fread(&no.c2, sizeof(int), 1, arquivo);
    fread(&no.pr2, sizeof(long), 1, arquivo);
    fread(&no.c3, sizeof(int), 1, arquivo);
    fread(&no.pr3, sizeof(long), 1, arquivo);
    fread(&no.p1, sizeof(int), 1, arquivo);
    fread(&no.p2, sizeof(int), 1, arquivo);
    fread(&no.p3, sizeof(int), 1, arquivo);
    fread(&no.p4, sizeof(int), 1, arquivo);
    return no;
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
// split(&novaRaiz, 0, &raiz, &novoFilho);
void split(BTreeNode *pai, int pos, BTreeNode *filho, BTreeNode *novoFilho)
{
    int meio = 1; // Com 3 chaves, o meio é a segunda chave (índice 1)

    novoFilho->alturaNo = filho->alturaNo;
    novoFilho->nroChaves = 1; // Novo nó terá uma chave

    novoFilho->c1 = filho->c3;
    novoFilho->pr1 = filho->pr3;
    novoFilho->p1 = filho->p3;
    novoFilho->p2 = filho->p4;

    // Move as chaves e ponteiros do pai para acomodar a nova chave e o novo filho
    pai->c3 = pai->c2;
    pai->pr3 = pai->pr2;
    pai->p4 = pai->p3;

    pai->c2 = pai->c1;
    pai->pr2 = pai->pr1;
    pai->p3 = pai->p2;

    // Insere a chave do meio e os ponteiros no pai
    pai->c1 = filho->c2;
    pai->pr1 = filho->pr2;
    pai->p2 = pai->p1 + 1;

    pai->nroChaves++;

    // Atualiza o nó filho original, que agora terá uma chave a menos
    filho->nroChaves = meio;
    AtualizaFilho(filho);
}

// Função para inserir uma chave em um nó não cheio
void insereNaoCheio(FILE *arquivo, Header *header, BTreeNode *raiz, int chave, long byteOffSet, int RRN)
{
    int i = raiz->nroChaves - 1;
    printf("Iniciando inserção do raiz\n");
    imprimirNo(raiz);
    printf("\n");
    if (raiz->alturaNo == 0)
    {
        // Inserção em um nó folha
        while (i >= 0 && chave < raiz->c1)
        {
            raiz->c3 = raiz->c2;
            raiz->pr3 = raiz->pr2;
            raiz->c2 = raiz->c1;
            raiz->pr2 = raiz->pr1;
            raiz->c1 = chave;
            raiz->pr1 = byteOffSet;
            i--;
        }

        if (i == 0)
        {
            raiz->c2 = chave;
            raiz->pr2 = byteOffSet;
        }
        else if (i == 1)
        {
            raiz->c3 = chave;
            raiz->pr3 = byteOffSet;
        }
        printf("Finalizando inserção do raiz de altura 0\n");
        imprimirNo(raiz);
        printf("\n");
        raiz->nroChaves++;
    }
    else
    {
        // Inserção em um nó não folha
        while (i >= 0 && chave < raiz->c1)
        {
            i--;
        }
        i++;
        printf("Buscando filho %d\n", raiz->p1);
        BTreeNode filho;
        printf("Chave a ser buscada %d\n", chave);
        printf("Chave do nó %d\n", raiz->c1);

        if (chave < raiz->c1)
        {
            filho = leNo(arquivo, raiz->p1);
        }
        else
        {
            filho = leNo(arquivo, raiz->p2);
        }

        if (filho.nroChaves == MAX_CHAVES)
        {
            printf("nó cheio\n");
            BTreeNode novoFilho;
            inicializaNo(&novoFilho);
            split(raiz, i, &filho, &novoFilho);
            escreveNo(arquivo, filho, raiz->p1);
            escreveNo(arquivo, novoFilho, header->proxRRN);
            header->proxRRN++;

            if (chave > raiz->c1)
            {
                i++;
                filho = novoFilho;
            }
        }
        // printf("inserindo em no n folha\n");
        imprimirNo(&filho);
        // printf("\n");
        insereNaoCheio(arquivo, header, &filho, chave, byteOffSet);
    }
}

// Função para inserir uma chave na árvore-B
void insere(FILE *arquivo, Header *header, int chave, long byteOffSet)
{
    // Caso não exista Raiz cria o nó raiz
    printf("Iteração %d\n", contador);
    if (header->noRaiz == -1)
    {
        BTreeNode raiz;
        inicializaNo(&raiz);
        raiz.c1 = chave;
        raiz.pr1 = byteOffSet;
        raiz.nroChaves = 1;
        header->noRaiz = header->proxRRN;
        escreveNo(arquivo, raiz, header->proxRRN);
        header->proxRRN++;
    }
    else
    {
        BTreeNode node;
        printf("Buscando raiz %d\n", header->noRaiz);
        BTreeNode raiz = leNo(arquivo, header->noRaiz);
        if (raiz.nroChaves == MAX_CHAVES)
        {
            BTreeNode novaRaiz, novoFilho;
            inicializaNo(&novaRaiz);
            inicializaNo(&novoFilho);
            novaRaiz.alturaNo = raiz.alturaNo + 1;
            novaRaiz.p1 = header->noRaiz;
            split(&novaRaiz, 0, &raiz, &novoFilho);
            printf("RRN ATUAL %d\n", header->noRaiz);
            escreveNo(arquivo, raiz, header->noRaiz);
            printf("RRN ATUAL +1 %d\n", header->proxRRN);
            escreveNo(arquivo, novoFilho, header->proxRRN);
            // printf("RRN ATUAL %d\n", header->proxRRN);
            header->proxRRN++;
            // printf("RRN ATUAL +1 %d\n", header->proxRRN);
            header->noRaiz = header->proxRRN;
            printf("Valor do nó raiz %d\n", header->noRaiz);
            escreveNo(arquivo, novaRaiz, header->noRaiz);
            insereNaoCheio(arquivo, header, &novaRaiz, chave, byteOffSet);
            printf("Inserindo nova Raiz\n");
            imprimirNo(&node);
            printf("\n");
            escreveNo(arquivo, node, header->noRaiz);
        }
        else
        {
            if (raiz.alturaNo > 0)
            {
                imprimirNo(&raiz);
            }
            insereNaoCheio(arquivo, header, &raiz, chave, byteOffSet);

            escreveNo(arquivo, node, header->noRaiz);
        }
    }
    header->nroChaves++;

    escreveCabecalhoB(arquivo, header);
    contador++;
}

void create_indexB_sem_leitura(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    // arquivo inicializado
    FILE *ArquivoBinario = LerArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndice = CriarArquivoIndiceB(nomeArquivoSaida);

    Cabecalho cabecalho;

    Header header;
    inicializaCabecalho(&header);

    escreveCabecalhoB(ArquivoIndice, &header);
    // printf("ByteOffSet após escrever o cabecalho no indice:%ld\n\n", ftell(ArquivoIndice));
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
    for (int i = 0; i < 5; i++)
    {
        registro.id = -1;
        // faz a leitura e armazena o registro atual
        byteoffset = ftell(ArquivoBinario);

        registro = LerRegistrosID(ArquivoBinario);
        // printf("Id: %d\n", registro.id);
        // printf("ByteOffSet: %d\n\n", byteoffset);
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