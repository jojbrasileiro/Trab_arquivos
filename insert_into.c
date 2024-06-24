#include "insert_into.h"

int insert_into(char *nomeArquivoEntrada, char *nomeArquivoIndice)
{
    int numEscolhas;
    scanf("%d", &numEscolhas);

    // incia registro que sera escrito
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
        .nomeClube = NULL};

    // abre arquivo binario no modo rb+
    FILE *ArquivoBinario = LerEscreverArquivoBinario(nomeArquivoEntrada);

    while (numEscolhas > 0)
    {
        // recebe o tamanho do registro
        int tamanho = LeRegistroStdin(&registro);

        // atualiza o tamanho
        registro.tamanhoRegistro = tamanho;

        Cabecalho cabecalho;

        fseek(ArquivoBinario, 0, SEEK_SET);

        // faz a leitura do cabeçalho
        LeCabecalho(ArquivoBinario, &cabecalho);

        // recebe o primeiro registro removido da lista pelo topo do cabeçalho
        long proxByteOffset = cabecalho.topo;
        // mantem o registro do ultimo registro vizitado para o caso de ser necessario atualizar a lista
        long antigo_proxByteOffset = proxByteOffset;

        Registro registro_removido;
        // mantem o controle do caso de haver ou não espaço para inserir o registro
        int espaco_suficiente = 0;

        for (int i = 0; i < cabecalho.nroRegRem; i++)
        {
            // move o cursor para o registro removido
            fseek(ArquivoBinario, proxByteOffset * sizeof(char), SEEK_SET);

            // faz a leitura do registro removido
            registro_removido = LerRegistrosRemovidos(ArquivoBinario, "SEM DADO");

            // verifica se o tamanho do registro removido atual comporta nossa inserção
            if (registro_removido.tamanhoRegistro >= tamanho)
            {
                // verifica se é a primeira interação para o caso de ter que atualizar o cabeçalho ou outro registro da lista
                if (i == 0)
                {
                    cabecalho.topo = registro_removido.Prox;
                }
                else
                {
                    // volta o cursor para o registro anterior e atualiza o prox removido
                    fseek(ArquivoBinario, (antigo_proxByteOffset + 5) * sizeof(char), SEEK_SET);
                    fwrite(&registro_removido.Prox, sizeof(long), 1, ArquivoBinario);
                }

                // move o cursor para o registro
                fseek(ArquivoBinario, proxByteOffset * sizeof(char), SEEK_SET);

                // atualiza o tamanho do registro novo com o espaço recebido
                registro.tamanhoRegistro += registro_removido.tamanhoRegistro - tamanho;

                // escreve o registro e adiciona o lixo
                EscreveRegistro(ArquivoBinario, registro);
                EscreveLixo(ArquivoBinario, registro_removido.tamanhoRegistro - tamanho);

                // atualiza o cabeçalho
                cabecalho.nroRegArq += 1;
                cabecalho.nroRegRem -= 1;
                EscreveCabecalho(ArquivoBinario, cabecalho);

                espaco_suficiente = 1;

                break;
            }

            if (registro_removido.Prox == -1)
            {
                break;
            }

            // atualiza novos bytesoffsets
            antigo_proxByteOffset = proxByteOffset;
            proxByteOffset = registro_removido.Prox;

            zera_registro(&registro_removido);
        }

        // caso onde não ha espaço no arquivo
        if (espaco_suficiente == 0)
        {
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
    // roda a funcionalidade 4 para gerar o indice
    create_index(nomeArquivoEntrada, nomeArquivoIndice);
}
