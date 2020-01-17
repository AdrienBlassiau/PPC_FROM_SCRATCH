# PROJET PPC FROM SCRATCH

IMPORTANT: LIRE CE FICHIER AVANT DE LANCER LE PROGRAMME

Sommaire
===============================================================================

1. Introduction
2. Arborescence des fichiers
3. Instructions d'installation des différents outils
4. Conseils d'utilisation



# 1. Introduction                 

Ceci est le README du projet **PPC FROM SCRATCH** réalisé dans le cadre du
cours de Programmation Par Contraintes (PPC) du MPRO. Ce projet consiste en
la réalisation d'un **solveur générique de CSP** où les contraintes sont
binaires et les variables entières. **Plusieurs algorithmes** ont été
implémentés (backtrack, forward-checking, AC4, ...), des 
**heuristiques de branchement** ont été mises en place et un 
**format de fichier** (.cspi) lisible par le solveur a été créé, pour que 
l'utilisateur puisse créer ses propres CSP et les résoudre avec le solveur.

Nous vous proposons trois types d'instances à résoudre avec notre solveur :

* le problème des n-reines, de taille souhaitée, qui peut être généré 
  directement par le solveur. 
* des graphes à colorer, disponibles dans le dossier *inst/test*
* ... ou n'importe qu'elle instance que vous pouvez vous même créer en
  utilisant le format .cspi.

NOTE: Nous vous invitons à lire notre rapport qui vous renseignera sur la
démarche et les choix engagés dans ce projet.


# 2. Arborescence des fichiers

Nous avons l’arborescence suivante :

    /bin
    /doc
    /inst
    /obj
    /src
    /test

* Dans */bin* se trouvent les exécutables.
* Dans */doc* se trouvent la documentation du code générée avec Doxygen.
* Dans */inst* se trouvent les instances de test.
* Dans */obj* les fichiers objets .o.
* Dans */src* le code source du projet.
* Dans */test* les tests unitaires du code source.

# 3. Instructions d'installation des différents outils


**Utilisateur Linux**

*******************************************************************************

Doxygen (NON OBLIGATOIRE)
--------

Doxygen est un outil qui génère la documentation de son code. Il
permet à terme de fournir une page web ou un pdf contenant la documentation du
code que le développeur souhaite publier. Vous pouvez l'installer si vous
souhaitez régénérer la documentation.

**Entrez dans votre console** : 
> sudo apt-get install doxygen

*******************************************************************************

CUnit (NON OBLIGATOIRE)
--------

CUnit est une bibliothèque de tests unitaires pour C. Elle permet de
programmer des tests, de les exécuter, et d’afficher un résumé des tests
réussis ou échoués. Un test unitaire ne teste qu’une partie atomique des
spécifications sous des conditions précises qui, bien généralement, ne
couvrent pas tous les cas. Vous pouvez l'installer si vous souhaitez lancer
les tests unitaires.

**Entrez dans votre console** : 
> sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev

*******************************************************************************

Valgrind (NON OBLIGATOIRE)
--------

Valgrind est un outil qui permet de repérer les fuites mémoires (et autres
erreurs). Vous pouvez l'installer si vous souhaitez contrôler que le programme
n'a pas de fuites mémoires.

**Entrez dans votre console** : 
> sudo apt-get install valgrind

*******************************************************************************

Python (NON OBLIGATOIRE)
--------

Python est utilisé pour l'affichage graphique à l'intérieur même du code C.
Vous pouvez l'installer si vous souhaitez être en mesure de faire marcher
l'affichage graphique du graphe des contraintes. Pour cela, il vous faut tout
d'abord installer python sur votre machine, si ça n'est pas déjà fait, ici python 3 par exemple :

**Entrez dans votre console** : 
> sudo apt-get install python3-dev

**Attention** : dans le fichier Makefile, à la racine du projet, pensez à
spécifier la version de python que vous possédez sur votre machine avec la
variable PYTHON_VERSION (trouvable au niveau de /usr/include/).

*******************************************************************************


# 4. Conseils d'utilisation

