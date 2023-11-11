import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("resultados.txt", "r") as file:
    data = [float(line.strip()) for line in file]

# Crear ejes X con valores de 200 a 1500 con saltos de 50
x = list(range(200, 1550, 50))

# Dividir los datos en grupos de 27
datos_threads = [data[i:i+27] for i in range(0, len(data), 27)]
datos_omp = [data[i:i+27] for i in range(27, len(data), 27)]

# Crear un gráfico para cada conjunto de datos
plt.plot(x, datos_threads[0], label="Threads")
plt.plot(x, datos_omp[0], label="OpenMP")

# Para los demás conjuntos, usar plt.plot nuevamente

plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño de la matriz y tiempo de ejecución con 2 threads')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")