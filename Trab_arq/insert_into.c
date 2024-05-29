#include "insert_into.h"

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

void EscreveLixo(FILE *arquivo, int num){
    for(int i = 0; i < num; i++){
        fwrite("$", sizeof(char), 1, arquivo);
    }
}

int VerificaNulo(char **Campo, char *string) {
    int tamanho;
    if (strcmp(string, "NULO") == 0) {
        tamanho = 0;
        *Campo = (char *)malloc(sizeof(char));
        (*Campo)[0] = '\0';
    } else {
        tamanho = strlen(string);
        *Campo = (char *)malloc((tamanho + 1) * sizeof(char));
        strncpy(*Campo, string, tamanho);
        (*Campo)[tamanho] = '\0';
    }
    return tamanho;
}

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


int insert_into(char *nomeArquivoEntrada, char *nomeArquivoIndice){
    int numEscolhas;
    scanf("%d", &numEscolhas);

    Registro registro = {
    .removido = '0',
    .Prox = -1,
    .id = -1,
    .idade = -1,
    .tamNomeJog = 0,
    .nomeJogador = NULL,
    .tamNacionalidade = 0,
    .nacionalidade = NULL,
    .tamNomeClube = 0,
    .nomeClube = NULL
    };

    FILE *ArquivoBinario = lerEscreverArquivoBinario(nomeArquivoEntrada);

    while (numEscolhas > 0)
    {
        int tamanho = le_registro_stdin(&registro);

        registro.tamanhoRegistro = tamanho;

        Cabecalho cabecalho;

        fseek(ArquivoBinario, 0, SEEK_SET);

        LeCabecalho(ArquivoBinario, &cabecalho);

        long proxByteOffset = cabecalho.topo;
        long antigo_proxByteOffset = proxByteOffset;

        Registro registro_removido;
        int espaco_suficiente = 0;

        for (int i = 0; i < cabecalho.nroRegRem; i++) {

            fseek(ArquivoBinario, proxByteOffset * sizeof(char), SEEK_SET);

            registro_removido = Ler_registros_removidos(ArquivoBinario, "SEM DADO");

            if (registro_removido.tamanhoRegistro >= tamanho) {

                if(i == 0){
                    cabecalho.topo = registro_removido.Prox;
                }else{
                    fseek(ArquivoBinario, (antigo_proxByteOffset + 5) * sizeof(char), SEEK_SET);
                    fwrite(&registro_removido.Prox, sizeof(long), 1, ArquivoBinario);
                }

                fseek(ArquivoBinario, proxByteOffset * sizeof(char), SEEK_SET);

                registro.tamanhoRegistro += registro_removido.tamanhoRegistro - tamanho;

                EscreveRegistro(ArquivoBinario, registro);
                EscreveLixo(ArquivoBinario, registro_removido.tamanhoRegistro - tamanho);

                cabecalho.nroRegArq += 1;
                cabecalho.nroRegRem -= 1;
                EscreveCabecalho(ArquivoBinario, cabecalho);

                espaco_suficiente = 1;

                break;
            }

            if (registro_removido.Prox == -1) {
                break;
            }

            antigo_proxByteOffset = proxByteOffset;
            proxByteOffset = registro_removido.Prox;

            zera_registro(&registro_removido);
        }


        if(espaco_suficiente == 0){
                fseek(ArquivoBinario, 0, SEEK_END);
                EscreveRegistro(ArquivoBinario, registro);
                cabecalho.nroRegArq += 1;
                cabecalho.proxByteOffset += tamanho;
                EscreveCabecalho(ArquivoBinario, cabecalho);
        }

        zera_registro(&registro);

        numEscolhas--;
    }
    
    fclose(ArquivoBinario);

    binarioNaTela(nomeArquivoEntrada);
    create_index (nomeArquivoEntrada, nomeArquivoIndice);
}
