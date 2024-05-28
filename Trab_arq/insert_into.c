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

        ImprimeRegistro(registro);

        return registro;
}

void EscreveLixo(FILE *arquivo, int num){
    fwrite("$", sizeof(char), num, arquivo);
}

int VerificaNulo(char **Campo, char *string){
    int tamanho;
    if(strcmp(string, "NULO") == 0){
        tamanho = 0;
    }else{

        tamanho = strlen(string);

        *Campo = (char *)malloc((tamanho + 1) * sizeof(char));

        if (*Campo == NULL) {
            return -1;
        }

        strncpy(*Campo, string, tamanho);
    }
    return tamanho;
}

int le_registro_stdin(Registro *registro) {
    char string[20];
    char str[5];

        scanf("%d", &registro->id);

        scanf("%s", str);

        if(strcmp(str, "NULO") == 0){
            registro->idade = -1;
        }else{
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
    //numero de buscas e campos por busca
    int numEscolhas;
    scanf("%d", &numEscolhas);

    //registro padrão inicializado, a ideia é que os campos só sejam comparados se diferentes desses valores, uma vez
    //são valores impossiveis de serem assumidos
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

    //arquivo inicializado
    FILE *ArquivoBinario = lerEscreverArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndice = lerEscreverArquivoBinario(nomeArquivoIndice);

    //looping pelo numero de ebuscas do usuario
    while (numEscolhas > 0)
    {
        int tamanho = le_registro_stdin(&registro);

        ImprimeRegistro(registro);

        printf("O Tamanho é:%d \n", tamanho);

        //inicializa o cabeçalho
        Cabecalho cabecalho;

        //garante que o arquivo inicia no inicio em todas as iterações
        fseek(ArquivoBinario, 0, SEEK_SET);

        //le o cabeçalho
        LeCabecalho(ArquivoBinario, &cabecalho);

        ImprimeCabecalho(cabecalho);

        long proxByteOffset = cabecalho.topo;

        Registro registro_removido;

        int espaço_suficiente = 0;

        //itera pelo arquivo comparando registro a registro com os campos indicados
        for(int i = 0; i < cabecalho.nroRegRem; i++)
        {
            fseek(ArquivoBinario, proxByteOffset  * sizeof(char), SEEK_SET);

            //faz a leitura do registro no arquivo
            registro_removido = Ler_registros_removidos(ArquivoBinario, "SEM DADO");

            printf("Compara tamanho do arquivo: %d, com o necessario: %d\n", registro_removido.tamanhoRegistro, tamanho);

            if(registro_removido.tamanhoRegistro >= tamanho){
                fseek(ArquivoBinario, proxByteOffset  * sizeof(char), SEEK_SET);
                EscreveRegistro(ArquivoBinario, registro);
                EscreveLixo(ArquivoBinario, registro_removido.tamanhoRegistro - tamanho);
                printf("Registro escrito\n");
                //fseek(ArquivoIndice, 0, SEEK_END);
                //(ArquivoIndice, registro.id, proxByteOffset);
                espaço_suficiente = 1;
                break;
            }

            if(registro_removido.Prox == -1){
                break;
            }

            proxByteOffset = registro_removido.Prox;

            zera_registro(&registro_removido);
        }

        //caso não hajam registros correspondentes exibe a mensagem de erro
        if(espaço_suficiente == 0){
                fseek(ArquivoBinario, 0, SEEK_END);
                printf("Final do registro antes: %ld \n", ftell(ArquivoBinario));
                EscreveRegistro(ArquivoBinario, registro);
                printf("Final do registro depois: %ld \n", ftell(ArquivoBinario));
                cabecalho.nroRegArq += 1;
                cabecalho.proxByteOffset += tamanho;
                EscreveCabecalho(ArquivoBinario, cabecalho);
                //fseek(ArquivoIndice, 0, SEEK_END);
                //EscreveRegistroIndice(ArquivoIndice, registro.id, proxByteOffset);
        }

        //registro padrão é zerado para uma nova busca
        zera_registro(&registro);

        numEscolhas--;
    }
    
    //arquivo é fechado
    fclose(ArquivoBinario);
    fclose(ArquivoIndice);

    binarioNaTela(nomeArquivoEntrada);
    //binarioNaTela(nomeArquivoIndice);
    
}
