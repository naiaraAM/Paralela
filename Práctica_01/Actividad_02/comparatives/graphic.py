import matplotlib.pyplot as plt
import datetime

with open("resultados.txt", "r") as file:
    data = [float(line.strip()) for line in file]

x = list(range(200, 1550, 50))

datos_threads = [data[i:i+27] for i in range(0, len(data), 27)]
datos_omp = [data[i:i+27] for i in range(27, len(data), 27)]

plt.plot(x, datos_threads[0], label="Threads")
plt.plot(x, datos_omp[0], label="OpenMP")

plt.xlabel('Tamaño de la matriz')
plt.ylabel('Speedup obtenido')
plt.title('Relación tamaño de la matriz y tiempo de ejecución con 8 threads')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"resultados_comparativa_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()