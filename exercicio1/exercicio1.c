#include <stdio.h>
#include <stdlib.h>

struct entrada {
	int id;
	int a, l, c;
};

void quick_sort_volumes_ids(struct entrada *entradas, int ini, int fim) {
	int i = ini;
	int j = ini;
	int volJ = 0;
	int volFim = 0;
	struct entrada aux;
	while (j < fim) {
		volJ = entradas[j].a * entradas[j].l * entradas[j].c;
		volFim = entradas[fim].a * entradas[fim].l * entradas[fim].c;
		if (volJ > volFim || (entradas[j].id < entradas[fim].id && volJ == volFim)) {
			aux = entradas[i];
			entradas[i] = entradas[j];
			entradas[j] = aux;
			++i;                                                                                                                                                                         // mais um elemento menor do que o pivo
		}
		++j;
	}
	aux = entradas[fim];
	entradas[fim] = entradas[i];
	entradas[i] = aux;
	if (ini < i - 1) {
		quick_sort_volumes_ids(entradas, ini, i - 1);
	}                                                                                                              // processa metade inferior
	if (i + 1 < fim) {
		quick_sort_volumes_ids(entradas, i + 1, fim);
	}
	return;
}

int* solucao(struct entrada *entradas, int n, int p) {
	int *ret = (int *) malloc(p * sizeof(int));
	quick_sort_volumes_ids(entradas, 0, n - 1);
	for (int i = 0; i < p; ++i) {
		ret[i] = entradas[i].id;
	}                                                                                               // processa metade superior
	return ret;
}

int main()
{
	int *ret;
	int t, i;
	int T, N, P;

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
