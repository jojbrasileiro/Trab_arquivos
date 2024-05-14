#include "create_index.h"

void create_index (char *nomeArquivoEntrada, char *nomeArquivoSaida){
     //arquivo inicializado
    FILE *ArquivoBinario = lerArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndice = criarArquivoIndice(nomeArquivoSaida);

    Cabecalho cabecalho;

    //Faz a leitura do cabaçalho
    LeCabecalho(ArquivoBinario, &cabecalho);

    //string para o caso de um campo ser nulo
    Registro registro;
    int byteoffset;
    //itera por todos os registros do arquivo
    for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++) {

        //faz a leitura e armazena o registro atual
        byteoffset = ftell(ArquivoBinario);
        registro = Ler_registros_ID(ArquivoBinario);

        //verifica se o registro esta removido
        if(registro.removido == '0'){
        EscreveRegistroIndice(ArquivoIndice, registro.id, byteoffset);
        }
    }

    //caso não hajam registros no arquivo
    if(cabecalho.nroRegArq == 0){
        printf("Registro inexistente.\n\n");
    }

    fclose(ArquivoBinario);
    fclose(ArquivoIndice);

    binarioNaTela(nomeArquivoSaida);
}