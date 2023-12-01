import matplotlib.pyplot as plt
import datetime

with open("results_block_dynamic.txt", "r") as file:
    lines = file.readlines()
    data_set1 = [line.strip().split() for line in lines[:50]]
    data_set2 = [line.strip().split() for line in lines[50:]]

x_set1 = [int(entry[0]) for entry in data_set1]
y_set1 = [float(entry[1]) for entry in data_set1]

x_set2 = [int(entry[0]) for entry in data_set2]
y_set2 = [float(entry[1]) for entry in data_set2]

plt.plot(x_set1, y_set1, label='8 threads')
plt.plot(x_set2, y_set2, label='16 threads')

plt.xlabel('Tamaño del bloque')
plt.ylabel('Tiempo de ejecución')
plt.title('Relación tamaño del bloque - tiempo de ejecución')
plt.legend()

now = datetime.datetime.now()
plt.savefig(f"block_dynamic_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")

plt.show()