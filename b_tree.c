#include "b_tree.h"
int contador = 0;
int calls = 0;
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
    printf("Próximo RprN: %d\n", Header->proxRRN);
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
    BTreeNode no = {};
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
    printf("RRN ATUAL: %d\n", no->RRNAtual);
}

int conta_cria(BTreeNode *no)
{
    int cria = 0;
    if (no->p1 != -1)
        cria++;
    if (no->p2 != -1)
        cria++;
    if (no->p3 != -1)
        cria++;
    if (no->p4 != -1)
        cria++;
    return cria;
}

dados split(BTreeNode *esquerda, dados dadosInsercao, BTreeNode *direita)
{

    int keys[4];
    long prs[4];
    int p[5];
    // Combina as 3 chaves com a chave para inserção
    keys[0] = esquerda->c1;
    keys[1] = esquerda->c2;
    keys[2] = esquerda->c3;
    keys[3] = dadosInsercao.chave;

    prs[0] = esquerda->pr1;
    prs[1] = esquerda->pr2;
    prs[2] = esquerda->pr3;
    prs[3] = dadosInsercao.byteOffSet;

    p[0] = esquerda->p1;
    p[1] = esquerda->p2;
    p[2] = esquerda->p3;
    p[3] = esquerda->p4;
    p[4] = dadosInsercao.RRNDireita;

    // Ordena as chaves para encontrar o melhor nó para promoção
    for (int i = 3; i > 0; i--)
    {
        if (keys[i] < keys[i - 1])
        {
            int aux_k = keys[i];
            long aux_pr = prs[i];
            int aux_p = p[i + 1];
            keys[i] = keys[i - 1];
            prs[i] = prs[i - 1];
            p[i + 1] = p[i];
            keys[i - 1] = aux_k;
            prs[i - 1] = aux_pr;
            p[i] = aux_p;
        }
        else
        {
            break;
        }
    }
    // define a chave a ser promovida
    dados promove = {
        .chave = keys[1],
        .byteOffSet = prs[1],
        .AlturaNo = esquerda->alturaNo,
        .RRNDireita = direita->RRNAtual};

    // cria o maior filho
    direita->c1 = keys[2];
    direita->pr1 = prs[2];
    direita->c2 = keys[3];
    direita->pr2 = prs[3];
    direita->c3 = -1;
    direita->pr3 = -1;
    direita->p1 = p[2];
    direita->p2 = p[3];
    direita->p3 = p[4];
    direita->p4 = -1;
    direita->nroChaves = 2;
    direita->alturaNo = esquerda->alturaNo;
    // cria o menor filho
    esquerda->c1 = keys[0];
    esquerda->pr1 = prs[0];
    esquerda->c2 = -1;
    esquerda->pr2 = -1;
    esquerda->c3 = -1;
    esquerda->pr3 = -1;
    esquerda->p1 = p[0];
    esquerda->p2 = p[1];
    esquerda->p3 = -1;
    esquerda->p4 = -1;
    esquerda->nroChaves = 1;
    return promove;
}

