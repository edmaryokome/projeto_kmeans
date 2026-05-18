import matplotlib.pyplot as plt

# Dados
x = [100000, 200000, 300000, 400000, 500000]
dados = {
    "Euclidiana": [129606, 248718, 324802, 422861, 622146],
    "Manhattan": [148033, 253224, 420444, 546363, 736598],
    "Cosseno": [132791, 278611, 325896, 556506, 698874],
    "Minkowski": [128325, 213503, 374523, 418191, 847726],
    "Chebyshev": [151990, 202186, 446280, 565517, 587053]
}

# Criar o gráfico
plt.figure(figsize=(10, 6))

for rotulo, valores in dados.items():
    plt.plot(x, valores, marker='o', label=rotulo)

plt.title('Mudanças de Grupo por Algoritmo')
plt.xlabel('Quantidade de Dados')
plt.ylabel('Número de Mudanças')
plt.legend()
plt.grid(True)
plt.show()