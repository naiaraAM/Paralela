import matplotlib.pyplot as plt
import datetime
import sys

# Leer los datos del archivo txt
with open("resultados_max_" + sys.argv[1] + "_omp.txt", "r") as file:
    data = [float(line.strip()) for line in file]

# Crear ejes X con valores de 200 a 1500 con saltos de 50
x = list(range(200, 1550, 50))

# Dividir los datos en grupos de 27
datos_sec = [data[i:i+27] for i in range(0, len(data), 27)]
datos_omp_directives = [data[i:i+27] for i in range(27, len(data), 27)]
datos_omp_runtime = [data[i:i+27] for i in range(54, len(data), 27)]
datos_omp_reduction = [data[i:i+27] for i in range(81, len(data), 27)]

# Crear un gráfico para cada conjunto de datos
plt.plot(x, datos_sec[0], label="Single")
plt.plot(x, datos_omp_directives[0], label="Directivas")
plt.plot(x, datos_omp_runtime[0], label="Runtime")
plt.plot(x, datos_omp_reduction[0], label="Reduction")

# Para los demás conjuntos, usar plt.plot nuevamente

plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño de la matriz y tiempo de ejecución con ' + sys.argv[1] + ' procesos')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"max_omp_" + sys.argv[1] + "_" + now.strftime("%Y-%m-%d_%H-%M-%S") + ".png")

plt.show()

# guarda la grafica en un archivo png con la fecha y hora actual