Le projet est constitué de 4 exécutables différents :

 * **./bin/main** [PARAMÈTRES] qui lance le solveur sur une instance, les
  paramètres de résolution et l'instance à tester sont à préciser en
  entrées de l’exécutable.
 * **./bin/main-g** [PARAMÈTRES] même chose que ./bin/main mais avec un
   affichage graphique du graphe des contraintes en plus.
 * **./bin/test** qui lance les tests unitaire du projet.
 * **./bin/convert** [NOM DU FICHIER SOUS FORMAT DIMACS À CONVERTIR] [NOM DU
  FICHIER DE SORTIE] [NOMBRE DE COULEURS MAXIMALE] qui permet de convertir un
  fichier sous format DIMACS (.col) en un fichier lisible par le solveur de
  PPC (.cspi).
 
Ces exécutables sont déjà présents dans le rendu du projet mais vous pouvez
les régénérer si vous le souhaitez. Pour plus d'informations sur ces
exécutables, nous vous invitons à prendre connaissance des informations qui
suivent.


Lancer le programme via une console
------------------------

Pour lancer le solveur, il faut utiliser l’exécutable ./bin/main. Un exécutable est déjà présent dans le rendu. Les commandes importantes sont les suivantes :

**1. Entrez dans votre console (compiler)** : 
> make main

**2. Entrez dans votre console (lancer)** : 
> ./bin/main

**2. Entrez dans votre console (compiler et lancer)** : 
> make main && ./bin/main

**Important** : L'exécutable ./bin/main est entièrement paramétrable. Vous
pouvez tout préciser via des paramètres, que ce soit l'instance d'entrée, les
heuristiques de branchement, etc.
De bases, l’exécutable ./bin/main sans paramètre lance le solveur sur un 
problème de n-reines de taille 5, qui utilise le backtrack, en choisissant
les variables (resp. les valeurs) dans l'ordre lexicographique (resp.
croissant). 

Un petit exemple, si vous souhaitez lancer le solveur sur le graphe *myciel5*
, en utilisant le forward checking, avec pour heuristique de choix des
variables l'ordre lexicographique inversé , il faudra entrer :

> ./bin/main -f inst/test/myciel5.cspi -fc 1 -hvar 2 

**Très Important** : Pour plus d'information sur les différents paramètres, 
nous mettons à votre disposition un petit manuel de secours avec la commande
suivante :

**Entrez dans votre console** : 
> ./bin/main --help

**Très Important** : Un grand nombre d'instance sont déjà présentes dans
le dossier *inst/test*. Si vous souhaitez écrire vous même une instance d'un
problème à résoudre avec le solveur, nous mettons à votre disposition un
petit manuel de secours sur le format .cspi, avec la commande suivante :

**Entrez dans votre console** : 
> ./bin/main --format

Lancer le programme via une console avec le mode graphique activé
------------------------

**Pré-requis** : Avant de lancer le mode graphique, il vous faut python 
d'installé sur votre machine (voir la section dédiée plus haut).

Pour lancer le solveur en mode graphique, il faut utiliser l’exécutable 
./bin/g-main. Un exécutable est déjà présent dans le rendu. Les commandes importantes sont les suivantes :

**1. Entrez dans votre console (compiler)** : 
> make g-main

**2. Entrez dans votre console (lancer)** : 
> ./bin/g-main

**2. Entrez dans votre console (compiler et lancer)** : 
> make g-main && ./bin/g-main

Les autres instructions sont les mêmes que pour exécutables ./bin/main

Lancer les tests unitaires 
------------------------

**Pré-requis** : Avant de lancer les tests unitaires, il vous faut CUnit
d'installé sur votre machine (voir la section dédiée plus haut).

Pour lancer les tests unitaires, il faut utiliser l’exécutable 
./bin/test. Un exécutable est déjà présent dans le rendu. Les commandes
importantes sont les suivantes :

**1. Entrez dans votre console (compiler)** : 
> make test

**2. Entrez dans votre console (lancer)** : 
> ./bin/test

**2. Entrez dans votre console (compiler et lancer)** : 
> make test && ./bin/test

*Comment lire le résultat d'un test CUnit ?*

      CUnit - A unit testing framework for C - Version 2.1-3
      http://cunit.sourceforge.net/

    Run Summary:     Type  total    Ran Passed Failed  Inactive
                   suites      1      1    n/a      0         0
                    tests      5      5      5      0         0
                  asserts    118    118    118      0       n/a

    Elapsed time =    0.001 seconds


