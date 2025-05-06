import pandas as pd
import matplotlib.pyplot as plt

# Carrega os dados do CSV
df = pd.read_csv('dados.csv')

# Converte a coluna 'timestamp' para datetime
df['timestamp'] = pd.to_datetime(df['timestamp'])

# Cria uma nova coluna para identificar paradas (consumo == 0)
df['parada'] = df['Consumption'] == 0

# Cria uma nova coluna para identificar redundância ativada
df['redundancia'] = df['Redundant'] == True

# Cria o gráfico de linha para o consumo
plt.figure(figsize=(12, 6))
plt.plot(df['timestamp'], df['Consumption'], label='Consumo', color='gray')

# Adiciona pontos vermelhos para paradas
plt.scatter(df.loc[df['parada'], 'timestamp'],
            df.loc[df['parada'], 'Consumption'],
            color='red', label='Parada')

# Adiciona pontos azuis para redundância ativada
plt.scatter(df.loc[df['redundancia'], 'timestamp'],
            df.loc[df['redundancia'], 'Consumption'],
            color='blue', label='Redundância Ativada')

# Configurações do gráfico
plt.xlabel('Tempo')
plt.ylabel('Consumo')
plt.title('Consumo ao Longo do Tempo com Indicação de Paradas e Redundância')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
