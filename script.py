import subprocess
import re
import matplotlib.pyplot as plt
from tqdm import tqdm


dico = {
    
"Normal" :{
    "executablePath": "./exCodeSequentiel/codeSequentiel",
    "total_execution_time" : 0.0,
    "execution_times" : [],
    "color" : "blue"
},
"SSE(Char)" :{
    "executablePath": "./exCodeSequentielSseChar/codeSequentielSseChar",
    "total_execution_time" : 0.0,
    "execution_times" : [],
    "color" : "purple"
},
"AVX(Char)" :{
    "executablePath": "./exCodeSequentielAvxChar/codeSequentielAvxChar",
    "total_execution_time" : 0.0,
    "execution_times" : [],
    "color" : "pink"
},
"CUDA" :{
    "executablePath": "./exCodeSequentielCuda/codeSequentielCuda",
    "total_execution_time" : 0.0,
    "execution_times" : [],
    "color" : "gold"
}

}

nb_iteration = int(input("Nombre d'itérations : "))
image = "./images/MontagneFoncee.pgm"


for i in tqdm(range(nb_iteration), desc="Progress", ncols=100):    
    for key, value in dico.items():
        try:
            result = subprocess.run([value["executablePath"], image], capture_output=True, check=True)
            output_text = result.stdout.decode('utf-8')
            execution_time_str = re.search(r'(\d+\.\d+)', output_text).group(1)
            execution_time = float(execution_time_str)
            value["execution_times"].append(execution_time)
            value["total_execution_time"] += execution_time

        except subprocess.CalledProcessError as e:
            print(f"Erreur lors de l'exécution de l'exécutable C : {e}")
        except FileNotFoundError:
            print("Fichier exécutable C introuvable à l'emplacement : "+value["executablePath"])

for key, value in dico.items():
    average_execution_time = value["total_execution_time"]/nb_iteration
    plt.plot(value["execution_times"], label=key, color=value["color"])
    plt.axhline(y=average_execution_time, color=value["color"], linestyle='--', label=key+" (moyenne)")

plt.xlabel("Iteration")
plt.ylabel("Temps d'execution (s)")
#plt.yscale('log')
plt.title("Temps d'execution des differents parallélismes")
plt.legend()
#save
plt.gcf().set_size_inches(12, 8)
plt.savefig("results_OpenMP_SSE.png")
plt.show()
