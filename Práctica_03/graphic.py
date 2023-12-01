import sys
import matplotlib.pyplot as plt
import datetime

n = sys.argv[1]

if n == "0":
    with open("tiempo_threads.txt", "r") as file:
        data = [float(line.strip()) for line in file]

    x = list(range(1, 17, 1))

    plt.plot(x, data)

    plt.xlabel('Número de threads')
    plt.ylabel('Tiempo de ejecución')
    plt.title('Relación número de threads y tiempo de ejecución')
    plt.axvline(x=8, color='r', linestyle='--')

    now = datetime.datetime.now()
    plt.savefig(f"tiempo_de_ejecución_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")
    plt.show()
elif n == "1":
    with open("escalability_strong.txt", "r") as file:
        data = [float(line.strip()) for line in file]

    x = list(range(1, 9, 1))

    plt.plot(x, data)

    plt.xlabel('Número de threads')
    plt.ylabel('Speed Up')
    plt.title('Escalabilidad fuerte')

    now = datetime.datetime.now()
    plt.savefig(f"escalabilidad_fuerte_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")
    plt.show()
elif n == "2":
    with open("escalability_weak.txt", "r") as file:
        data = [float(line.strip()) for line in file]

    x = list(range(1, 9, 1))

    plt.plot(x, data)

    plt.xlabel('Número de threads')
    plt.ylabel('Speed Up')
    plt.title('Escalabilidad débil')

    now = datetime.datetime.now()
    plt.savefig(f"escalabilidad_debil_{now.strftime('%Y-%m-%d_%H-%M-%S')}.png")
    plt.show()