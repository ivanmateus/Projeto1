#include <stdio.h>
#include <stdlib.h>

struct entrada {
    int *itens;
    int *consultas;
};

// Ordenação dos itens usando quicksort
void quick_sort_recursivo(int *arr, int ini, int fim) {
    int i = ini, j, aux;
    for (j = ini; j < fim; j++)
        if (arr[j] < arr[fim]) {
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            i++;
        }
    aux = arr[fim];
    arr[fim] = arr[i];
    arr[i] = aux;
    if (ini < i - 1) quick_sort_recursivo(arr, ini, i - 1);
    if (i + 1 < fim) quick_sort_recursivo(arr, i + 1, fim);
    return;
}

void quick_sort(int *arr, int size) {
    quick_sort_recursivo(arr, 0, size - 1);
    return;
}

// Busa binária feita no vetor ordenado dos itens
int busca(int *arr, int ini, int fim, int consulta) {
    if (fim >= ini) {
        int meio = ini + (fim - ini) / 2;

        if (arr[meio] == consulta) {
            // Pequena modificação na busca binária para o caso de itens repetidos
            int i = meio;
            // Confere itens à 'esquerda' do item encontrado para conferir se há repetidos e retorna
            // o primeiro da lista
            while (arr[i - 1] == consulta) {
                i--;
            }
            return i;
        }

        if (arr[meio] > consulta) {
            return busca(arr, ini, meio - 1, consulta);
        }
        return busca(arr, meio + 1, fim, consulta);
    }

    return -1;
}

int *solucao(struct entrada entrada, int n, int c) {
    int *ret = (int *)malloc(c * sizeof(int));

    // Implemente aqui sua solução
    // Para as consultas, caso o item não exista, retorne -1
    quick_sort(entrada.itens, n);

    for (int i = 0; i < c; i++) {
        // Popula o vetor de resultados com os resultados das buscas
        ret[i] = busca(entrada.itens, 0, n - 1, entrada.consultas[i]);
    }

    return ret;
}

int main() {
    int *ret;
    int t, i;
    int T, N, C;

    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        scanf("%d %d", &N, &C);

        struct entrada entrada;
        entrada.itens = (int *)malloc(N * sizeof(int));
        entrada.consultas = (int *)malloc(C * sizeof(int));

        scanf("%d", &entrada.itens[0]);
        for (i = 1; i < N; i++) {
            scanf(" %d", &entrada.itens[i]);
        }

        scanf("%d", &entrada.consultas[0]);
        for (i = 1; i < C; i++) {
            scanf(" %d", &entrada.consultas[i]);
        }

        ret = solucao(entrada, N, C);

        for (i = 0; i < C; i++) {
            if (ret[i] >= 0)
                printf("Caso %d, item %d na posicao %d.\n", t, entrada.consultas[i], ret[i]);
            else
                printf("Caso %d, item %d nao existe.\n", t, entrada.consultas[i]);
        }
    }

    return 0;
}