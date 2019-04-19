#include <stdio.h>
#include <stdlib.h>

struct entrada {
	int id;
	int a, l, c;
};

//Ordena decescentemente os elementos em relacao aos volumes
//E crescentemente em relacao aos ids que possuem valores de volume iguais
void quick_sort_volumes_ids(struct entrada *entradas, int ini, int fim) {
	int i = ini;
	int j = ini;
	int volJ = 0;
	int volFim = 0;
	struct entrada aux = null;
	while (j < fim) {       //enquanto nao chegar no pivo
		volJ = entradas[j].a * entradas[j].l * entradas[j].c;   //calcula o volume do j-esimo elemento
		volFim = entradas[fim].a * entradas[fim].l * entradas[fim].c;   //calcula o elemento do pivo
		if (volJ > volFim || (entradas[j].id < entradas[fim].id && volJ == volFim)) {   //troca se satisfizer os criterios descritos acima da funcao
			aux = entradas[i];
			entradas[i] = entradas[j];
			entradas[j] = aux;
			++i;
		}
		++j;
	}
	//troca o pivo
	aux = entradas[fim];
	entradas[fim] = entradas[i];
	entradas[i] = aux;
	if (ini < i - 1) {      //ordena a parte inferior ao pivo
		quick_sort_volumes_ids(entradas, ini, i - 1);
	}
	if (i + 1 < fim) {      //ordena a parte superior ao pivo
		quick_sort_volumes_ids(entradas, i + 1, fim);
	}
	return;
}

int* solucao(struct entrada *entradas, int n, int p) {
	int *ret = (int *) malloc(p * sizeof(int));
	quick_sort_volumes_ids(entradas, 0, n - 1);     //ordena as entradas de acordo com os criterios ja definidos acima
	for (int i = 0; i < p; ++i) {
		ret[i] = entradas[i].id;        //retorna os p primeiros ids
	}
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
