#include "delete_from.h"

int delete_from(char *nomeArquivoEntrada, char *nomeArquivoIndice)
{

    // string que armazena o nome do campo selecionado
    char campo[20];

    // numero de buscas e campos por busca
    int numEscolhas;
    int numCampos;
    int buscaId = 0;
    int remocoes = 0;
    long int prox_inicial = -1;
    scanf("%d", &numEscolhas);

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
        .nomeClube = NULL};

    // contador de buscas
    int count = 1;

    // arquivo inicializado
    FILE *ArquivoBinario = LerEscreverArquivoBinario(nomeArquivoEntrada);
    EspacoDisponivel *lista = NULL;
    // inicializa o cabeçalho
    Cabecalho cabecalho;
    LeCabecalho(ArquivoBinario, &cabecalho);

    if (cabecalho.nroRegRem != 0)
    {

        fseek(ArquivoBinario, cabecalho.topo, SEEK_SET);
        Registro registroRemovido;
        for (int i = 0; i < (cabecalho.nroRegRem); i++)
        {

            registroRemovido = LerRegistrosRemovidos(ArquivoBinario, "SEM DADO");

            long byteoffsetRemovido = ftell(ArquivoBinario);
            // verifica se o registro esta removido
            if (registroRemovido.removido == '1')
            {
                long int prox_byteoffset = registroRemovido.Prox;
                // ImprimeRegistro(registroRemovido);
                InserirEspacoDisponivel(&lista, registroRemovido.tamanhoRegistro, (byteoffsetRemovido - registroRemovido.tamanhoRegistro));
                fseek(ArquivoBinario, prox_byteoffset, SEEK_SET);
            }
        }
        // fseek(ArquivoBinario, 25, SEEK_SET);
    }
    // looping pelo numero de ebuscas do usuario
    while (numEscolhas > 0)
    {
        scanf("%d", &numCampos);
        buscaId = 0;
        // for pelo numero de campos indicados pelo usuario
        for (int i = 0; i < numCampos; i++)
        {
            // le o campo
            scanf("%s", campo);
            // Define se a busca utilizada sera por id ou por campo
            if (strcmp(campo, "id") == 0)
            {
                buscaId = 1;
                create_index_sem_leitura(nomeArquivoEntrada, nomeArquivoIndice);
                ArquivoBinario = LerEscreverArquivoBinario(nomeArquivoEntrada);
            }
            // determina qual o campo e faz e faz o armazenamento apropriado no registro padrão
            determina_campo(campo, &registro);

            // zera a string campo
            memset(campo, 0, sizeof(campo));
        }

        // garante que o arquivo inicia no inicio em todas as iterações
        fseek(ArquivoBinario, 0, SEEK_SET);

        // le o cabeçalho
        LeCabecalho(ArquivoBinario, &cabecalho);
        // inicializa o registro
        Registro registroAtual;

        // contador para saber se algum registro contem as informações desejadas
        int registros_corretos = 0;
        // Itera pelo arquivo indice procurando um id correspondente
        if (buscaId)
        {
            // Verifica se o id existe no arquivo de indice
            int byteBuscado = BuscaId(nomeArquivoIndice, registro.id);
            if (byteBuscado != -1)
            {
                fseek(ArquivoBinario, byteBuscado, SEEK_SET);
                registroAtual = LerRegistros(ArquivoBinario, "SEM DADO");
                // Atualiza lista de lógicamente removidos
                InserirEspacoDisponivel(&lista, registroAtual.tamanhoRegistro, byteBuscado);
                fseek(ArquivoBinario, (byteBuscado + registroAtual.tamanhoRegistro) * sizeof(char), SEEK_SET);
                registros_corretos++;
                remocoes++;
            }
        }
        // itera pelo arquivo comparando registro a registro com os campos indicados
        else
        {
            for (int i = 0; i < (cabecalho.nroRegArq + cabecalho.nroRegRem); i++)
            {
                // faz a leitura do registro no arquivo
                int long byteOffSet = ftell(ArquivoBinario);
                registroAtual = LerRegistros(ArquivoBinario, "SEM DADO");
                // caso o registro não esteja removido
                if (registroAtual.removido == '0')
                {
                    // compara os registros
                    if (compararRegistros(&registro, &registroAtual) == 1)
                    {
                        InserirEspacoDisponivel(&lista, registroAtual.tamanhoRegistro, byteOffSet);
                        // Avança para o pŕoximo
                        fseek(ArquivoBinario, (byteOffSet + registroAtual.tamanhoRegistro) * sizeof(char), SEEK_SET);
                        registros_corretos++;
                        remocoes++;
                    }
                }
                zera_registro(&registroAtual);
            }
        }
        zera_registro(&registro);

        numEscolhas--;
    }

    // Remove os registros salvo na lista para remoção
    EspacoDisponivel *atual = lista;
    Registro reg;
    while (atual != NULL)
    {
        int tam = atual->tamanho;
        EspacoDisponivel *prox = atual->prox;
        fseek(ArquivoBinario, atual->offset, SEEK_SET);
        if (prox != NULL)
        {
            RemoveRegistro(ArquivoBinario, tam, prox->offset);
        }
        else
        {
            RemoveRegistro(ArquivoBinario, tam, (long)-1);
        }
        atual = atual->prox;
    }
    // printf("Foram removidos %d\n", remocoes);
    AtualizaCabecalho(ArquivoBinario, cabecalho, lista->offset, remocoes);
    // #####################

    // arquivo é fechado
    fclose(ArquivoBinario);

    binarioNaTela(nomeArquivoEntrada);
    create_index(nomeArquivoEntrada, nomeArquivoIndice);
    // Da free no malloc da lista
    LiberarListaEspacoDisponivel(lista);
}
