import matplotlib.pyplot as plt
import pandas as pd

#Preparação dos dados
data = {
'Registros': ['100k', '200k', '300k', '400k', '500k'],
'Euclidiana': [0.474, 2.657, 2.762, 4.195, 4.575],
'Manhattan': [0.188, 0.315, 0.436, 0.651, 0.762],
'Cosseno': [0.521, 0.674, 1.175, 1.417, 3.084],
'Minkowski': [1.577, 4.776, 3.588, 7.506, 22.687],
'Chebyshev': [0.148, 0.263, 0.738, 0.911, 0.515]
}
df = pd.DataFrame(data)

#Configuração do Gráfico
plt.plot(df['Registros'], df['Euclidiana'], marker='o', linestyle='-', linewidth=2, label='Euclidiana')
plt.plot(df['Registros'], df['Manhattan'], marker='s', linestyle='--', linewidth=2, label='Manhattan')
plt.plot(df['Registros'], df['Cosseno'], marker='^', linestyle='-.', linewidth=2, label='Cosseno')
plt.plot(df['Registros'], df['Minkowski'], marker='x', linestyle='-', linewidth=2, label='Minkowski')
plt.plot(df['Registros'], df['Chebyshev'], marker='d', linestyle=':', linewidth=2, label='Chebyshev')

#Formatação
plt.title('Comparação de Tempo de Execução por Algoritmo', fontsize=14)
#plt.xlabel('Volume de Dados (Número de Registros)', fontsize=12)
plt.ylabel('Tempo de Execução (segundos)', fontsize=12)
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.tight_layout()

#Mostrar o gráfico
plt.show()