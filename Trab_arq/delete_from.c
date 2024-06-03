#include "delete_from.h"

void atualiza_topo(FILE* ArquivoBinario,Cabecalho cabecalho,long int byteOffSet){
    cabecalho.topo = byteOffSet;
    cabecalho.nroRegArq--;
    cabecalho.nroRegRem++;
    EscreveCabecalho(ArquivoBinario, cabecalho);
}

int delete_from(char *nomeArquivoEntrada, char *nomeArquivoIndice){
    
    //string que armazena o nome do campo selecionado
    char campo[20];

    //numero de buscas e campos por busca
    int numEscolhas;
    int numCampos;
    scanf("%d", &numEscolhas);

    // create_index_sem_leitura(nomeArquivoEntrada, nomeArquivoIndice);
    // registro padrão inicializado, a ideia é que os campos só sejam comparados se diferentes desses valores, uma vez
    // são valores impossiveis de serem assumidos
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
    FILE *ArquivoBinario = lerEscreverArquivoBinario(nomeArquivoEntrada);

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
        ImprimeCabecalho(cabecalho);

        //itera pelo arquivo comparando registro a registro com os campos indicados
        for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
        {
            //faz a leitura do registro no arquivo
            long int byteoffset = ftell(ArquivoBinario);
            registroAtual =  Ler_registros(ArquivoBinario, "SEM DADO");
            // caso o registro não esteja removido
            if(registroAtual.removido == '0'){
                //compara os registros
                if(compararRegistros(&registro, &registroAtual) == 1){
                    //caso corresponda a busca é printado
                    ImprimeRegistro(registroAtual);
                    int tam_reg = registroAtual.tamanhoRegistro;
                    printf("Tamnho do arquivo %d\n", tam_reg);
                    // volta o ponteiro para a posição inicial da leitura do registro
                    // printf("Posição do byte %ld\n",byteoffset);
                    // printf("Posição antes fseek %ld\n", ftell(ArquivoBinario));

                    //Atualiza o topo com valor do byteOffSet do registro removido
                    atualiza_topo(ArquivoBinario, cabecalho, byteoffset);
                    fseek(ArquivoBinario, 0, SEEK_SET);
                    LeCabecalho(ArquivoBinario, &cabecalho);
                    ImprimeCabecalho(cabecalho);
                    
                    //Remove lógicamente o registro
                    fseek(ArquivoBinario, byteoffset, SEEK_SET);
                    printf("Posição depois fseek %ld\n", ftell(ArquivoBinario));
                    RemoveRegistro(ArquivoBinario,tam_reg,cabecalho);
                    
                    // Avança para o pŕoximo
                    printf("Posição depois da escrita %ld\n", ftell(ArquivoBinario));
                    fseek(ArquivoBinario, (tam_reg - 13) * sizeof(char), SEEK_CUR);
                    printf("Posição depois do seek da escrita %ld\n", ftell(ArquivoBinario));
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
    
    binarioNaTela(nomeArquivoEntrada);
    create_index (nomeArquivoEntrada, nomeArquivoIndice);
}