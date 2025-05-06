import serial
import csv
import time

# Configurações da porta serial
porta = '/dev/ttyACM0'  # Ex: 'COM3' no Windows ou '/dev/ttyUSB0' no Linux
baudrate = 9600
timeout = 1

# Nome do arquivo CSV
arquivo_csv = './data/dados.csv'

# Abre a conexão serial
ser = serial.Serial(porta, baudrate, timeout=timeout)

# Aguarda a estabilização da conexão
time.sleep(2)

print(f"Lendo dados da porta {porta} e salvando em {arquivo_csv}...")

# Abre arquivo CSV para escrita
with open(arquivo_csv, mode='w', newline='') as arquivo:
    escritor_csv = csv.writer(arquivo)
    # Cabeçalho atualizado
    escritor_csv.writerow(['Timestamp', 'State', 'Consumption', 'Redundant', 'Distance', 'IsOn'])

    while True:
            if ser.in_waiting:
                linha = ser.readline().decode('utf-8').strip()
                timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                print(f"[{timestamp}] {linha}")
                dados = linha.split(',')
                escritor_csv.writerow([timestamp] + dados)