La ligne tests correspond au nombre de tests unitaires effectués, la ligne
asserts correspond au nombres d'assertions vérifiées. Pour chaque tests, il
peux y avoir plusieurs assertions. 


Convertir un fichier sous format DIMACS (.col) en un fichier lisible par le solveur de PPC (.cspi)
------------------------

Les fichiers de graphes à convertir sont sous format (.col). Ils se trouvent
dans le dossier *inst/source*. Un certain nombre de graphes ont déjà été
convertis et se trouvent dans le dossier *inst/test*. Lors d'une conversion, il
faut précise le fichier d'entrée, le fichier de sortie et la taille du domaine,
c'est-a-dire le nombre de couleurs avec lesquelles on va essayer de colorier le
graphe (c'est un problème de décision !). Un exécutable est déjà présent dans le rendu. Les commandes importantes sont les suivantes :

**1. Entrez dans votre console (compiler)** : 
> make convert 

**2. Entrez dans votre console (lancer)** : 
> ./bin/convert [ENTRÉE] [SORTIE] [NB COULEURS]

**2. Entrez dans votre console (compiler et lancer)** : 
> make convert && ./bin/convert [ENTRÉE] [SORTIE] [NB COULEURS]

Un exemple : 

> ./bin/convert inst/source/myciel5.col inst/test/myciel5.cspi 8

Cette commande convertit myciel5.col en myciel5.cspi avec des domaines de 
taille 8 pour les variables. Le problème de décision associé à ce graphe est 
donc : *"Peut-on colorier myciel5 avec avec 8 couleurs ?"*.

**Important** : Un petit script permet de résoudre automatiquement le problème
d'optimisation de recherche du nombre chromatique d'un graphe. Cet algorithme
effectue une dichotomie sur le nombre de couleurs testées. Ce script se nomme
*run_test_graph.sh*. Son utilisation est simple :  

> bash run_test_graph.sh [NOM DU GRAPHE] [BORNE MAX]

Par exemple :

> bash run_test_graph.sh myciel5 10

... lance une dichotomie sur le graphe myciel5 en fixant la borne supérieurs à
10 (Cette borne pourrait être le degré maximum + 1 ...).


*******************************************************************************

Doxygen
-------

Pour obtenir la documentation générée par Doxygen, un document sous format web
est déjà présent dans le dossier fournit, pour l'ouvrir :

*Via navigateur fichier*

Il est présent dans *doc/html/index.html* Ouvrez le sur votre navigateur web
favori.

*Via console*

**Entrez dans votre console** : 
> firefox doc/html/index.html &

NOTE: Remplacez firefox par votre navigateur web favori.

*Informations*

Vous pouvez aussi régénérer la documentation puis l' ouvrir : 

**Entrez dans votre console** :
> make doxygen && firefox doc/html/index.html &



*******************************************************************************

Valgrind
--------

Pour contrôler la présence de fuites mémoires (attention, cela ralenti 
considérablement l’exécution du programme) : 

> valgrind [NOM DE L'EXECUTBALE QUE VOUS VOULEZ]

**Attention** : ne SURTOUT pas tester cette commande avec le mode graphique
activé (exécutable ./bin/g-main). L'exécution de python créée
énormément de fuites mémoires ...

*Comment lire les résultats de valgrind ?*

Une fois lancé, rendez vous à la section HEAP SUMMARY : 
    
      ==22390== 
      ==22390== HEAP SUMMARY:
      ==22390==     in use at exit: 0 bytes in 0 blocks
      ==22390==   total heap usage: 6,189,434 allocs, 6,189,434 frees, 269,465,331 bytes allocated
      ==22390== 
      ==22390== All heap blocks were freed -- no leaks are possible
      ==22390== 
      ==22390== For counts of detected and suppressed errors, rerun with: -v
      ==22390== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


Vous obtenez la mémoire allouée (allocs) et la mémoire libérée (frees) ainsi
que certaines autres erreurs liées à une mauvaise gestion de la mémoire (ERROR
SUMMARY).
 
*******************************************************************************

Auteurs
---------------------

* **Adrien BLASSIAU** _alias_ [@AdrienBlassiau](https://github.com/AdrienBlassiau)
* **Corentin JUVOGNY** _alias_ [@corentinjuvigny](https://github.com/corentinjuvigny)


*Merci pour votre lecture !*
