//Esse coódigo não tem o intuído de ser executado, a função é apresentar o cálculo da complexidade usando a notação Big O

#include <stdio.h>      // O(1)
#include <stdlib.h>     // O(1)
#include <math.h>       // O(1)
#include <time.h>       // O(1)

#define ITER_MAXIMA 100 // O(1)


// Função para calcular distância Euclidiana
double calcDistancia(double *a, double *b, int dimensao) {

    double soma = 0.0;                          // O(1)

    for (int i = 0; i < dimensao; i++) {        // O(d)
                                                // (inicialização O(1) + d comparações + d incrementos)

        soma += pow(a[i] - b[i], 2);            // O(1) por iteração:
                                                // acesso a[i] O(1)
                                                // acesso b[i] O(1)
                                                // subtração O(1)
                                                // pow(...) O(1)
                                                // soma acumulada O(1)
    }                                           // Executado d vezes ? O(d)

    return sqrt(soma);                          // O(1)
}

// Função para calcular Distância de Manhattan
double calcDistancia(double *a, double *b, int dimensao) {

    double soma = 0.0;                          // O(1)

    for (int i = 0; i < dimensao; i++) {        // O(d)
                                                // (inicialização O(1) + d comparações + d incrementos)

        soma += fabs(a[i] - b[i]);              // O(1) por iteração:
                                                // acesso a[i] O(1)
                                                // acesso b[i] O(1)
                                                // subtração O(1)
                                                // fabs(...) O(1)
                                                // soma acumulada O(1)
    }                                           // Executado d vezes ? O(d)

    return soma;                                // O(1)
}

// Função para calcular distância Coseno
double calcDistancia(double *a, double *b, int dimensao) {

    double dot = 0.0;                          // O(1)
    double norm_a = 0.0;                       // O(1)
    double norm_b = 0.0;                       // O(1)

    for (int i = 0; i < dimensao; i++) {       // O(d)
                                               // (inicialização O(1) + d comparações + d incrementos)

        dot += a[i] * b[i];                    // O(1)
                                               // acesso a[i] O(1)
                                               // acesso b[i] O(1)
                                               // multiplicação O(1)
                                               // soma acumulada O(1)

        norm_a += a[i] * a[i];                 // O(1)
                                               // acesso a[i] O(1)
                                               // multiplicação O(1)
                                               // soma acumulada O(1)

        norm_b += b[i] * b[i];                 // O(1)
                                               // acesso b[i] O(1)
                                               // multiplicação O(1)
                                               // soma acumulada O(1)
    }                                          // Executado d vezes ? O(d)

    if (norm_a == 0 || norm_b == 0) {          // O(1)
        return 1.0;                            // O(1)
    }

    double cos_sim = dot / (sqrt(norm_a) * sqrt(norm_b)); // O(1)
                                                          // sqrt O(1)
                                                          // multiplicação O(1)
                                                          // divisão O(1)

    return 1.0 - cos_sim;                     // O(1)
}

// Função para calcular distância de Minkowski
double calcDistancia(double *a, double *b, int dimensao, double p) {

    double soma = 0.0;                          // O(1)

    for (int i = 0; i < dimensao; i++) {        // O(d)
                                                // (inicialização O(1) + d comparações + d incrementos)

        soma += pow(fabs(a[i] - b[i]), p);      // O(1) por iteração:
                                                // acesso a[i] O(1)
                                                // acesso b[i] O(1)
                                                // subtração O(1)
                                                // fabs(...) O(1)
                                                // pow(..., p) O(1)
                                                // soma acumulada O(1)
    }                                           // Executado d vezes ? O(d)

    return pow(soma, 1.0 / p);                  // O(1)
                                                // divisão O(1)
                                                // pow(...) O(1)
}


// Função de distância (Chebyshev)
double calcDistancia(double *a, double *b, int dimensao) {
    double max = 0.0;                    // O(1)
    for (int i = 0; i < dimensao; i++) { // O(d)
        double diferenca = fabs(a[i] - b[i]); // O(1)
        if (diferenca > max) {                // O(1)
            max = diferenca;                 // O(1)
        }
    }
    return max; // O(1)
}

