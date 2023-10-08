# README

## exCodeSequentielCudaMinMax

### Fichiers
* codeSequentielCudaMinMax.cu
* codeSequentielCudaMinMax
* script.py
* resultats.png
* README.md

### Objectif
Utiliser le fichier script.py pour éxécuter n fois le fichier codeSequentielCudaMinMax.cu. 

### Comment faire ?

* Compiler le fichier cu

``` $ nvcc -o codeSequentielCudaMinMax codeSequentielCudaMinMax.cu ```

* Exécuter le fichier .out

``` $ ./codeSequentielCudaMinMax ../images/image1.pgm```

Vous pouvez remplacer "image1.pgm" par une autre image disponible comme "MontagneFoncee.pgm" ou "stavrovouni.pgm".

* Exécuter le fichier script.py

Pré-requis : Vérifier la présence ou installer les bibliothèques python suivantes : subprocess, re, matplotlib.

``` $ python3 script.py ```

Au début de l'éxécution du script vous serez invité à indiquer le nombre fois que vous souhaitez exécuter le fichier codeSequentielCudaMinMax.cu. L'image resultats.pgm est crée ou mise à jour à la fin de cette étape. 