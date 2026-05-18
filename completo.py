import math
import random
import time
import matplotlib.pyplot as plt

MAX_ITER = 10  # reduzido para visualização

# Distância Euclidiana
def distance(a, b):
    return math.sqrt(sum((a[i] - b[i]) ** 2 for i in range(len(a))))


def plot_clusters(data, labels, centroids, iteration):
    plt.clf()  # limpa gráfico anterior

    # Separar pontos por cluster
    k = len(centroids)
    for i in range(k):
        x = [data[j][0] for j in range(len(data)) if labels[j] == i]
        y = [data[j][1] for j in range(len(data)) if labels[j] == i]
        plt.scatter(x, y, label=f"Cluster {i}")

    # Plotar centróides
    cx = [c[0] for c in centroids]
    cy = [c[1] for c in centroids]
    plt.scatter(cx, cy, marker='X', s=200, label='Centróides')

    plt.title(f"Iteração {iteration}")
    plt.legend()
    plt.pause(1.5)  # pausa para visualizar


def main():
    # Ler arquivo
    try:
        with open("C:\dados\dados.txt", "r") as file:
            n, d = map(int, file.readline().split())

            if d != 2:
                print("Visualização funciona apenas para dados 2D.")
                return

            data = [list(map(float, file.readline().split())) for _ in range(n)]

    except FileNotFoundError:
        print("Erro ao abrir o arquivo!")
        return

    k = int(input("Informe o numero de clusters (k): "))

    # Inicialização
    random.seed(time.time())
    centroids = [data[random.randint(0, n - 1)].copy() for _ in range(k)]
    labels = [0] * n

    plt.ion()  # modo interativo
    start = time.time()

    # K-Means
    for iteration in range(MAX_ITER):

        # Atribuição
        for i in range(n):
            min_dist = float("inf")
            cluster = 0

            for j in range(k):
                dist = distance(data[i], centroids[j])

                if dist < min_dist:
                    min_dist = dist
                    cluster = j

            labels[i] = cluster

        # Plot passo a passo
        plot_clusters(data, labels, centroids, iteration)

        # Reset
        new_centroids = [[0.0] * d for _ in range(k)]
        count = [0] * k

        # Soma
        for i in range(n):
            c = labels[i]
            count[c] += 1

            for j in range(d):
                new_centroids[c][j] += data[i][j]

        # Média
        for j in range(k):
            if count[j] == 0:
                continue
            for l in range(d):
                new_centroids[j][l] /= count[j]

        centroids = new_centroids

    end = time.time()

    plt.ioff()
    plt.show()

    print(f"\nTempo de execução: {end - start:.6f} segundos")


if __name__ == "__main__":
    main()