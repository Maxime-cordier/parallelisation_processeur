# Processeurs pour le multi-média

# Auteurs
- Romain Heriteau
- Maxime Cordier

# Introduction
blablabla

# Achitecture et organisation des travaux pratiques
Les travaux pratiques sont organisés dans des dossiers "exercice" commencant par le préfixé "Ex". Nous pouvons ainsi retrouver les travaux pratiques suivants : 
- exCodeSequentiel : Code séquentiel de base de réhaussement de contraste d'image.
- exCodeSequentielSSE_float : Code adapté avec des instructions SSE. Les données stockés dans les registres sont de type float.
- exCodeSequentielSSE_short : Code adapté avec des instructions SSE. Les données stockés dans les registres sont de type short.
- exCodeSequentielSSE_char : Code adapté avec des instructions SSE. Les données stockés dans les registres sont de type char.
- exCodeSequentielAVX_float : Code adapté avec des instructions AVX. Les données stockés dans les registres sont de type float.
- exCodeSequentielAVX_short : Code adapté avec des instructions AVX. Les données stockés dans les registres sont de type short.
- exCodeSequentielAVX_char : Code adapté avec des instructions AVX. Les données stockés dans les registres sont de type char.

Les dossiers suivant sont également présents : 
- Exemples : Dossiers contenant des exemples d'utilisations de plusieurs type d'instructions.
- Images : Dossier contenant les images ciblés lors des réhaussements de contraste déclanché par l'éxécution des fichiers c. Les images a réhaussé ont une extension .pgm et les images obtenues suite au réhaussement ont une extension .new.

Liste des fichiers disponible à la racine du projet :
- Readme.md
- script.py : Script python déclanchant l'éxécution de un ou plusieurs exercice(s) de réhaussement de contraste.
- methodes.json : Fichier json permettant de modifier le contenue de la variable "dico" du fichier script.py. Cette variable est un dictionnaire regroupant les exercices de réhaussement de contraste que nous voulont tester lors d'une même exécution.
- results_XXX.png : Images des résulats obtenus suite à l'exécution du fichier script.py.

# How to run the script.py file ? 

Pré-requis : Vérifier la présence ou installer les bibliothèques python suivantes : subprocess, re, matplotlib et tqdm.

``` $ python3 script.py ```

Then, give the number of times you want to run the chaque exercice de réhaussement de contraste. The results_XXX.png image is created or update at the end of this step. 