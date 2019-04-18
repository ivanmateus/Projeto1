#include <stdio.h>
#include <stdlib.h>

struct entrada {
    int id;
    int a, l, c;
};

int* solucao(struct entrada *entradas, int n, int p)
{
    int *ret = (int *) malloc(p * sizeof(int));

    // Implemente aqui sua solução

    return ret;
}

int main()
{
    int *ret;
    int t, i, j;
    int T, N, P, ID, A, L, C;

    scanf("%d", &T);

    for (t = 0; t < T; t++) {

        scanf("%d %d", &N, &P);

        struct entrada *entradas = (struct entrada *) malloc(N * sizeof(struct entrada));
        for (i = 0; i < N; i++) {
            scanf("%d %d %d %d", &entradas[i].id, &entradas[i].a, &entradas[i].l, &entradas[i].c);
        }

        ret = solucao(entradas, N, P);

        for (i = 0; i < P; i++)
            if (i + 1 < P)
                printf("%d ", ret[i]);
            else
                printf("%d\n", ret[i]);
    }

    return 0;
}
