#include "create_index.h"

void create_index (char *nomeArquivoEntrada, char *nomeArquivoSaida){
    create_index_sem_leitura(nomeArquivoEntrada, nomeArquivoSaida);
    binarioNaTela(nomeArquivoSaida);
}

void create_index_sem_leitura(char *nomeArquivoEntrada, char *nomeArquivoSaida){
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
    int ids_list[10000];
    memset(ids_list, 0, sizeof(10000));
    for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
    {
        registro.id = -1;      
        //faz a leitura e armazena o registro atual
        byteoffset = ftell(ArquivoBinario);
        
        registro = Ler_registros_ID(ArquivoBinario);
        
        //verifica se o registro esta removido
        if (registro.id ==-1){
            printf("Falha no processamento do arquivo.");
            return;
        }
        if (registro.removido == '0')
        {
            // printf("ByteOffSet %d\n", byteoffset);
            if(i >0){
                if (verifica_id_Repetido(ids_list, i, registro.id) == 1)
                    {
                        printf("Falha no processamento do arquivo.");
                        return;
                    }
            }
            EscreveRegistroIndice(ArquivoIndice, registro.id, byteoffset);
            ids_list[i] = registro.id;
        }
        
    }

    //caso não hajam registros no arquivo
    if(cabecalho.nroRegArq == 0){
        printf("Registro inexistente.\n\n");
    }

    fclose(ArquivoBinario);
    fclose(ArquivoIndice);
    
}