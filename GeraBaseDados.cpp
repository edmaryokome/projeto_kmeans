//Declaração das bibliotecas para usar as funções do programa
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main() {
    int n = 500000; //Quantidade de pontos que serão gerados
    int d = 2;   // Dimensão dos dados, neste caso sera de duas dimensões para o plano cartesino x e y

    FILE *arquivo = fopen("dados.txt", "w");  // Cria o arquivo "dados.txt" para escrita de dados

    //Verifica se conseguiu abri o arquivo, senão conseguir emite uma mensagem de erro e encerra o programa
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    // Escreve n e d no arquivo (primeira linha)
    fprintf(arquivo, "%d %d\n", n, d);

    // Inicializa a semente do gerador aleatório com o tempo atual 
    srand(time(NULL));

    //A proposta de gerar dados é que sejam gerados três agrupamentos de dados com características semelhantes 80%
    //E também dados fora desse agrupamento de dados 20%
    //Laço para gerar os pontos
    for (int i = 0; i < n; i++) {

        double x, y; //Variáveis que receberam os valores

        // Controle de probabilidade
        int tipo = rand() % 10; // Gera um número de 0 a 9
        
        // 80% dos casos -> gera pontos do agrupamento
        if (tipo < 8) {
            
            // Escolhe um dos 3 clusters (0, 1 ou 2)
            int cluster = rand() % 3;

            if (cluster == 0) {
                // Cluster 1: região próxima de (1,1) até (3,3)
                x = ((double) rand() / RAND_MAX) * 2 + 1;
                y = ((double) rand() / RAND_MAX) * 2 + 1;
            }
            else if (cluster == 1) {
                // Cluster 2: região próxima de (5,5) até (7,7)
                x = ((double) rand() / RAND_MAX) * 2 + 5;
                y = ((double) rand() / RAND_MAX) * 2 + 5;
            }
            else {
                // Cluster 3: região próxima de (9,1) até (11,3)
                x = ((double) rand() / RAND_MAX) * 2 + 9;
                y = ((double) rand() / RAND_MAX) * 2 + 1;
            }

            // Pequeno ruído (perturbação leve nos pontos do cluster)
            x += ((double) rand() / RAND_MAX - 0.5);
            y += ((double) rand() / RAND_MAX - 0.5);
        }
        else {
            // 20% dos casos -> gera pontos totalmente aleatórios (outliers)
            // valor entre 0 e 15
            x = ((double) rand() / RAND_MAX) * 15;
            y = ((double) rand() / RAND_MAX) * 15;
        }
        
        // Escreve o ponto gerado no arquivo 
        fprintf(arquivo, "%lf %lf\n", x, y);
    }

    fclose(arquivo); //Fecha o arquivo

    printf("Arquivo dados.txt gerado com 80%% cluster e 20%% ruido!\n");

}
