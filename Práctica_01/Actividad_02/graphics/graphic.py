import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("resultados.txt", "r") as file:
    data = [float(line.strip()) for line in file]

x = list(range(200, 1550, 50))

# Dividir los datos en grupos de 27
datos_threads_mul = [data[i:i+27] for i in range(0, len(data), 27)]
datos_threads_mul_inf = [data[i:i+27] for i in range(27, len(data), 27)]
datos_omp_mul = [data[i:i+27] for i in range(54, len(data), 27)]
datos_omp_mul_inf = [data[i:i+27] for i in range(81, len(data), 27)]

plt.plot(x, datos_threads_mul[0], label="Threads Mul")
plt.plot(x, datos_threads_mul_inf[0], label="Threads Mul_Inf")
plt.plot(x, datos_omp_mul[0], label="OpenMP Mul")
plt.plot(x, datos_omp_mul_inf[0], label="OpenMP Mul_Inf")


plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño de la matriz y tiempo de ejecución con 2 threads')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()
