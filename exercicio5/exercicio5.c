#include <stdio.h>
#include <stdlib.h>

int merge(int *l, int *copia, int ini, int meio, int fim){
    int l1 = ini;
    int l2 = meio;
    int lc = ini;
    int trocas = 0;

    while (l1 <= meio - 1 && l2 <= fim){
        if(l[l1] <= l[l2]) {
            copia[lc] = l[l1];
            ++l1;
        }else {
            copia[lc] = l[l2];
            ++l2;
            trocas += meio - l1;
        }
        ++lc;
    }
    while(l1 <= meio - 1){
        copia[lc] = l[l1];
        ++l1;
        ++lc;
    }
    while(l2 <= fim){
        copia[lc] = l[l2];
        ++l2;
        ++lc;
    }
    for (lc = ini; lc <= fim; ++lc) {
        l[lc] = copia[lc];
    }
    return trocas;
}

int merge_sort_trocas(int *l, int *copia, int ini, int fim) {
    int trocas = 0;
    if(fim > ini){
        int meio = (fim + ini)/2; // calcula o meio
        trocas = merge_sort_trocas(l, copia, ini, meio); // ordena metade inferior
        trocas += merge_sort_trocas(l, copia, meio + 1, fim); // ordena metade superior
        trocas += merge(l, copia, ini, meio + 1, fim);
    }
    return trocas;
}

int solucao(int *arr, int n)
{
    // Implemente aqui sua solução
    int *copia = (int *)malloc(n * sizeof(int));
    int ret = merge_sort_trocas(arr, copia, 0, n - 1); // Atribua aqui o número de inversões
    return ret;
}

int main()
{
    int t, i;
    int T, N, C;

    scanf("%d", &T);

    for (t = 1; t <= T; t++) {

        scanf("%d", &N);
        int *municao = (int *) malloc(N * sizeof(int));

        for (i = 0; i < N; i++) {
            scanf(" %d", &municao[i]);
        }
        
        int trocas = solucao(municao, N);

        if (trocas % 2 == 0) 
            printf("Total de trocas: %d. Silva vai distribuir as caixas.\n", trocas);
        else
            printf("Total de trocas: %d. Pereira vai distribuir as caixas.\n", trocas);
    }

    return 0;
}