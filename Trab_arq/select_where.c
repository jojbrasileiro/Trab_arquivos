#include "select_where.h"

//Função responsavel por ler e printar os registros que atendam a busca do usuario
void select_where(char *nomeArquivoEntrada){
    
    //string que armazena o nome do campo selecionado
    char campo[20];

    //numero de buscas e campos por busca
    int numEscolhas;
    int numCampos;
    scanf("%d", &numEscolhas);

    //registro padrão inicializado, a ideia é que os campos só sejam comparados se diferentes desses valores, uma vez
    //são valores impossiveis de serem assumidos
    Registro registro = {
    .id = -1,
    .idade = -1,
    .tamNomeJog = 0,
    .nomeJogador = NULL,
    .tamNacionalidade = 0,
    .nacionalidade = NULL,
    .tamNomeClube = 0,
    .nomeClube = NULL
    };

    //contador de buscas
    int count = 1;

    //arquivo inicializado
    FILE *ArquivoBinario = lerArquivoBinario(nomeArquivoEntrada);

    //looping pelo numero de ebuscas do usuario
    while (numEscolhas > 0)
    {
        scanf("%d", &numCampos);

        //for pelo numero de campos indicados pelo usuario
        for (int i = 0; i < numCampos; i++)
        {
            //le o campo
            scanf("%s", campo);
            
            //determina qual o campo e faz e faz o armazenamento apropriado no registro padrão
            determina_campo(campo, &registro);

            //zera a string campo
            memset(campo, 0, sizeof(campo));
        }

        //print da busca
        printf("Busca %d\n\n", count++);

        //inicializa o cabeçalho
        Cabecalho cabecalho;

        //garante que o arquivo inicia no inicio em todas as iterações
        fseek(ArquivoBinario, 0, SEEK_SET);

        //le o cabeçalho
        LeCabecalho(ArquivoBinario, &cabecalho);

        //inicializa o registro
        Registro registroAtual;

        //contador para saber se algum registro contem as informações desejadas
        int registros_corretos = 0;

        //itera pelo arquivo comparando registro a registro com os campos indicados
        for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
        {
            //faz a leitura do registro no arquivo
            registroAtual =  Ler_registros(ArquivoBinario, "SEM DADO");

            //caso o registro não esteja removido
            if(registroAtual.removido == '0'){
                //compara os registros
                if(compararRegistros(&registro, &registroAtual) == 1){
                    //caso corresponda a busca é printado
                    ImprimeRegistroFunc2(registroAtual);
                    registros_corretos++;
                }   
            }
        }

        //caso não hajam registros correspondentes exibe a mensagem de erro
        if(registros_corretos == 0){
            printf("Registro inexistente.\n\n");
        }

        //registro padrão é zerado para uma nova busca
        zera_registro(&registro);

        numEscolhas--;
    }
    
    //arquivo é fechado
    fclose(ArquivoBinario);
    
}