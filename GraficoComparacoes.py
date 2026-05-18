import matplotlib.pyplot as plt

#Preparação dos dados
x = ['100k', '200k', '300k', '400k', '500k']
euclidiana = [3.0, 18.0, 8.1, 20.4, 27.0] # Valores em milhões
manhattan = [3.6, 4.2, 12.6, 20.4, 18.0]
cosseno = [4.8, 7.8, 12.6, 18.0, 27.0]
minkowski = [3.3, 8.4, 7.2, 14.4, 52.5]
chebyshev = [3.6, 4.8, 16.2, 19.2, 13.5]

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(x, euclidiana, marker='o', label='Distância Euclidiana')
plt.plot(x, manhattan, marker='s', label='Distância de Manhattan')
plt.plot(x, cosseno, marker='^', label='Medida do Cosseno')
plt.plot(x, minkowski, marker='d', label='Distância de Minkowski')
plt.plot(x, chebyshev, marker='x', label='Distância de Chebyshev')

# Customização
plt.title('Comparação do Número de Comparações por Algoritmo', fontsize=14)
plt.xlabel('Volume de Dados', fontsize=12)
plt.ylabel('Número de Comparações (em Milhões)', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

# Exibir
plt.tight_layout()
plt.show()