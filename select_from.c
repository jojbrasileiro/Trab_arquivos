#include "select_from.h"

// Função que faz a leitura e printa todos os registros de um arquivo binario (Funcionalidade 2)
void select_from(char *nomeArquivoEntrada)
{
    // arquivo inicializado
    FILE *ArquivoBinario = LerArquivoBinario(nomeArquivoEntrada);

    Cabecalho cabecalho;

    // Faz a leitura do cabaçalho
    LeCabecalho(ArquivoBinario, &cabecalho);

    if (cabecalho.status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    // string para o caso de um campo ser nulo
    char SemDados[] = "SEM DADO";
    Registro registro;
    // itera por todos os registros do arquivo
    for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
    {

        // faz a leitura e armazena o registro atual
        registro = LerRegistros(ArquivoBinario, SemDados);

        // verifica se o registro esta removido
        if (registro.removido == '0')
        {
            ImprimeRegistroFunc2(registro);
        }

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

    // caso não hajam registros no arquivo
    if (cabecalho.nroRegArq == 0)
    {
        printf("Registro inexistente.\n\n");
    }

    fclose(ArquivoBinario);
}
