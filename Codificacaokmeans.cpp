//Inclusão de bibliotecas para usar as funções necessária
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Define a quantidade máxima de interação que o programa pode ter (cálculo distância e centróides)
#define ITER_MAXIMA 500000


// OBS: as fuções foram nomeadas com o mesmo nome, assim deve ser desabilitada as funções que não serão executada

// Função para calcular distância Euclidiana
/**
double calcDistancia(double *a, double *b, int dimensao) {
    double soma = 0.0;
    for (int i = 0; i < dimensao; i++) {
        soma += pow(a[i] - b[i], 2);
    }
    return sqrt(soma);
}
*/

/**
// Função para calcular Distância de Manhattan
double calcDistancia(double *a, double *b, int dimensao) {
    double soma = 0.0;
    for (int i = 0; i < dimensao; i++) {
        soma += fabs(a[i] - b[i]);
    }
    return soma;
}
*/

/**
// Função para calcular distância Coseno
double calcDistancia(double *a, double *b, int dimensao) {
    double dot = 0.0;  //Produto escalar
    double norm_a = 0.0; //tamanho do vetor a
    double norm_b = 0.0; //tamanho do vetor b
    for (int i = 0; i < dimensao; i++) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    
    // Evitar divisão por zero
    if (norm_a == 0 || norm_b == 0) {
        return 1.0; // máxima distância
    }

    double cos_sim = dot / (sqrt(norm_a) * sqrt(norm_b));
    return 1.0 - cos_sim;
}
*/

// Função para calcular distância de Minkowski
double calcDistancia(double *a, double *b, int dimensao, double p) {
    double soma = 0.0;
    for (int i = 0; i < dimensao; i++) {
        soma += pow(fabs(a[i] - b[i]), p);
    }
    return pow(soma, 1.0 / p);
}

/**
// Função para calcular distância de Chebyshev
double calcDistancia(double *a, double *b, int dimensao) {
    double max = 0.0;
    
    for (int i = 0; i < dimensao; i++) {
        double diferenca = fabs(a[i] - b[i]);
        if (diferenca > max) {
            max = diferenca;
        }
    }
    
    return max;
}
*/

