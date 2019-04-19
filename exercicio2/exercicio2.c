#include <stdio.h>
#include <stdlib.h>

struct entrada {
	int usuario_id;
	int *hobbies;
};

int inversoes_bubble_sort(int *hobbies, int tamanho) {
	int i = 0;
	int iteracao = 0;
	int ordenado = 0;
	int aux = 0;
	int inversoes = 0;
	int *auxHobbies = (int *) malloc(tamanho * sizeof(int));
	for(i = 0; i < tamanho; ++i){
		auxHobbies[i] = hobbies[i];
	}
	while (!ordenado) {
		ordenado = 1;
		for (i = 0; i < tamanho - iteracao - 1; ++i) {
			if (auxHobbies[i] > auxHobbies[i + 1]) {
				ordenado = 0;
				aux = auxHobbies[i];
				auxHobbies[i] = auxHobbies[i + 1];
				auxHobbies[i + 1] = aux;
				++inversoes;
			}
		}
		++iteracao;
	}
	return inversoes;
}

void quick_sort_afinidades_ids(struct entrada *entradas, int *inversoes, int ini, int fim) {
	int i = ini;
	int j = ini;
	int volJ = 0;
	int volFim = 0;
	struct entrada aux;
	while (j < fim) {       //enquanto nao chegar no pivo
		if (inversoes[j] < inversoes[fim] || (entradas[j].usuario_id < entradas[fim].usuario_id && inversoes[j] == inversoes[fim])) {   //troca se satisfizer os criterios descritos acima da funcao
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
		quick_sort_afinidades_ids(entradas, inversoes, ini, i - 1);
	}
	if (i + 1 < fim) {      //ordena a parte superior ao pivo
		quick_sort_afinidades_ids(entradas, inversoes, i + 1, fim);
	}
	return;
}

int *solucao(struct entrada *entradas, int n, int h)
{
	int i = 0;
	int *ret = (int *) malloc(n * sizeof(int));
	int *inversoes = (int *) malloc(n * sizeof(int));
	for(i = 0; i < n; ++i) {
		inversoes[i] = inversoes_bubble_sort(entradas[i].hobbies, h);
	}
	quick_sort_afinidades_ids(entradas, inversoes, 0, n - 1);
	for(i = 0; i < n; ++i) {
		ret[i] = entradas[i].usuario_id;
	}
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