// Função para inserir uma chave em um nó não cheio
dados insereNaoCheio(FILE *arquivo, Header *header, BTreeNode *no_atual, dados dadosInsercao)
{
    dados dadosPromoveChave = {
        .chave = -1,
        .byteOffSet = -1,
        .RRNDireita = -1,
        .AlturaNo = 0};
    BTreeNode prox_no;
    // Caso nó seja uma folha
    if (no_atual->alturaNo == 0)
    {
        // SPLIT EM UM NO FOLHA
        if (no_atual->nroChaves == MAX_CHAVES)
        {
            BTreeNode filho;
            inicializaNo(&filho);
            filho.RRNAtual = header->proxRRN;
            dadosPromoveChave = split(no_atual, dadosInsercao, &filho);
            dadosPromoveChave.AlturaNo = 0;
            escreveNo(arquivo, no_atual, no_atual->RRNAtual);
            BTreeNode node = leNo(arquivo, no_atual->RRNAtual);
            escreveNo(arquivo, &filho, filho.RRNAtual);
            header->proxRRN++;
            return dadosPromoveChave;
        }
        // Caso tenha espaço realiza a inserção
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
            BTreeNode node = leNo(arquivo, no_atual->RRNAtual);
            node.RRNAtual = no_atual->RRNAtual;
            dadosPromoveChave.chave = -1;
            dadosPromoveChave.byteOffSet = -1;
            dadosPromoveChave.RRNDireita = -1;
            dadosPromoveChave.AlturaNo = 0;
            return dadosPromoveChave;
        }
    }
    // Caso nó não seja uma folha
    if (dadosInsercao.chave < no_atual->c1)
    {
        prox_no = leNo(arquivo, no_atual->p1);
        prox_no.RRNAtual = no_atual->p1;
    }
    else if (dadosInsercao.chave < no_atual->c2 || no_atual->c2 == -1)
    {
        prox_no = leNo(arquivo, no_atual->p2);
        prox_no.RRNAtual = no_atual->p2;
    }
    else if (dadosInsercao.chave < no_atual->c3 || no_atual->c3 == -1)
    {
        prox_no = leNo(arquivo, no_atual->p3);
        prox_no.RRNAtual = no_atual->p3;
    }
    else
    {
        prox_no = leNo(arquivo, no_atual->p4);
        prox_no.RRNAtual = no_atual->p4;
    }
    // Recursão
    dadosPromoveChave = insereNaoCheio(arquivo, header, &prox_no, dadosInsercao);

    if (dadosPromoveChave.chave == -1)
    {
        return dadosPromoveChave;
    }

    dadosPromoveChave.AlturaNo++;
    no_atual->alturaNo = dadosPromoveChave.AlturaNo;
    escreveNo(arquivo, no_atual, no_atual->RRNAtual);
    BTreeNode node = leNo(arquivo, no_atual->RRNAtual);
    // Caso pai esteja cheio
    if (no_atual->nroChaves == MAX_CHAVES)
    {
        BTreeNode filho;
        inicializaNo(&filho);
        filho.RRNAtual = header->proxRRN;
        dadosPromoveChave = split(no_atual, dadosPromoveChave, &filho);
        escreveNo(arquivo, no_atual, no_atual->RRNAtual);
        BTreeNode node = leNo(arquivo, no_atual->RRNAtual);
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
    }
    else if (dadosPromoveChave.chave < no_atual->c2 || no_atual->c2 == -1)
    {
        no_atual->c3 = no_atual->c2;
        no_atual->c2 = dadosPromoveChave.chave;

        no_atual->pr3 = no_atual->pr2;
        no_atual->pr2 = dadosPromoveChave.byteOffSet;

        no_atual->p4 = no_atual->p3;
        no_atual->p3 = dadosPromoveChave.RRNDireita;
    }
    else
    {
        no_atual->c3 = dadosPromoveChave.chave;
        no_atual->pr3 = dadosPromoveChave.byteOffSet;
        no_atual->p4 = dadosPromoveChave.RRNDireita;
    }
    no_atual->nroChaves++;
    escreveNo(arquivo, no_atual, no_atual->RRNAtual);
    node = leNo(arquivo, no_atual->RRNAtual);

    dadosPromoveChave.chave = -1;
    dadosPromoveChave.byteOffSet = -1;
    dadosPromoveChave.RRNDireita = -1;
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
        // .RRNEsquerda = -1,
        .AlturaNo = 0};

    // Caso não exista Raiz cria o nó raiz
    if (header->noRaiz == -1)
    {
        BTreeNode raiz;
        inicializaNo(&raiz);
        raiz.c1 = chave;
        raiz.pr1 = byteOffSet;
        raiz.nroChaves = 1;
        header->noRaiz = header->proxRRN;
        escreveNo(arquivo, &raiz, header->proxRRN);
        BTreeNode node = leNo(arquivo, header->proxRRN);
        header->proxRRN++;
    }
    else
    {
        BTreeNode raiz = leNo(arquivo, header->noRaiz);
        raiz.RRNAtual = header->noRaiz;
        dadosInsercao = insereNaoCheio(arquivo, header, &raiz, dadosInsercao);
        // CRIA UMA NOVA RAIZ
        if (dadosInsercao.chave != -1)
        {
            BTreeNode novaRaiz;
            inicializaNo(&novaRaiz);
            novaRaiz.c1 = dadosInsercao.chave;
            novaRaiz.pr1 = dadosInsercao.byteOffSet;
            novaRaiz.nroChaves = 1;
            novaRaiz.p1 = header->noRaiz;
            novaRaiz.p2 = dadosInsercao.RRNDireita;
            novaRaiz.alturaNo = dadosInsercao.AlturaNo + 1;
            novaRaiz.RRNAtual = header->proxRRN;
            header->noRaiz = header->proxRRN;
            escreveNo(arquivo, &novaRaiz, header->proxRRN);
            BTreeNode node = leNo(arquivo, header->proxRRN);
            header->proxRRN++;
        }
    }
    header->nroChaves++;

    escreveCabecalhoB(arquivo, header);
    contador++;
}

void create_indexB(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{

    // arquivo inicializado
    FILE *ArquivoBinario = LerArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndice = CriarArquivoIndiceB(nomeArquivoSaida);

    Cabecalho cabecalho;

    Header header;
    inicializaCabecalho(&header);

    escreveCabecalhoB(ArquivoIndice, &header);
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
    for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
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
            insere(ArquivoIndice, &header, registro.id, byteoffset);
        }
    }

    // caso não hajam registros no arquivo
    if (cabecalho.nroRegArq == 0)
    {
        printf("Registro inexistente.\n\n");
    }
    int prox = header.proxRRN;

    fclose(ArquivoBinario);
    fclose(ArquivoIndice);
    binarioNaTela(nomeArquivoSaida);
}
