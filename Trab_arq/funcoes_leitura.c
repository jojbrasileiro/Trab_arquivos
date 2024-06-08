#include "funcoes_leitura.h"

// função que faz a leitura dos registros a serem inseridos
int LeRegistroStdin(Registro *registro)
{
    char string[30];
    char str[5];

    scanf("%d", &registro->id);

    scanf("%s", str);

    if (strcmp(str, "NULO") == 0)
    {
        registro->idade = -1;
    }
    else
    {
        registro->idade = atoi(str);
    }

    memset(str, '\0', sizeof(str));

    scan_quote_string(string);
    registro->tamNomeJog = VerificaNulo(&registro->nomeJogador, string);

    scan_quote_string(string);
    registro->tamNacionalidade = VerificaNulo(&registro->nacionalidade, string);

    scan_quote_string(string);
    registro->tamNomeClube = VerificaNulo(&registro->nomeClube, string);

    return 33 + registro->tamNacionalidade + registro->tamNomeClube + registro->tamNomeJog;
}

// função que faz a leitura dos campos sem considerar se o arquivo esta removido
Registro LerRegistrosRemovidos(FILE *ArquivoBinario, char *SemDados)
{
    Registro registro;

    fread(&registro.removido, sizeof(char), 1, ArquivoBinario);
    fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
    fread(&registro.Prox, sizeof(long), 1, ArquivoBinario);
    fread(&registro.id, sizeof(int), 1, ArquivoBinario);
    fread(&registro.idade, sizeof(int), 1, ArquivoBinario);

    LerCampoVariado(&registro.nomeJogador, &registro.tamNomeJog, ArquivoBinario, SemDados);
    LerCampoVariado(&registro.nacionalidade, &registro.tamNacionalidade, ArquivoBinario, SemDados);
    LerCampoVariado(&registro.nomeClube, &registro.tamNomeClube, ArquivoBinario, SemDados);

    return registro;
}

// inicia a leitura do csv e verifica se o arquivo foi aberto corretamente
FILE *LerArquivoCSV(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

// inicia a leitura do arquivo binario e verifica se o arquivo foi aberto corretamente
FILE *LerArquivoBinario(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

FILE *LerEscreverArquivoBinario(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb+");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

// função dedicada a fazer a leitura de campos de tamanho variado no caso de seu tamanho ser nulo,
// ja colocando a string "SEM DADO" no campo
void LerCampoVariado(char **Campo, int *tamanhoCampo, FILE *arquivo, char *SemDados)
{
    fread(tamanhoCampo, sizeof(int), 1, arquivo);
    if (*tamanhoCampo == 0)
    {
        *Campo = (char *)malloc((strlen(SemDados) + 1) * sizeof(char));
        strcpy(*Campo, SemDados);
    }
    else
    {
        LerCamposVariadosNaoNulos(Campo, *tamanhoCampo, arquivo);
    }
}

// função que faz a leitura dos campos variados não nulos
void LerCamposVariadosNaoNulos(char **Campo, int tamanho, FILE *arquivo)
{
    *Campo = (char *)malloc((tamanho + 1) * sizeof(char));
    fread(*Campo, sizeof(char), tamanho, arquivo);
    (*Campo)[tamanho] = '\0'; //\0 adicionado apenas para que o print fique correto
}

// função que faz a leitura do cabeçalho
void LeCabecalho(FILE *ArquivoBinario, Cabecalho *cabecalho)
{
    fread(&cabecalho->status, sizeof(char), 1, ArquivoBinario);
    fread(&cabecalho->topo, sizeof(long), 1, ArquivoBinario);
    fread(&cabecalho->proxByteOffset, sizeof(long), 1, ArquivoBinario);
    fread(&cabecalho->nroRegArq, sizeof(int), 1, ArquivoBinario);
    fread(&cabecalho->nroRegRem, sizeof(int), 1, ArquivoBinario);
}

// função que le os registros no arquivo binario, verifica se esta removido, e caso positivo pula o registro
Registro LerRegistros(FILE *ArquivoBinario, char *SemDados)
{
    Registro registro;

    fread(&registro.removido, sizeof(char), 1, ArquivoBinario);
    if (registro.removido == '1')
    {
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fseek(ArquivoBinario, (registro.tamanhoRegistro - 5) * sizeof(char), SEEK_CUR);

        registro.nomeJogador = NULL;
        registro.nacionalidade = NULL;
        registro.nomeClube = NULL;
    }
    else
    {
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fread(&registro.Prox, sizeof(long), 1, ArquivoBinario);
        fread(&registro.id, sizeof(int), 1, ArquivoBinario);
        fread(&registro.idade, sizeof(int), 1, ArquivoBinario);

        LerCampoVariado(&registro.nomeJogador, &registro.tamNomeJog, ArquivoBinario, SemDados);
        LerCampoVariado(&registro.nacionalidade, &registro.tamNacionalidade, ArquivoBinario, SemDados);
        LerCampoVariado(&registro.nomeClube, &registro.tamNomeClube, ArquivoBinario, SemDados);
    }

    return registro;
}

// função que le os registros no arquivo binario no formato do registro indice,
// verifica se esta removido, e caso positivo pula o registro
Registro LerRegistrosID(FILE *ArquivoBinario)
{
    Registro registro;

    fread(&registro.removido, sizeof(char), 1, ArquivoBinario);
    if (registro.removido == '1')
    {
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fseek(ArquivoBinario, (registro.tamanhoRegistro - 5) * sizeof(char), SEEK_CUR);
    }
    else
    {
        registro.id = -1;
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fread(&registro.Prox, sizeof(long), 1, ArquivoBinario);
        fread(&registro.id, sizeof(int), 1, ArquivoBinario);

        fseek(ArquivoBinario, (registro.tamanhoRegistro - 17) * sizeof(char), SEEK_CUR);
    }

    return registro;
}
// Funçaõ que percorre o arquivo indice e busca o byteOffSet do id
int BuscaId(const char *filename, int idBuscado)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    Cabecalho cabecalho;
    LeCabecalho(file, &cabecalho);
    Index temp;
    while (fread(&temp, sizeof(Index), 1, file))
    {
        if (temp.id == idBuscado)
        {
            fclose(file);
            return temp.byteOffset;
        }
    }

    fclose(file);
    return -1;
}
// Função para imprimir os valores na lista de espaços disponíveis
void ImprimirListaEspacoDisponivel(EspacoDisponivel *lista)
{
    EspacoDisponivel *atual = lista;
    while (atual != NULL)
    {
        printf("Tamanho: %d, Offset: %ld\n", atual->tamanho, atual->offset);
        atual = atual->prox;
    }
}

// função que imprime o registro completo para fins de correção
void ImprimeRegistro(Registro registro)
{
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
    printf("Nome do Clube: %s\n\n", registro.nomeClube);
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

// função que imprime o cabeçalho para fins de correção
void ImprimeCabecalho(Cabecalho cabecalho)
{
    printf("Status: %c\n", cabecalho.status);
    printf("Topo: %ld\n", cabecalho.topo);
    printf("Próximo Byte Offset: %ld\n", cabecalho.proxByteOffset);
    printf("Número de Registros no Arquivo: %d\n", cabecalho.nroRegArq);
    printf("Número de Registros Removidos: %d\n\n", cabecalho.nroRegRem);
}