main(){

   int n, d, k; // n = número de pontos, d = dimensões, k = número de clusters
   clock_t tempoInicial, tempoFinal; //Variaveis para receber o tempo inicial e tempo final
   double tempo_execucao; //Variavel para receber o cálculo do tempo de execução
   int comparacoes = 0;  //Varivael para receber a quantidade de comparações
   int trocas = 0;  //Variavel para contar quantas vezes um ponto muda de grupo entre iterações
   double p = 3.0;  //Esta variável é para ser usada na distância de Minkowski, habilitar quando for usar Minkowski
   
   
   // Abre o arquivo de dados para leitura
    FILE *file = fopen("dados.txt", "r");
    
    // Verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
    	
    	printf("Erro ao abrir o arquivo!\n");
        return 1; // Encerra o programa se não conseguir abrir
    }
    
    // Lê do arquivo o número de pontos (n) e dimensões (d)
    fscanf(file, "%d %d", &n, &d);
    
    printf("n = %d | d = %d\n", n, d); // Exibe os valores lidos
    
    // Solicita ao usuário o número de clusters - Desabilitei essa linha, porque será definido como padrão 3 agruapamentos
    //printf("Informe o numero de clusters (k): ");
    //scanf("%d", &k);
    k=3;
    
    
    // Alocação dinâmica da matriz de dados
    double **dados = (double **) malloc(n * sizeof(double *));
    
    // Alocação dos centróides
    double **centroide = (double **) malloc(k * sizeof(double *));
    
    // Vetor que guarda o cluster de cada ponto
    int *rotulo = (int *) malloc(n * sizeof(int));
    
    // Vetor que conta quantos pontos há em cada cluster
    int *contar = (int *) malloc(k * sizeof(int));
    
    // Verifica se houve erro de alocação
    if (dados == NULL || centroide == NULL || rotulo == NULL || contar == NULL) {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }
    
    // Aloca cada linha da matriz de dados
    for (int i = 0; i < n; i++) {
        dados[i] = (double *) malloc(d * sizeof(double));
    }
    
    // Aloca cada centróide
    for (int i = 0; i < k; i++) {
        centroide[i] = (double *) malloc(d * sizeof(double));
    }
    
    // Leitura dos dados do arquivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            fscanf(file, "%lf", &dados[i][j]); // Lê cada valor
        }
    }
    
    fclose(file); // Fecha o arquivo após leitura
    
    // Inicializa rótulos com valor inválido
    for (int i = 0; i < n; i++) {
        rotulo[i] = -1;
    }
    
        // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Escolhe centróides iniciais aleatórios
    for (int i = 0; i < k; i++) {
        int idx = rand() % n; // Seleciona um ponto aleatório

        for (int j = 0; j < d; j++) {
            centroide[i][j] = dados[idx][j]; // Copia o ponto como centróide
        }
    }    
    
    tempoInicial = time(NULL);  //Inicializando a variável
    tempoInicial = clock();     //Atribui a variável o tempo inicial do consumo do processador
    //OBS: A ideia desse programa é medir quanto tempo que leva para fazer o agrupamento dos dados
    //Portanto não está considerando o tempo gasto para as atividades antes e depois do agrupamento de dados
    
    // Loop principal do K-Means
    for (int iter = 0; iter < ITER_MAXIMA; iter++) {
    	
    	   int trocas_iter = 0;

        // Etapa 1: Atribuição dos pontos aos clusters
        for (int i = 0; i < n; i++) {
            double dist_min = INFINITY; // Inicializa com valor infinito
            
            int grupo = 0; // Cluster mais próximo

            // Calcula distância para cada centróide
            for (int j = 0; j < k; j++) {
                //double dist = calcDistancia(dados[i], centroide[j], d); //Desabilitar quando usar a Minkowski
                double dist = calcDistancia(dados[i], centroide[j], d, p);  //Habilitar quando usar a Minkwonski
                
                comparacoes++;                // Conta a comparação abaixo
                if (dist < dist_min) {        // Verifica se é a menor distância
                    dist_min = dist;
                     grupo = j;
                }
            }
            
             // Verifica se houve troca de cluster
            if (rotulo[i] != grupo) {
                trocas++;
                trocas_iter++;
                rotulo[i] = grupo;
            }   
        }
        
       
        printf("Iteracao %d: %d mudanca grupo\n", iter, trocas_iter);
        // Critério de parada (convergência)
        if (trocas_iter == 0) {
            printf("Convergiu na iteracao %d\n", iter);
            break;
        }

        // Zera contadores e centróides
        for (int j = 0; j < k; j++) {
            contar[j] = 0; // Nenhum ponto contado ainda

            for (int l = 0; l < d; l++) {
                centroide[j][l] = 0.0; // Zera soma do centróide
            }
        }
        // Soma os pontos de cada cluster
        for (int i = 0; i < n; i++) {
            int c = rotulo[i]; // Cluster do ponto
            contar[c]++; // Incrementa contador

            for (int j = 0; j < d; j++) {
                centroide[c][j] += dados[i][j]; // Soma coordenadas
            }
        }
        
        // Calcula a média (novo centróide)
        for (int j = 0; j < k; j++) {

            if (contar[j] == 0) continue; // Evita divisão por zero

            for (int l = 0; l < d; l++) {
            	 centroide[j][l] /= contar[j]; // Média dos pontos
            }
        }
  }
  
    tempoFinal = time(NULL); //Inicializando a variável
    tempoFinal = clock();    ////Atribui a variável o tempo final do consumo do processador
    
    //Fazer a conversão de tempo para segundos:
    tempo_execucao = (double)(tempoFinal - tempoInicial) / CLOCKS_PER_SEC;
    
  
    // Exibe os resultados finais
    printf("\nAgrupamentos:\n");

    for (int i = 0; i < n; i++) {
        printf("Ponto %d -> Grupo %d\n", i, rotulo[i]);
    }
     //Apresenta o tempo de execução do agrupamento - um dos critérios para analisar a complexidade de um algoritmo
     printf("\nTempo de execucao: %f segundos\n", tempo_execucao);
     
     //Apresenta o número de comparaçõo - um dos critérios para analisar a complexidade de um algoritmo
     printf("Numero de comparacoes: %d\n", comparacoes);
     
     //Apresenta o número de vezes que mudou de ponto
     printf("\nNumero total de trocas: %d\n", trocas);
     
    // Liberação de memória
    for (int i = 0; i < n; i++) {
        free(dados[i]);
    }

    for (int i = 0; i < k; i++) {
        free(centroide[i]);
    }
    
    free(dados);
    free(centroide);
    free(rotulo);
    free(contar);
	
}
