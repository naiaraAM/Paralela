import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("results_dim.txt", "r") as file:
    data = [float(line.strip()) for line in file]

x = list(range(200, 1550, 50))

# Dividir los datos en grupos de 27
datos_omp_mul_inf_static = [data[i:i+27] for i in range(0, len(data), 27)]
datos_omp_mul_inf_dynamic = [data[i:i+27] for i in range(27, len(data), 27)]
datos_omp_mul_inf_guided = [data[i:i+27] for i in range(54, len(data), 27)]

plt.plot(x, datos_omp_mul_inf_static[0], label="static")
plt.plot(x, datos_omp_mul_inf_dynamic[0], label="dynamic")
plt.plot(x, datos_omp_mul_inf_guided[0], label="guided")



plt.xlabel('Número de threads')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño de la matriz y schedule implementado')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"implementations_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()
