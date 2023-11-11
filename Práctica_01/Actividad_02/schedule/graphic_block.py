import matplotlib.pyplot as plt
import datetime

# Leer los datos del archivo txt
with open("results_block.txt", "r") as file:
    data = [float(line.strip()) for line in file]

x = list(range(1, 1001, 50))

plt.plot(x, data)



plt.xlabel('Tamaño del bloque')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño del bloque - tiempo de ejecución')

now = datetime.datetime.now()
plt.savefig(f"block_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()
