Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

# Sommaire

- [Sommaire](#sommaire)
- [Lancement](#lancement)
    - [Avec les extensions :](#avec-les-extensions-)
    - [Avec la ligne de commande :](#avec-la-ligne-de-commande-)
- [Structure](#structure)
- [Guide des touches](#guide-des-touches)
- [Listes des tâches](#listes-des-tâches)
- [Informations supplémentaires](#informations-supplémentaires)
    - [Informations utiles](#informations-utiles)
    - [Explication de la refactorisation des coordonnées](#explication-de-la-refactorisation-des-coordonnées)
    - [Identification des bugs](#identification-des-bugs)
    - [Temps passé Nils](#temps-passé-nils)

# Lancement

## Avec les extensions :

Avec [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) et [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) il suffit d'exécuter la cible `[main]`

## Avec la ligne de commande :

Depuis la racine faire :

```sh
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles"
cd .. && cmake --build ./build --target all --config Debug -j 16
cd bin && ./main.exe fichier/a/lire.json
```

Exemple : `./main.exe ../data/path_1.json`

> Les commandes précédent l'exécution peuvent ne pas marcher ou être différentes selon l'ordinateur

# Structure

```
├───📁 assets : shaders & textures
├───📁 data : les dossiers avec les json de rails
│   └─── DATADESC.md : décrit les fichiers de données
├───📁 docs : des documents
├───📁 lib : les librairies externes
├───📁 src : les fichiers sources
│   ├───📁 draw : les fichiers individuels des rendus 3D
│   │   ├───📄 base.cpp : contient le dessin du sol, de la grille et du repère
│   │   ├───📄 rail.cpp : contient le dessin des morceaux de rails
│   │   ├───📄 shared.cpp : contient les valeurs globales utilisées par les autres (dont les unités sr, sx, rr et myEngine)
│   │   ├───📄 train_station.cpp : contient le dessin de la gare
│   │   └───📄 train.cpp : contient le dessin du train
│   ├───📄 camera.cpp : variables et fonctions pour la camera
│   ├───📄 draw_scene.cpp : les rendus 3D
│   ├───📄 main.cpp : moteur de rendus
│   └───📄 railways.cpp : structure de sérialisation du JSON
└───📄 README.md : ce fichier
```

# Guide des touches

| Touche                                              | Action                                            | Note                |
| --------------------------------------------------- | ------------------------------------------------- | ------------------- |
| <kbd>Esc</kbd>                                      | Quitter l'application                             |                     |
| <kbd>Z</kbd> <kbd>Q</kbd> <kbd>S</kbd> <kbd>D</kbd> | Déplacer/Bouger la caméra                         |                     |
| <kbd>Molette souris</kbd>                           | Avancer/Reculer la caméra                         | Hors mode FPS       |
| <kbd>Déplacement souris</kbd>                       | Tourner la caméra                                 | Uniquement mode FPS |
| <kbd>R</kbd>                                        | Changer le mode de rendu (fil de fer ou plein)    |                     |
| <kbd>F</kbd>                                        | Changer le mode d'éclairage (flat ou phong)       |                     |
| <kbd>C</kbd>                                        | Changer le mode de la camera (orbitale, top, fps) |                     |
| <kbd>G</kbd>                                        | Afficher/Masquer la grille                        |                     |

# Listes des tâches

> ☑️ = Bonus énuméré dans l'énoncé ♒ = Bonus supplémentaire

| Status | Catégorie      | En + | Description                           | Commentaire                              | Qui    |
| ------ | -------------- | ---- | ------------------------------------- | ---------------------------------------- | ------ |
| ✅     | 📁Structure    |      | Créer la structure du projet          | Reprendre la base du TD04                | Nils   |
| ✅     | 📁Structure    |      | Fragmentation du draw_scene           |                                          | Nils   |
| ❌     | ⚒️Modélisation |      | Faire les Rails                       | Faire Courbé et Droit                    | Yanis  |
| ✅     | ⚒️Modélisation |      | Faire le Train                        | + Faire triangle et cylindre fermé       | Nils   |
| ❌     | ⚒️Modélisation |      | Faire la Gare                         |                                          | -      |
| ✅     | 📝JSON         |      | Lire le JSON (Railways)               | Serialisé en `Railways`                  | Nils   |
| ❌     | 📝JSON         |      | Créer le parcours                     | Depuis `Railways`                        | Yanis  |
| ❌     | 📝JSON         |      | Placer la gare et le train            |                                          | -      |
| ✅     | 📝JSON         |      | Lancement avec JSON en argument       |                                          | Nils   |
| ✅     | 🖥️IHM          |      | Touche pour quitter                   | Touche Échap                             | Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes d'éclairages | Touche F                                 | Nils   |
| ❌     | 🖥️IHM          |      | Caméra FPS                            | ZQSD to move (X,Y), Scroll to move (Z)   | -      |
| ✅     | 🖥️IHM          |      | Caméra ORBITAL                        | ZQSD to rotate (X,Y), Scroll to zoom (Z) | Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes camera       | Touche C                                 | -      |
| ✅     | 👁️Rendu        |      | Éclairage "flat"                      | Par défaut sur OpenGL                    | OpenGL |
| ❌     | 👁️Rendu        |      | Éclairage "réaliste" `*`              | Un soleil et phares du train             | -      |
| ❌     | 👁️Rendu        |      | Texturé un truc                       | Avant du train                           | -      |
| ✅     | 📁Structure    | ♒   | Refactorisation des coordonnées       | Voir informations supplémentaires        | Nils   |
| ✅     | 🖥️IHM          | ♒   | Touche pour toggle modes de rendu     | Touche R                                 | Nils   |
| ✅     | 🖥️IHM          | ♒   | Caméra TOP                            | ZQSD to move (X,Z), Scroll to zoom (Y)   | Nils   |
| ✅     | 🖥️IHM          | ♒   | Touche pour toggle grille             | Touche G                                 | Nils   |
| ✅     | ⚒️Modélisation | ♒   | Grille des cellules de rails          | Pour visualiser le placement             | Nils   |
| ✅     | ⚒️Modélisation | ☑️   | Modéliser (+ placer) du décors        | Genre un arbre                           | -      |
| ❌     | ⚒️Modélisation | ☑️   | Primitives supplémentaires            | Triangle reactangle et cylindre fermé    | Nils   |
| ❌     | 📝JSON         | ☑️   | Ajouter des trucs dans le JSON        |                                          | Nils   |
| ❌     | 👁️Rendu        | ☑️   | Animer le train                       |                                          | -      |
| ❌     | 👁️Rendu        | ☑️   | Ajouter des lumières                  | Genre à la gare                          | -      |

> `*` = D'après le PDF : _"vous devrez positionner une lumière directionnelle (orientée selon votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être texturé !"_

# Informations supplémentaires

## Informations utiles

> Extension pratique pour naviguer dans des endroits du code sur `VS Code` :<br>
> [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)<br>
> Avec `NOTE:` et `SOURCE:` d'ajoutée dans [todo-tree.general.tags](vscode://settings/todo-tree.general.tags)
>
> Il est aussi recommandé d'utiliser l'`Outline` dans le panneau de droite de `VS Code`

## Explication de la refactorisation des coordonnées

La refactorisation des coordonnées a été effectué pour plus de clarté car le système était en **Right-handed Z-up**
(X+ derrière, Y+ droite, Z+ haut), ce qui n'est pas standard, en **Right-handed Y-up** (X+ gauche, Y+ haut, Z+ avant)
Comme dans Minecraft !

## Identification des bugs

Deux accès à des `std::vector` dans `glbasimac/tools/basic_mesh.hpp` faisait crash le programme car il y avait un accès à des données inexistantes (par le temps que la frame prend à s'exécuter)

---

Les chemins pour les shaders étaient en relatif (depuis le dossier `bin`) ce qui contraignait l'exécution depuis EXCLUSIVEMENT bin, si l'on exécutait le .exe sans être placé dans le dossier `bin` cela donnais l'erreur suivante : `ERROR GL : erreur dans le fichier [...]]\src\main.cpp à la ligne 276 : INVALID_VALUE (A numeric argument is out of range)`

J'ai donc modifié `glbi_engine.cpp` pour avoir une variable de chemin pointant vers `assets/` que je met à jour depuis le `main.cpp`

> Avec `assetsPath = (fs::canonical(fs::path(argv[0])).parent_path() / "../assets/").string();` qui :
>
> 1. Converti l'argument 0 (chemin du .exe) en objet `fs::path`
> 2. Récupère son dossier parent (`bin/`)
> 3. Va vers `../assets`
> 4. Nettoie le chemin pour le rendre absolue avec `fs::canonical`
>
> Merci la documentation de filesystem

## Temps passé Nils

- Structure : 8h
- Modélisation du train : 3h30
- Création des primitives + utilisation sur le train : 5h
- Lecture du JSON + en ligne de commande : 2h
- Grille : 1h
- Camera TOP + Refactorisation : 2h
- Refactorisation des coordonnées : 4h30
- Fragmentation : 2h
  Total : 27h
