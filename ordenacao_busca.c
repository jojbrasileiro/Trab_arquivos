#include "ordenacao_busca.h"

// Função para ordenar um array de inteiros usando o algoritmo de ordenação por seleção
void selection_sort(int* lista, int lista_tam) {
    int i, j, minIndex, temp;

    for (i = 0; i < lista_tam - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < lista_tam; j++) {
            if (lista[j] < lista[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = lista[i];
            lista[i] = lista[minIndex];
            lista[minIndex] = temp;
        }
    }
}

// Função para realizar uma busca binária em um array de inteiros
int busca_binaria(int* lista, int lista_tam, int valor) {
    int esquerda = 0;
    int direita = lista_tam - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        if (lista[meio] == valor) {
            return meio; // Elemento encontrado, retorna o índice
        } else if (lista[meio] < valor) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return 0; // Elemento não encontrado
}
