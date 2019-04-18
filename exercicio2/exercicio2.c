#include <stdio.h>
#include <stdlib.h>

struct entrada {
    int usuario_id;
    int *hobbies;
};

int *solucao(struct entrada *entradas, int n, int h)
{
    int *ret = (int *) malloc(h * sizeof(int));

    // Implemente aqui sua solução

    return ret;
}

int main()
{
    int *ret;
    int t, i, j;
    int T, N, H;

    scanf("%d", &T);

    for (t = 0; t < T; t++) {

        scanf("%d %d", &N, &H);
        
        struct entrada *entradas = (struct entrada *) malloc(N * sizeof(struct entrada));

        for (i = 0; i < N; i++) {
            entradas[i].hobbies = (int *) malloc(H * sizeof(int));
            scanf("%d", &entradas[i].usuario_id);
            for (j = 0; j < H; j++)
                scanf(" %d", &entradas[i].hobbies[j]);
        }

        ret = solucao(entradas, N, H);

        for (i = 0; i < N; i++)
            if (i + 1 < N)
                printf("%d ", ret[i]);
            else
                printf("%d\n", ret[i]);
    }

    return 0;
}
