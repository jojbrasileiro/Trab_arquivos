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
    header->status = '1';
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
void escreveNo(FILE *arquivo, BTreeNode *node, int RRN)
{
    fseek(arquivo, TAMANHO_CABECALHO + RRN * TAMANHO_NO, SEEK_SET);
    fwrite(&node->alturaNo, sizeof(int), 1, arquivo);
    fwrite(&node->nroChaves, sizeof(int), 1, arquivo);
    fwrite(&node->c1, sizeof(int), 1, arquivo);
    fwrite(&node->pr1, sizeof(long), 1, arquivo);
    fwrite(&node->c2, sizeof(int), 1, arquivo);
    fwrite(&node->pr2, sizeof(long), 1, arquivo);
    fwrite(&node->c3, sizeof(int), 1, arquivo);
    fwrite(&node->pr3, sizeof(long), 1, arquivo);
    fwrite(&node->p1, sizeof(int), 1, arquivo);
    fwrite(&node->p2, sizeof(int), 1, arquivo);
    fwrite(&node->p3, sizeof(int), 1, arquivo);
    fwrite(&node->p4, sizeof(int), 1, arquivo);
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

dados split(BTreeNode *esquerda, dados dadosInsercao, BTreeNode *direita)
{
    dados promove = {
        .chave = esquerda->c2,
        .byteOffSet = esquerda->pr2,
        .RRNEsquerda = esquerda->RRNAtual,
        .RRNDireita = direita->RRNAtual};

    direita->c1 = esquerda->c3;
    direita->pr1 = esquerda->pr3;
    direita->p1 = esquerda->p3;
    direita->p2 = esquerda->p4;
    direita->nroChaves = 1;
    direita->alturaNo = esquerda->alturaNo;

    esquerda->c2 = -1;
    esquerda->pr2 = -1;
    esquerda->c3 = -1;
    esquerda->pr3 = -1;
    esquerda->p3 = -1;
    esquerda->p4 = -1;
    esquerda->nroChaves = 1;

    if (dadosInsercao.chave < esquerda->c1)
    {
        esquerda->c2 = esquerda->c1;
        esquerda->pr2 = esquerda->pr1;
        esquerda->c1 = dadosInsercao.chave;
        esquerda->pr1 = dadosInsercao.byteOffSet;
        esquerda->p3 = esquerda->p2;
        esquerda->p2 = esquerda->p1;
        esquerda->p1 = dadosInsercao.RRNEsquerda;
        esquerda->nroChaves++;
    }
    else if (dadosInsercao.chave < promove.chave)
    {
        esquerda->c2 = dadosInsercao.chave;
        esquerda->pr2 = dadosInsercao.byteOffSet;
        esquerda->p3 = dadosInsercao.RRNDireita;
        esquerda->nroChaves++;
    }
    else if (dadosInsercao.chave < direita->c1)
    {
        direita->c2 = direita->c1;
        direita->pr2 = direita->pr1;
        direita->c1 = dadosInsercao.chave;
        direita->pr1 = dadosInsercao.byteOffSet;
        direita->p3 = direita->p2;
        direita->p2 = direita->p1;
        direita->p1 = dadosInsercao.RRNEsquerda;
        direita->nroChaves++;
    }
    else
    {
        direita->c2 = dadosInsercao.chave;
        direita->pr2 = dadosInsercao.byteOffSet;
        direita->p3 = dadosInsercao.RRNDireita;
        direita->nroChaves++;
    }

    return promove;
}

// Função para inserir uma chave em um nó não cheio
dados insereNaoCheio(FILE *arquivo, Header *header, BTreeNode *no_atual, dados dadosInsercao)
{
    dados dadosPromoveChave = {
        .chave = -1,
        .byteOffSet = -1,
        .RRNDireita = -1,
        .RRNEsquerda = -1,
        .AlturaNo = 0};
    BTreeNode prox_no;
    if (no_atual->alturaNo == 0)
    {
        if (no_atual->nroChaves == MAX_CHAVES)
        {
            BTreeNode filho;
            inicializaNo(&filho);
            filho.RRNAtual = header->proxRRN;
            dadosPromoveChave = split(no_atual, dadosInsercao, &filho);
            dadosPromoveChave.AlturaNo = 0;
            escreveNo(arquivo, no_atual, no_atual->RRNAtual);
            escreveNo(arquivo, &filho, filho.RRNAtual);
            header->proxRRN++;
        }
        else
        {
            if (dadosInsercao.chave < no_atual->c1)
            {
                no_atual->c3 = no_atual->c2;
                no_atual->c2 = no_atual->c1;
                no_atual->c1 = dadosInsercao.chave;

                no_atual->pr3 = no_atual->pr2;
                no_atual->pr2 = no_atual->pr1;
                no_atual->pr1 = dadosInsercao.byteOffSet;
            }
            else if (dadosInsercao.chave < no_atual->c2 || no_atual->c2 == -1)
            {
                no_atual->c3 = no_atual->c2;
                no_atual->c2 = dadosInsercao.chave;

                no_atual->pr3 = no_atual->pr2;
                no_atual->pr2 = dadosInsercao.byteOffSet;
            }
            else
            {
                no_atual->c3 = dadosInsercao.chave;
                no_atual->pr3 = dadosInsercao.byteOffSet;
            }
            no_atual->nroChaves++;
            escreveNo(arquivo, no_atual, no_atual->RRNAtual);
        }
        dadosPromoveChave.AlturaNo = 0;
        return dadosPromoveChave;
    }
    if (dadosInsercao.chave < no_atual->c1)
    {
        prox_no = leNo(arquivo, no_atual->p1);
        imprimirNo(&prox_no);
        prox_no.RRNAtual = no_atual->p1;
    }
    else if (dadosInsercao.chave < no_atual->c2 || no_atual->c2 == -1)
    {
        prox_no = leNo(arquivo, no_atual->p2);
        imprimirNo(&prox_no);
        prox_no.RRNAtual = no_atual->p2;
    }
    else if (dadosInsercao.chave < no_atual->c3 || no_atual->c3 == -1)
    {
        prox_no = leNo(arquivo, no_atual->p3);
        imprimirNo(&prox_no);
        prox_no.RRNAtual = no_atual->p3;
    }
    else
    {
        prox_no = leNo(arquivo, no_atual->p4);
        imprimirNo(&prox_no);
        prox_no.RRNAtual = no_atual->p4;
    }
    dadosPromoveChave = insereNaoCheio(arquivo, header, &prox_no, dadosInsercao);
    dadosPromoveChave.AlturaNo++;
    no_atual->alturaNo = dadosPromoveChave.AlturaNo;
    escreveNo(arquivo, no_atual, no_atual->RRNAtual);
    if (dadosPromoveChave.chave == -1)
    {
        return dadosPromoveChave;
    }
    if (no_atual->nroChaves == MAX_CHAVES)
    {
        BTreeNode filho;
        inicializaNo(&filho);
        filho.RRNAtual = header->proxRRN;
        // no_atual->alturaNo++;
        dadosPromoveChave = split(no_atual, dadosPromoveChave, &filho);
        escreveNo(arquivo, no_atual, no_atual->RRNAtual);
        escreveNo(arquivo, &filho, filho.RRNAtual);
        header->proxRRN++;
        dadosPromoveChave.AlturaNo = no_atual->alturaNo;
        return dadosPromoveChave;
    }
    if (dadosPromoveChave.chave < no_atual->c1)
    {
        no_atual->c3 = no_atual->c2;
        no_atual->c2 = no_atual->c1;
        no_atual->c1 = dadosPromoveChave.chave;

        no_atual->pr3 = no_atual->pr2;
        no_atual->pr2 = no_atual->pr1;
        no_atual->pr1 = dadosPromoveChave.byteOffSet;

        no_atual->p4 = no_atual->p3;
        no_atual->p3 = no_atual->p2;
        no_atual->p2 = dadosPromoveChave.RRNDireita;
        no_atual->p1 = dadosPromoveChave.RRNEsquerda;
    }
    else if (dadosPromoveChave.chave < no_atual->c2 || no_atual->c2 == -1)
    {
        no_atual->c3 = no_atual->c2;
        no_atual->c2 = dadosPromoveChave.chave;

        no_atual->pr3 = no_atual->pr2;
        no_atual->pr2 = dadosPromoveChave.byteOffSet;

        no_atual->p4 = no_atual->p3;
        no_atual->p3 = dadosPromoveChave.RRNDireita;
        no_atual->p2 = dadosPromoveChave.RRNEsquerda;
    }
    else
    {
        no_atual->c3 = dadosPromoveChave.chave;
        no_atual->pr3 = dadosPromoveChave.byteOffSet;
        no_atual->p3 = dadosPromoveChave.RRNEsquerda;
        no_atual->p4 = dadosPromoveChave.RRNDireita;
    }
    no_atual->nroChaves++;
    escreveNo(arquivo, no_atual, no_atual->RRNAtual);

    dadosPromoveChave.chave = -1;
    dadosPromoveChave.byteOffSet = -1;
    dadosPromoveChave.RRNDireita = -1;
    dadosPromoveChave.RRNEsquerda = -1;
    dadosPromoveChave.AlturaNo = no_atual->alturaNo;
    return dadosPromoveChave;
}

// Função para inserir uma chave na árvore-B
void insere(FILE *arquivo, Header *header, int chave, long byteOffSet)
{
    dados dadosInsercao = {
        .chave = chave,
        .byteOffSet = byteOffSet,
        .RRNDireita = -1,
        .RRNEsquerda = -1,
        .AlturaNo = 0};

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
        escreveNo(arquivo, &raiz, header->proxRRN);
        header->proxRRN++;
    }
    else
    {
        BTreeNode raiz = leNo(arquivo, header->noRaiz);
        imprimirNo(&raiz);
        raiz.RRNAtual = header->noRaiz;
        dadosInsercao = insereNaoCheio(arquivo, header, &raiz, dadosInsercao);
        if (dadosInsercao.chave != -1)
        {
            BTreeNode novaRaiz;
            inicializaNo(&novaRaiz);
            novaRaiz.c1 = dadosInsercao.chave;
            novaRaiz.pr1 = dadosInsercao.byteOffSet;
            novaRaiz.nroChaves = 1;
            novaRaiz.p1 = dadosInsercao.RRNEsquerda;
            novaRaiz.p2 = dadosInsercao.RRNDireita;
            novaRaiz.alturaNo = dadosInsercao.AlturaNo + 1;
            novaRaiz.RRNAtual = header->proxRRN;
            header->noRaiz = header->proxRRN;
            escreveNo(arquivo, &novaRaiz, header->proxRRN);
            header->proxRRN++;
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
    for (int i = 0; i < 40; i++)
    {
        registro.id = -1;
        byteoffset = ftell(ArquivoBinario);

        registro = LerRegistrosID(ArquivoBinario);
        if (registro.id == -1)
        {
            printf("Falha no processamento do arquivo.\n");
            return;
        }
        if (registro.removido == '0')
        {
            printf("\nIDS: %d\n", registro.id);
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
    binarioNaTela(nomeArquivoSaida);
}