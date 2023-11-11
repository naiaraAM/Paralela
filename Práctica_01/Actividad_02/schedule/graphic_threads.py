import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("results_threads.txt", "r") as file:
    data = [float(line.strip()) for line in file]

x = list(range(1, 9, 1))

# Dividir los datos en grupos de 27
datos_omp_mul_inf_static = [data[i:i+8] for i in range(0, len(data), 8)]
datos_omp_mul_inf_dynamic = [data[i:i+8] for i in range(8, len(data), 8)]
datos_omp_mul_inf_guided = [data[i:i+8] for i in range(16, len(data), 8)]

plt.plot(x, datos_omp_mul_inf_static[0], label="static(default)")
plt.plot(x, datos_omp_mul_inf_dynamic[0], label="dynamic")
plt.plot(x, datos_omp_mul_inf_guided[0], label="guided")



plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación número threads - schedule implementado')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"threads_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()
