import matplotlib.pyplot as plt

def main():
    try:
        caminho = r"C:\dados\dados.txt"

        with open(caminho, "r") as file:
            n, d = map(int, file.readline().split())

            if d != 2:
                print("Este gráfico funciona apenas para dados 2D.")
                return

            data = [list(map(float, file.readline().split())) for _ in range(n)]

    except FileNotFoundError:
        print("Erro ao abrir o arquivo! Verifique o caminho.")
        return

    # Separar coordenadas
    x = [p[0] for p in data]
    y = [p[1] for p in data]

    fig, ax = plt.subplots()

    # Plot dos pontos
    ax.scatter(x, y)

    # Linhas dos eixos (plano cartesiano)
    ax.axhline(0)  # eixo X
    ax.axvline(0)  # eixo Y

    # Grade
    ax.grid(True)

    # Escala igual (importante!)
    ax.set_aspect('equal', adjustable='box')

    # Títulos
    ax.set_title("Plano Cartesiano - Dados")
    ax.set_xlabel("Eixo X")
    ax.set_ylabel("Eixo Y")

    plt.show()


if __name__ == "__main__":
    main()