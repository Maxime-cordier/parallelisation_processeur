import subprocess
import re
import matplotlib.pyplot as plt

nb_iteration = int(input("Nombre d'itérations : "))
executablePath = "./codeSequentielAvxFloat"
image = "../images/image1.pgm"

total_execution_time = 0.0
execution_times = []

for i in range(nb_iteration):
    try:
        result = subprocess.run([executablePath, image], capture_output=True, check=True)


        output_text = result.stdout.decode('utf-8')

        execution_time_str = re.search(r'(\d+\.\d+)', output_text).group(1)
        execution_time = float(execution_time_str)
        
        execution_times.append(execution_time)

        total_execution_time += execution_time

    except subprocess.CalledProcessError as e:
        print(f"Erreur lors de l'exécution de l'exécutable C : {e}")
    except FileNotFoundError:
        print(f"Fichier exécutable C introuvable à l'emplacement : {executablePath}")

average_execution_time = total_execution_time/nb_iteration
print(f"Temps d'execution pour {nb_iteration} iterations: {average_execution_time:.9f} secondes")

plt.plot(execution_times, label="Variation du temps d'execution")
plt.axhline(average_execution_time, color="red", label="Temps moyen d'execution")

plt.title("Temps d'executions de l'algorithme codeSequentielAvxFloat.c")
plt.xlabel("Nombre d'executions du code C")
plt.ylabel("Temps d'executions (s)")
plt.legend()
plt.subplots_adjust(left=0.2, right=0.8, top=0.9, bottom=0.1)
plt.savefig("resultats.png")
plt.show()
