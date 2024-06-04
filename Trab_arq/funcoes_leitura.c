#include "funcoes_leitura.h"

//função que faz a leitura dos registros a serem inseridos
int le_registro_stdin(Registro *registro) {
    char string[30];
    char str[5];

    scanf("%d", &registro->id);

    scanf("%s", str);

    if (strcmp(str, "NULO") == 0) {
        registro->idade = -1;
    } else {
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

//função que faz a leitura dos campos sem considerar se o arquivo esta removido
Registro Ler_registros_removidos(FILE *ArquivoBinario, char *SemDados) {
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

//inicia a leitura do csv e verifica se o arquivo foi aberto corretamente
FILE *lerArquivoCSV(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

//inicia a leitura do arquivo binario e verifica se o arquivo foi aberto corretamente
FILE *lerArquivoBinario(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

FILE *lerEscreverArquivoBinario(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb+");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return arquivo;
}

//função dedicada a fazer a leitura de campos de tamanho variado no caso de seu tamanho ser nulo, 
//ja colocando a string "SEM DADO" no campo
void LerCampoVariado(char **Campo, int *tamanhoCampo, FILE *arquivo, char* SemDados) {
    fread(tamanhoCampo, sizeof(int), 1, arquivo);
    if (*tamanhoCampo == 0) {
        *Campo = (char *)malloc((strlen(SemDados) + 1) * sizeof(char));
        strcpy(*Campo, SemDados);
    } else {
        LerCamposVariadosNaoNulos(Campo, *tamanhoCampo, arquivo);
    }
}

//função que faz a leitura dos campos variados não nulos
void LerCamposVariadosNaoNulos(char **Campo, int tamanho, FILE *arquivo) {
    *Campo = (char *)malloc((tamanho + 1) * sizeof(char));
    fread(*Campo, sizeof(char), tamanho, arquivo);
    (*Campo)[tamanho] = '\0'; //\0 adicionado apenas para que o print fique correto
}

//função que faz a leitura do cabeçalho
void LeCabecalho(FILE *ArquivoBinario, Cabecalho *cabecalho){
    fread(&cabecalho->status, sizeof(char), 1, ArquivoBinario);
    fread(&cabecalho->topo, sizeof(long), 1, ArquivoBinario);
    fread(&cabecalho->proxByteOffset, sizeof(long), 1, ArquivoBinario);
    fread(&cabecalho->nroRegArq, sizeof(int), 1, ArquivoBinario);
    fread(&cabecalho->nroRegRem, sizeof(int), 1, ArquivoBinario);

}

//função que le os registros no arquivo binario, verifica se esta removido, e caso positivo pula o registro
Registro Ler_registros(FILE *ArquivoBinario, char *SemDados) {
    Registro registro;

    fread(&registro.removido, sizeof(char), 1, ArquivoBinario);
    if (registro.removido == '1') {
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fseek(ArquivoBinario, (registro.tamanhoRegistro - 5) * sizeof(char), SEEK_CUR);

        registro.nomeJogador = NULL;
        registro.nacionalidade = NULL;
        registro.nomeClube = NULL;
    } else {
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
//função que le os registros no arquivo binario, apenas para correção
Registro Ler_registros_debug(FILE *ArquivoBinario, char *SemDados) {
    Registro registro;

    fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
    fread(&registro.Prox, sizeof(long), 1, ArquivoBinario);
    fread(&registro.id, sizeof(int), 1, ArquivoBinario);
    fread(&registro.idade, sizeof(int), 1, ArquivoBinario);

    LerCampoVariado(&registro.nomeJogador, &registro.tamNomeJog, ArquivoBinario, SemDados);
    LerCampoVariado(&registro.nacionalidade, &registro.tamNacionalidade, ArquivoBinario, SemDados);
    LerCampoVariado(&registro.nomeClube, &registro.tamNomeClube, ArquivoBinario, SemDados);
        

    return registro;
}




Registro Ler_registros_ID(FILE *ArquivoBinario) {
    Registro registro;

    fread(&registro.removido, sizeof(char), 1, ArquivoBinario);
    if (registro.removido == '1') {
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fseek(ArquivoBinario, (registro.tamanhoRegistro - 5) * sizeof(char), SEEK_CUR);
    } else {
        registro.id = -1;
        // printf("Valor inicial %d\n", registro.id);
        fread(&registro.tamanhoRegistro, sizeof(int), 1, ArquivoBinario);
        fread(&registro.Prox, sizeof(long), 1, ArquivoBinario);
        fread(&registro.id, sizeof(int), 1, ArquivoBinario);
        // printf("Valor Encontrado %d\n", registro.id);

        fseek(ArquivoBinario, (registro.tamanhoRegistro - 17) * sizeof(char), SEEK_CUR);
        }

    return registro;
}

// Função para procurar um ID no arquivo de índice
int verifica_id_Repetido(int* lista_ids,int lista_tam, int id_procurado) {
    // printf("procurando %d na lista %d\n", id_procurado, lista_tam);
    selection_sort(lista_ids, lista_tam);    
    if (busca_binaria(lista_ids, lista_tam, id_procurado)){
        return 1;
    }
        return 0;
}