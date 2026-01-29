
# Push_swap

*This project has been created as part of the 42 curriculum by blamotte.*

## Description

**Push_swap** est un projet d'algorithmique dont l'objectif est de trier une pile de nombres entiers en utilisant un ensemble d'instructions limité, tout en visant le plus petit nombre d'opérations possible.

Le projet repose sur deux piles, **a** et **b**, et une série de mouvements (swaps, pushes, rotations). La complexité réside dans la recherche d'un algorithme capable de trier des volumes importants (100 et 500 nombres) de manière extrêmement optimisée pour atteindre les barèmes de performance les plus stricts de l'école.

## Instructions

### Compilation

Le projet utilise un `Makefile` standard pour la compilation.

```bash
make          # Compile l'exécutable principal push_swap et le checker pour vérifier le tri
make clean    # Supprime les fichiers objets
make fclean   # Supprime les objets et les exécutables
make re		  # fclean puis make

```

### Exécution

Pour générer la suite d'instructions permettant de trier une liste de nombres :

```bash
./push_swap 3 2 1 5 4

```

Pour vérifier que le tri est correct à l'aide du checker (bonus) :

```bash
ARG="3 2 1 5 4"; ./push_swap $ARG | ./checker $ARG

```

## Performances

L'algorithme a été optimisé pour dépasser les attentes du sujet. Voici les résultats moyens obtenus :

| Taille de la pile | Moyenne d'opérations | Barème 42 (Note Max) |
| --- | --- | --- |
| **3 nombres** | 1 - 2 | < 3 |
| **5 nombres** | ~6 - 8 | < 12 |
| **100 nombres** | ~450 | < 700 |
| **500 nombres** | ~3600 | < 5500 |

## Choix Techniques & Améliorations

### Algorithme

Le projet utilise une logique de **K-Sort** (ou tri par "chunks") pour la phase de pré-tri de la pile A vers la pile B. Cette méthode permet de placer les éléments par plages de valeurs, facilitant ensuite leur repositionnement dans A avec un coût minimal.

### Pourquoi ne pas avoir utilisé le Backtracking ?

Lors du développement, l'option du *Backtracking* (explorer toutes les combinaisons possibles sur une certaine profondeur) a été écartée pour les grandes piles. Bien que précis, il souffre de l'**effet tunnel** : l'algorithme peut s'engager dans une branche qui semble optimale localement mais qui mène à une impasse ou à un surcoût massif quelques coups plus tard. Augmenter la profondeur ou le nombre de candidats entraîne une explosion combinatoire ingérable en C pour ce projet.

### Améliorations possibles (Heuristiques)

Pour aller encore plus loin, l'implémentation d'un **bonus heuristique** sur le calcul des coûts permettrait d'éviter les **minimas locaux**. Au lieu de choisir l'élément le plus proche mathématiquement, une fonction de coût plus complexe pourrait évaluer l'impact d'un mouvement sur les éléments suivants, garantissant ainsi une fluidité constante tout au long du tri.

## Resources

* **Algorithmique** : Logique du K-sorting (documentation via [Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)).
* **Intelligence Artificielle** : L'IA a été utilisée exclusivement pour l'aide à la rédaction et à la mise en page de ce fichier `README.md`. Aucun code de l'algorithme de tri n'a été généré par IA.

---

*Projet réalisé avec rigueur pour valider le cercle 2 du cursus 42.*
