# Statistext - Les mots qui comptent !

## 👨‍💻 À propos

Il s'agit mon tout premier projet personnel en tant qu'étudiant en Informatique à la Haute École Léonard de Vinci, orientation développement d'applications.

Pour débuter, j'ai voulu mettre à l'épreuve les bases acquises en bloc 1 et 2. Et quoi de mieux (ou de pire) que le bon vieux C, le père des langages modernes ? Pour maîtriser les bases, autant retourner aux sources.

Ce projet reste volontairement simple, et c’est justement le but : construire quelque chose de solide et fonctionnel avant de viser plus haut. De plus je ne sais encore définir ce qu'est un "projet pro"... Il faut bien commencer quelque part de tout façon. Un petit pas pour mon github, un grand pas pour ma légende.

## Description

**Statistext** est une application en langage C conçue pour analyser des fichiers texte et extraire des statistiques sur la fréquence d'apparition de chaque mot. Le programme lit un fichier .txt, identifie tous les mots uniques, compte leurs occurrences et affiche les résultats triés par ordre décroissant de fréquence.

## Fonctionnalités

### Fonctionnalités principales
- **Lecture de fichiers texte** : Traitement de fichiers .txt de taille variable
- **Extraction de mots** : Séparation basée sur les espaces, sauts de ligne et ponctuation
- **Normalisation** : Conversion en minuscules pour éviter les doublons (ex. "Mot" et "mot" comptabilisés comme un seul mot)
- **Comptage des occurrences** : Stockage dynamique et efficace des mots uniques avec leurs compteurs
- **Tri intelligent & performant** : Classement par fréquence décroissante, avec tri alphabétique en cas d'égalité
- **Affichage formaté** : Résultats lisibles et bien structurés
- **Gestion d'erreurs** : Traitement des cas d'erreur (fichier introuvable, extension non-conforme, etc.)

### Bonus (scalabilité future)
- Support de plusieurs fichiers avec cumul des occurrences
- Export des résultats dans un fichier texte
- Filtre de stopwords (mots vides à ignorer)

## Installation et Compilation

### Prérequis
- **Compilateur C** : GCC ou équivalent
- **Système d'exploitation** : Linux, macOS ou Windows (avec WSL)

### Compilation

```bash
# Compilation basique
gcc -o statistext main.c

# Compilation avec flags de debug (recommandé pendant le développement)
gcc -std=c17 -pedantic -Wvla -Wno-unused-variable -Wno-unused-but-set-variable -Wall -Werror -o statistext main.c

## Utilisation

### Usage basique

```bash
./statistext <chemin_du_fichier>
```

### Exemple

```bash
./statistext mon_texte.txt
```

**Sortie attendue :**
```
Analyse du fichier : test1.txt
==================================================

|Mot                  |Occurrence
|-------------------- |----------
|bonjour              | 1
|le                   | 1
|monde                | 1

==================================================
Nombre de mots = 3
```

### Gestion des erreurs

Le programme gère les cas suivants :

- **Fichier introuvable** : Message d'erreur explicite
- **Fichier vide** : Notification appropriée
- **Pas de mots trouvés** : Information claire
- **Problèmes de mémoire** : Nettoyage et message d'erreur

```bash
./statistext fichier_inexistant.txt
# Erreur : Impossible d'ouvrir le fichier 'fichier_inexistant.txt'
```

## Architecture et Design

### Structure du programme

```
main()
├── Ouverture et validation du fichier
├── Allocation mémoire
├── Lecture et traitement du texte
│   ├── Extraction des mots
│   ├── Normalisation (minuscules)
│   └── Comptage des occurrences
├── Tri des résultats
├── Affichage des statistiques
└── Libération mémoire
```

### Structures de données principales

- **Dictionnaire**

```c
typedef struct {
    char word[MAX_WORD_LENGTH];
    int occurrence;
} WordOccurrence;
```

### Algorithme de tri

Utilisation d'un algorithme de **tri par insertion** pour classer les mots par fréquence décroissante.

## Structure du projet

```
statistext/
├── main.c                 # Code principal
├── .gitignore             # Fichiers à ignorer par Git
├── test/
│   ├── test0.txt          # Fichier de test erreur fichier vide
│   ├── test0++.txt        # Fichier de test erreur aucun mot détecté
│   ├── test1.txt          # Fichier de test avec ponctuation
│   └── test2.txt          # Fichier de test plus volumineux
├── README.md              # Documentation (ce fichier)
```

## Tests

### Scénarios de test recommandés

1. **Fichier simple** : Quelques mots répétés
2. **Fichier avec ponctuation** : Virgules, points, points-virgules
3. **Fichier vide** : Vérifier la gestion d'erreur
4. **Fichier inexistant** : Vérifier le message d'erreur
5. **Fichier volumineux** : Vérifier la performance et la mémoire

## Performance et Limitations

### Complexité temporelle
- **Lecture du fichier** : O(n) où n = taille du fichier en caractères
- **Ajout des mots** : O(m) en moyenne avec recherche linéaire, où m = nombre de mots uniques
- **Tri** : O(m²) où m = nombre de mots uniques (tri par insertion)
- **Affichage** : O(m)
- **Total** : O(n + m²)

### Complexité spatiale
- O(m × MAX_WORD_LENGTH) où m = nombre de mots uniques
- Plus précisément : O(m × 256) avec redimensionnement dynamique du tableau

### Limitations actuelles
- La taille des mots et le buffer sont limités
- Les fichiers très volumineux peuvent nécessiter plus de RAM
- Les caractères spéciaux/accents sont traités basiquement
- Pas de gestion de l'UTF-8, ASCII simple
- Performance (tri + recheche linéaire)

## Évolutions futures

- Support UTF-8 pour analyser d'autres langues
- Gestion des accents français (é, è, ê, etc.)
- Menu avec fonctionnalités utilisateurs (export, selection via paramètres, etc.)

## Gestion de la Mémoire

Le programme utilise exclusivement **malloc()** et **free()** pour une gestion explicite de la mémoire. Chaque allocation est accompagnée d'une libération correspondante pour éviter les fuites mémoire.

**Vérification avec Valgrind :**
```bash
valgrind --leak-check=full --show-leak-kinds=all ./statistext test.txt
```

## Compétences démontrées

Mémoire dynamique • Manipulation de fichiers • Structures de données • Algorithmes de tri • Gestion d'erreurs • Versionning Git

## Auteur

**Rayan EL-KAROUNI**  
Étudiant en Bloc 2 - Développement d'Applications
Haute École Léonard de Vinci, Bruxelles

## Licence

Ce projet est créé à titre éducatif. Libre d'utilisation et de modification.

## Support et Questions

Pour toute question ou suggestion concernant le projet :
- Ouvrir une issue sur GitHub
- Consulter la documentation en ligne
- Vérifier les exemples dans le dossier `test/`

## Ressources utilisées

- **Compilateur** : [GCC (GNU Compiler Collection)](https://gcc.gnu.org/)
- **Bibliothèque standard C** : [C Standard Library Reference](https://en.cppreference.com/w/c)
- **Gestion de version** : [Git & GitHub](https://github.com/)
- **Syllabus du cours** : [Langage C - Haute École Léonard de Vinci](http://courslinux.vinci.be/~alegrand/Syllabus_C/index.html)
- **Documentation système** : Pages `man` (manuel du terminal Linux)


**Version** : 1.0 (en développement)  
**Dernière mise à jour** : 13 Novembre 2025
