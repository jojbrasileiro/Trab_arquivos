#include "create_table.h"
#include "select_from.h"
#include "select_where.h"
#include "create_index.h"
#include "insert_into.h"

int main() {
    int opcao;
    char nomeArquivoEntrada[100];
    char nomeArquivoSaida[100];

    scanf("%d", &opcao);

    //multiplex para a escolha da funcionalidade
    switch(opcao) {
        case 1:
            scanf("%s", nomeArquivoEntrada);
            scanf("%s", nomeArquivoSaida);

            create_table(nomeArquivoEntrada, nomeArquivoSaida);
            break;
        case 2:
            scanf("%s", nomeArquivoEntrada);

            select_from(nomeArquivoEntrada);

            break;
        case 3:
            scanf("%s", nomeArquivoEntrada);

            select_where(nomeArquivoEntrada);

            break;
        case 4:
            scanf("%s", nomeArquivoEntrada);
            scanf("%s", nomeArquivoSaida);

            create_index(nomeArquivoEntrada, nomeArquivoSaida);
            break;
        case 6:
            scanf("%s", nomeArquivoEntrada);
            scanf("%s", nomeArquivoSaida);

            insert_into(nomeArquivoEntrada, nomeArquivoSaida);
            break;
        default:
            printf("Opcao invalida.\n");
            break;
    }

    return 0;
}