int main() {

   int n, d, k;                  // O(1)
   clock_t tempoInicial, tempoFinal; // O(1)
   double tempo_execucao;        // O(1)
   int comparacoes = 0;          // O(1)
   int trocas = 0;               // O(1)

   FILE *file = fopen("dados.txt", "r"); // O(1)

   if (file == NULL) { // O(1)
        printf("Erro ao abrir o arquivo!\n"); // O(1)
        return 1; // O(1)
    }

    fscanf(file, "%d %d", &n, &d); // O(1)

    printf("n = %d | d = %d\n", n, d); // O(1)

    printf("Informe o numero de clusters (k): "); // O(1)
    scanf("%d", &k); // O(1)

    double **dados = (double **) malloc(n * sizeof(double *)); // O(n)
    double **centroide = (double **) malloc(k * sizeof(double *)); // O(k)
    int *rotulo = (int *) malloc(n * sizeof(int)); // O(n)
    int *contar = (int *) malloc(k * sizeof(int)); // O(k)

    if (dados == NULL || centroide == NULL || rotulo == NULL || contar == NULL) { // O(1)
        printf("Erro de alocacao de memoria\n"); // O(1)
        return 1; // O(1)
    }

    for (int i = 0; i < n; i++) { // O(n)
        dados[i] = (double *) malloc(d * sizeof(double)); // O(d)
    } // total ? O(n·d)

    for (int i = 0; i < k; i++) { // O(k)
        centroide[i] = (double *) malloc(d * sizeof(double)); // O(d)
    } // total ? O(k·d)

    for (int i = 0; i < n; i++) {        // O(n)
        for (int j = 0; j < d; j++) {    // O(d)
            fscanf(file, "%lf", &dados[i][j]); // O(1)
        }
    } // total ? O(n·d)

    fclose(file); // O(1)

    for (int i = 0; i < n; i++) { // O(n)
        rotulo[i] = -1; // O(1)
    }

    srand(time(NULL)); // O(1)

    for (int i = 0; i < k; i++) { // O(k)
        int idx = rand() % n; // O(1)
        for (int j = 0; j < d; j++) { // O(d)
            centroide[i][j] = dados[idx][j]; // O(1)
        }
    } // total ? O(k·d)

    tempoInicial = clock(); // O(1)

    for (int iter = 0; iter < ITER_MAXIMA; iter++) { // O(I)

        int trocas_iter = 0; // O(1)

        for (int i = 0; i < n; i++) { // O(n)
            double dist_min = INFINITY; // O(1)
            int grupo = 0; // O(1)

            for (int j = 0; j < k; j++) { // O(k)
                double dist = calcDistancia(dados[i], centroide[j], d); // O(d)
                comparacoes++; // O(1)

                if (dist < dist_min) { // O(1)
                    dist_min = dist;  // O(1)
                    grupo = j;        // O(1)
                }
            } // O(k·d)

            if (rotulo[i] != grupo) { // O(1)
                trocas++;            // O(1)
                trocas_iter++;       // O(1)
                rotulo[i] = grupo;   // O(1)
            }
        } // total ? O(n·k·d)

        printf("Iteracao %d: %d trocas\n", iter, trocas_iter); // O(1)

        if (trocas_iter == 0) { // O(1)
            printf("Convergiu na iteracao %d\n", iter); // O(1)
            break; // O(1)
        }

        for (int j = 0; j < k; j++) { // O(k)
            contar[j] = 0; // O(1)
            for (int l = 0; l < d; l++) { // O(d)
                centroide[j][l] = 0.0; // O(1)
            }
        } // total ? O(k·d)

        for (int i = 0; i < n; i++) { // O(n)
            int c = rotulo[i]; // O(1)
            contar[c]++; // O(1)

            for (int j = 0; j < d; j++) { // O(d)
                centroide[c][j] += dados[i][j]; // O(1)
            }
        } // total ? O(n·d)

        for (int j = 0; j < k; j++) { // O(k)
            if (contar[j] == 0) continue; // O(1)

            for (int l = 0; l < d; l++) { // O(d)
                centroide[j][l] /= contar[j]; // O(1)
            }
        } // total ? O(k·d)
    }

    tempoFinal = clock(); // O(1)

    tempo_execucao = (double)(tempoFinal - tempoInicial) / CLOCKS_PER_SEC; // O(1)

    printf("\nAgrupamentos:\n"); // O(1)

    for (int i = 0; i < n; i++) { // O(n)
        printf("Ponto %d -> Grupo %d\n", i, rotulo[i]); // O(1)
    }

    printf("\nTempo de execucao: %f segundos\n", tempo_execucao); // O(1)
    printf("Numero de comparacoes: %d\n", comparacoes); // O(1)
    printf("\nNumero total de trocas: %d\n", trocas); // O(1)

    for (int i = 0; i < n; i++) { // O(n)
        free(dados[i]); // O(1)
    }

    for (int i = 0; i < k; i++) { // O(k)
        free(centroide[i]); // O(1)
    }

    free(dados);     // O(1)
    free(centroide); // O(1)
    free(rotulo);    // O(1)
    free(contar);    // O(1)
}
