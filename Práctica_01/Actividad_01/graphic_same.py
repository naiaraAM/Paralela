import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("resultados_2.txt", "r") as file:
    data = [float(line.strip()) for line in file]

# Crear ejes X con valores de 1 a 8
x = list(range(1, 9, 1))

# Dividir los datos en grupos de 8
datos_threads = [data[i:i+8] for i in range(0, len(data), 8)]
datos_omp = [data[i:i+8] for i in range(8, len(data), 8)]

plt.plot(x, datos_threads[0], label="Threads")
plt.plot(x, datos_omp[0], label="OpenMP")

plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación número de threads y tiempo de ejecución')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()