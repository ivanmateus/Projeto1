#include <stdio.h>
#include <stdlib.h>

int merge(int *l, int *copia, int ini, int meio, int fim){
    int l1 = ini;   // comeco do subvetor da esquerda
    int l2 = meio;  // comeco do subvetor da direita
    int lc = ini;   // posicao do vetor copia
    int trocas = 0;

    while (l1 <= meio - 1 && l2 <= fim){ //enquanto os vetores nao terminarem
        if(l[l1] <= l[l2]) { // se o valor na posicao l1 for menor ou igual que o da posicao l2, nao conta a troca
            copia[lc] = l[l1];
            ++l1;
        }else { // senao, conta
            copia[lc] = l[l2];
            ++l2;
            // nesse caso, o valor das trocas vai ser esse, pois
            // se l[l1] > l[l2], entao significa que todos os valores
            // de l1 + 1 ate meio tambem vao ser maiores que l[l2], pois
            // os vetores sao ordenados. Entao é como se l[l2] fizesse
            // trocas com todos esses elementos. 
            trocas += meio - l1;
        }
        ++lc;
    }
    while(l1 <= meio - 1){ // termina de copiar, se nao terminou
        copia[lc] = l[l1];
        ++l1;
        ++lc;
    }
    while(l2 <= fim){ // termina de copiar, se nao terminou
        copia[lc] = l[l2];
        ++l2;
        ++lc;
    }
    for (lc = ini; lc <= fim; ++lc) { // copia tudo para o vetor original
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
        trocas += merge(l, copia, ini, meio + 1, fim); // faz o merge das duas metades ordenadas
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