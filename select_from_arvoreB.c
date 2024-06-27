#include "select_from_arvoreB.h"

// Função que faz a leitura e printa todos os registros de um arquivo binario (Funcionalidade 2)
void select_from_arvoreB(char *nomeArquivoEntrada, char *nomeArquivoIndice)
{
    int id;  // Modifiquei para int, pois estava char[20]
    char lixo[20];

    // número de buscas e campos por busca
    int numEscolhas;
    scanf("%d", &numEscolhas);

    // contador de buscas
    int count = 1;

    // arquivo inicializado
    FILE *ArquivoBinario = LerArquivoBinario(nomeArquivoEntrada);
    FILE *ArquivoIndex = LerArquivoBinario(nomeArquivoIndice);

    Header cabecalho;

    leCabecalhoB(ArquivoIndex, &cabecalho);

    if(cabecalho.status == '0' || cabecalho.nroChaves == 0){
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    // looping pelo número de buscas do usuário
    while (numEscolhas > 0)
    {
        scanf("%s", lixo);
        
        scanf("%d", &id);

        
        printf("BUSCA %d\n\n", count++);

        
        int noAtual = cabecalho.noRaiz;
        long prAssociado = busca_TreeB(ArquivoIndex, noAtual, id);

        if(prAssociado != -1)
        {
            Registro registro;
            fseek(ArquivoBinario, prAssociado, SEEK_SET);
            registro = LerRegistros(ArquivoBinario, "SEM DADO");
            ImprimeRegistroFunc2(registro);

        }else{
            printf("Registro inexistente.\n\n");
        }

        numEscolhas--;
    }

    // arquivo é fechado
    fclose(ArquivoBinario);
    fclose(ArquivoIndex);
}
