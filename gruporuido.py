import math
import random
import time
import matplotlib.pyplot as plt

MAX_ITER = 10
THRESHOLD = 5.0  # limite para considerar outlier (ajuste conforme seus dados)

# Distância Euclidiana
def distance(a, b):
    return math.sqrt(sum((a[i] - b[i]) ** 2 for i in range(len(a))))


def plot_clusters(data, labels, centroids, iteration):
    plt.clf()

    k = len(centroids)

    # Plot clusters normais
    for i in range(k):
        x = [data[j][0] for j in range(len(data)) if labels[j] == i]
        y = [data[j][1] for j in range(len(data)) if labels[j] == i]
        plt.scatter(x, y, label=f"Cluster {i}")

    # Plot outliers
    x_out = [data[j][0] for j in range(len(data)) if labels[j] == -1]
    y_out = [data[j][1] for j in range(len(data)) if labels[j] == -1]
    if x_out:
        plt.scatter(x_out, y_out, c='black', marker='x', label='Outliers')

    # Plot centróides
    cx = [c[0] for c in centroids]
    cy = [c[1] for c in centroids]
    plt.scatter(cx, cy, marker='X', s=200, c='red', label='Centróides')

    plt.title(f"Iteração {iteration}")
    plt.legend()
    plt.pause(1.5)


def main():
    try:
        with open(r"C:\dados\dados.txt", "r") as file:  # corrigido com raw string
            n, d = map(int, file.readline().split())

            if d != 2:
                print("Visualização funciona apenas para dados 2D.")
                return

            data = [list(map(float, file.readline().split())) for _ in range(n)]

    except FileNotFoundError:
        print("Erro ao abrir o arquivo!")
        return

    k = int(input("Informe o numero de clusters (k): "))

    random.seed(time.time())
    centroids = [data[random.randint(0, n - 1)].copy() for _ in range(k)]
    labels = [0] * n

    plt.ion()
    start = time.time()

    for iteration in range(MAX_ITER):

        # Atribuição com detecção de outliers
        for i in range(n):
            min_dist = float("inf")
            cluster = -1

            for j in range(k):
                dist = distance(data[i], centroids[j])

                if dist < min_dist:
                    min_dist = dist
                    cluster = j

            # Verifica se é outlier
            if min_dist > THRESHOLD:
                labels[i] = -1
            else:
                labels[i] = cluster

        plot_clusters(data, labels, centroids, iteration)

        # Reset
        new_centroids = [[0.0] * d for _ in range(k)]
        count = [0] * k

        # Soma (ignora outliers)
        for i in range(n):
            if labels[i] == -1:
                continue

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