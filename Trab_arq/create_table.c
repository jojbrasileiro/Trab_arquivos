#include "create_table.h"

// Função que faz a leitura de um arquivo csv e armazena como um arquivo binario (Funcionalidade 1)
int create_table(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    // arquivos iniciados e abertos
    FILE *ArquivoBinario = CriarArquivoBinario(nomeArquivoSaida);
    FILE *csv = LerArquivoCSV(nomeArquivoEntrada);

    // cabeçlho inicializado
    Cabecalho cabecalho = {
        .status = '0',
        .topo = -1,
        .proxByteOffset = 0,
        .nroRegArq = 0,
        .nroRegRem = 0};

    // função que escreve o cabeçalho no arquivo
    EscreveCabecalho(ArquivoBinario, cabecalho);

    // 1024 é o maximo de caracteres de cada linha do arquivo csv, dessa forma a leitura é feita linha por linha
    // e armazenada nesse vetor que posteriormente vai ser dividido pelas virgulas
    char linha[1024];
    int proxByteOffset = 25;
    int numRegistros = 0;

    // faz a leitura da primeira linha
    fgets(linha, sizeof(linha), csv) != NULL;
    // looping até o final do arquivo
    while (fgets(linha, sizeof(linha), csv) != NULL)
    {
        // retira o /n da string para fins de evitar erros no armazenamento e print do arquivo
        int tamanho = strlen(linha);
        if (tamanho > 0 && linha[tamanho - 1] == '\n')
        {
            linha[tamanho - 1] = '\0';
        }

        // inicializa o registro
        Registro registro;
        // aqui é feito o uso da funçao "strsep" ao inves da "strtok" pelo fato da primira tratar os casos dos tokens nulos,
        // por esse motivo é necessario criar um ponteiro para linha por conta do formato da função
        char *linha_ptr = linha;
        char *token;

        // prox e removido não estão inclusos nesse registro, por isso nao fazem parte da leitura, campos variados sao inicados
        // como nulos
        registro.removido = '0';
        registro.Prox = -1;
        registro.nomeJogador = NULL;
        registro.nacionalidade = NULL;
        registro.nomeClube = NULL;

        // aqui ocorrem a leitura campo a campo verificando se o campo existe ou é vazio
        token = strsep(&linha_ptr, ",");
        processarCampoInt(&registro, token, &registro.id);

        token = strsep(&linha_ptr, ",");
        processarCampoInt(&registro, token, &registro.idade);

        token = strsep(&linha_ptr, ",");
        processarCampoString(&registro, token, &registro.tamNomeJog, &registro.nomeJogador);

        token = strsep(&linha_ptr, ",");
        processarCampoString(&registro, token, &registro.tamNacionalidade, &registro.nacionalidade);

        token = strsep(&linha_ptr, ",");
        processarCampoString(&registro, token, &registro.tamNomeClube, &registro.nomeClube);

        // 33 é o tamanho dos campos fixos, que por sua vez é somado aos campos de tamanho variado
        registro.tamanhoRegistro = 33 + registro.tamNomeJog + registro.tamNacionalidade + registro.tamNomeClube;

        // registro é escrito no arquivo binario
        EscreveRegistro(ArquivoBinario, registro);
        proxByteOffset += registro.tamanhoRegistro;
        numRegistros++;

        // verifica se os campos variados foram alocados e executa um free caso positivo
        if (registro.nomeJogador != NULL)
        {
            free(registro.nomeJogador);
            registro.nomeJogador = NULL;
        }
        if (registro.nacionalidade != NULL)
        {
            free(registro.nacionalidade);
            registro.nacionalidade = NULL;
        }
        if (registro.nomeClube != NULL)
        {
            free(registro.nomeClube);
            registro.nomeClube = NULL;
        }
    }

    // proxByteOffset = ftell(ArquivoBinario);

    // cabecalho é atualizado e tem seu status mudado para 1, ja que a escrita acabou
    cabecalho.status = '1';
    cabecalho.topo = -1;
    cabecalho.proxByteOffset = proxByteOffset;
    cabecalho.nroRegArq = numRegistros;
    cabecalho.nroRegRem = 0;

    EscreveCabecalho(ArquivoBinario, cabecalho);

    // arquivos são fechados e o binario na tela é executado
    fclose(csv);
    fclose(ArquivoBinario);

    binarioNaTela(nomeArquivoSaida);

    return 0;
}
