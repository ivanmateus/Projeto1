#include <stdio.h>
#include <stdlib.h>

struct entrada {
    int x, y, z, w;
};

int *given_taken(struct entrada *entradas, int *teams, int j, int m) {
    int *ret = (int *)malloc(2 * sizeof(int));
    ret[0] = 0;
    ret[1] = 0;
    for (int i = 0; i < m; i++) {
        if (entradas[i].x == teams[j]) {
            ret[0] += entradas[i].y;
            ret[1] += entradas[i].w;
        } else if (entradas[i].z == teams[j]) {
            ret[0] += entradas[i].w;
            ret[1] += entradas[i].y;
        }
    }
    return ret;
}

int check_for_tie(struct entrada *entradas, int *points, int *teams, int j, int m, int fim) {
    int should_switch = 0;
    int a_given = given_taken(entradas, teams, j, m)[0];
    int a_taken = given_taken(entradas, teams, j, m)[1];

    int b_given = given_taken(entradas, teams, fim, m)[0];
    int b_taken = given_taken(entradas, teams, fim, m)[1];

    float a_avg = a_taken != 0 ? (float)a_given / a_taken : (float)a_given;
    float b_avg = b_taken != 0 ? (float)b_given / b_taken : (float)b_given;

    if (a_avg < b_avg) {
        should_switch = 1;
    } else if (a_avg == b_avg) {
        if (a_given < b_given) {
            should_switch = 1;
        } else if (a_given = b_given) {
            if (teams[j] > teams[fim]) {
                should_switch = 1;
            }
        }
    }
    return should_switch;
}

void quick_sort_recursivo(struct entrada *entradas, int *teams, int n, int m, int *points, int ini,
                          int fim) {
    int i = ini, j, aux;
    for (j = ini; j < fim; j++)
        if (points[j] > points[fim]) {
            aux = points[i];
            points[i] = points[j];
            points[j] = aux;

            aux = teams[i];
            teams[i] = teams[j];
            teams[j] = aux;
            i++;
        } else if (points[j] == points[fim]) {
            if (check_for_tie(entradas, points, teams, j, m, fim) == 1) {
                aux = points[i];
                points[i] = points[j];
                points[j] = aux;

                aux = teams[i];
                teams[i] = teams[j];
                teams[j] = aux;
                i++;
            }
        }
    aux = points[fim];
    points[fim] = points[i];
    points[i] = aux;
    if (ini > i - 1) quick_sort_recursivo(entradas, teams, n, m, points, ini, i - 1);
    if (i + 1 > fim) quick_sort_recursivo(entradas, teams, n, m, points, i + 1, fim);
    return;
}

void sort_both(struct entrada *entradas, int *points, int *teams, int n, int m) {
    quick_sort_recursivo(entradas, teams, n, m, points, 0, n - 1);
    return;
}

// Função para cálculo de pontos do jogo
// Retorna um 'vetor' com os pontos obtidos de cada time
// [2,1] = Time 'x' ganha 2 pts e Time 'z' ganha 1pt
int *get_points(struct entrada ent) {
    int *points = (int *)malloc(2 * sizeof(int));
    points[0] = 0;
    points[1] = 0;
    if (ent.y > ent.w) {
        points[0] = 2;
        points[1] = 1;
    } else if (ent.y < ent.w) {
        points[1] = 2;
        points[0] = 1;
    }
    return points;
}

int *solucao(struct entrada *entradas, int m, int n_teams) {
    int *ret = (int *)malloc(n_teams * sizeof(int));
    // Implemente aqui sua solução

    // Vetor com a pontuação dos times
    int *team_points = (int *)malloc(n_teams * sizeof(int));

    // Adiciona os pontos de cada time por jogos ao vetor team_points com o
    // auxílio do método get_points
    for (int i = 0; i < m; i++) {
        team_points[entradas[i].x - 1] += get_points(entradas[i])[0];
        team_points[entradas[i].z - 1] += get_points(entradas[i])[1];
    }

    // Popula o vetor ret com os times em ordem crescente
    for (int i = 0; i < n_teams; i++) {
        ret[i] = i + 1;
    }

    sort_both(entradas, team_points, ret, n_teams, m);
    return ret;
}

int main() {
    int *ret;
    int t, i, j;
    int T, N;

    scanf("%d", &T);

    for (t = 0; t < T; t++) {
        scanf("%d", &N);

        int m = (int)(N * (N - 1) / 2);
        struct entrada *entradas = (struct entrada *)malloc(m * sizeof(struct entrada));
        for (i = 0; i < m; i++) {
            scanf("%d %d %d %d", &entradas[i].x, &entradas[i].y, &entradas[i].z, &entradas[i].w);
        }

        ret = solucao(entradas, m, N);

        printf("Caso de teste %d\n", t);
        for (i = 0; i < N; i++)
            if (i + 1 < N)
                printf("%d ", ret[i]);
            else
                printf("%d\n", ret[i]);
    }

    return 0;
}
