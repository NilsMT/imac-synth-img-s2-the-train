Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

# Sommaire

- [Sommaire](#sommaire)
- [Lancement](#lancement)
  - [Avec les extensions :](#avec-les-extensions-)
  - [Avec la ligne de commande :](#avec-la-ligne-de-commande-)
- [Structure](#structure)
- [Guide des touches](#guide-des-touches)
- [Listes des tâches](#listes-des-tâches)
- [Listes des tâches annexes](#listes-des-tâches-annexes)
- [Informations supplémentaires](#informations-supplémentaires)
  - [Informations utiles](#informations-utiles)
  - [Explication de la refactorisation des coordonnées](#explication-de-la-refactorisation-des-coordonnées)
  - [Identification des bugs](#identification-des-bugs)
  - [Optimisation du moteur de rendu](#optimisation-du-moteur-de-rendu)
  - [Informations ajoutées au JSON](#informations-ajoutées-au-json)

# Lancement

## Avec les extensions :

Avec [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) et [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) il suffit d'exécuter la cible `[main]`.

## Avec la ligne de commande :

Depuis la racine faire :

```sh
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles"
cd .. && cmake --build ./build --target all --config Debug -j 16
cd bin && ./main.exe fichier/a/lire.json
```

Exemple : `./main.exe ../data/path_1.json`.

> Les commandes précédent l'exécution peuvent ne pas marcher ou être différentes selon l'ordinateur.

# Structure

```
├───📁 assets : shaders & textures
├───📁 data : les dossiers avec les json de rails
│   └─── DATADESC.md : décrit les fichiers de données
├───📁 docs : des documents
├───📁 lib : les librairies externes
├───📁 src : les fichiers sources
│   ├───📁 draw : les fichiers individuels des rendus 3D
│   │   └───📄 shared.cpp : contient les valeurs globales utilisées par les autres (dont les unités sr, sx, rr et myEngine)
│   ├───📄 main.cpp : moteur de rendus
│   └───📄 json_data.hpp : structure de sérialisation du JSON
└───📄 README.md : ce fichier
```

> Il y a des dossiers dans `src/` qui contiennent des `.hpp` et `.cpp`

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

| Status | Catégorie      | Bonus | Description                           | Commentaire                  |
| ------ | -------------- | ----- | ------------------------------------- | ---------------------------- |
| ✅     | 📁Structure    |       | Créer la structure du projet          | Reprendre la base du TD04    |
| ✅     | ⚒️Modélisation |       | Faire rail droite                     |                              |
| ✅     | ⚒️Modélisation |       | Faire rail courbé                     |                              |
| ✅     | ⚒️Modélisation |       | Faire le Train                        |                              |
| ✅     | ⚒️Modélisation |       | Faire la Gare                         |                              |
| ✅     | 📝JSON         |       | Lire le JSON (JsonData)               | Serialisé en `JsonData`      |
| ❌     | 📝JSON         |       | Créer le parcours                     | Depuis `JsonData`            |
| ✅     | 📝JSON         |       | Placer la gare                        |                              |
| ❌     | 📝JSON         |       | Placer le train                       |                              |
| ✅     | 📝JSON         |       | Lancement avec JSON en argument       |                              |
| ✅     | 🖥️IHM          |       | Touche pour quitter                   | Touche Échap                 |
| ✅     | 🖥️IHM          |       | Touche pour toggle modes d'éclairages | Touche F                     |
| ✅     | 🖥️IHM          |       | Caméra FPS                            | ZQSD + Mouvement souris      |
| ✅     | 🖥️IHM          |       | Caméra ORBITAL                        | ZQSD + Scroll                |
| ✅     | 🖥️IHM          |       | Touche pour toggle modes camera       | Touche C                     |
| ❌     | 👁️Rendu        |       | Éclairage "réaliste" `*`              | Un soleil et phares du train |
| ✅     | 👁️Rendu        |       | Texturé un truc                       | Avant du train OU le sol     |
| ✅     | ⚒️Modélisation | ☑️    | Modéliser (+ placer) du décors        | Genre un arbre               |
| ✅     | 📝JSON         | ☑️    | Ajouter des trucs dans le JSON        | Placement d'arbres           |
| ❌     | 👁️Rendu        | ☑️    | Animer le train                       |                              |
| ❌     | 👁️Rendu        | ☑️    | Ajouter des lumières                  | Genre à la gare              |

> `*` = D'après le PDF : _"vous devrez positionner une lumière directionnelle (orientée selon votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être texturé !"_

# Listes des tâches annexes

Des tâches non-énumérés dans le PDF

| Status | Catégorie      | Description                       | Commentaire                          |
| ------ | -------------- | --------------------------------- | ------------------------------------ |
| ✅     | 📁Structure    | Refactorisation des coordonnées   | Voir Informations supplémentaires    |
| ✅     | 📁Structure    | Correction des bugs               | Voir Informations supplémentaires    |
| ✅     | 📁Structure    | Optimisation du moteur de rendu   | Voir Informations supplémentaires    |
| ✅     | 🖥️IHM          | Touche pour toggle modes de rendu | Touche R                             |
| ✅     | 🖥️IHM          | Caméra TOP                        | ZQSD (X,Z) + Scroll (Y)              |
| ✅     | 🖥️IHM          | Touche pour toggle grille         | Touche G                             |
| ✅     | ⚒️Modélisation | Grille des cellules de rails      | Pour visualiser le placement         |
| ✅     | ⚒️Modélisation | Primitives supplémentaires        | Triangle rectangle et cylindre fermé |

# Informations supplémentaires

## Informations utiles

Il y a une extension pratique pour naviguer dans des endroits du code sur `VS Code` :<br>
[Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)<br>
Avec `NOTE:` d'ajoutée dans le paramètre de l'extension [todo-tree.general.tags](vscode://settings/todo-tree.general.tags).

Il est aussi recommandé d'utiliser l'`Outline` dans le panneau de droite de `VS Code`.

Il y a un document [DATADESC.md](./data/DATADESC.md) qui décrit les fichiers JSON et leurs visualisations.

## Explication de la refactorisation des coordonnées

La refactorisation des coordonnées a été effectué pour plus de clarté car le système était en **Right-handed Z-up**
(X+ derrière, Y+ droite, Z+ haut), ce qui n'est pas standard, en **Right-handed Y-up** (X+ gauche, Y+ haut, Z+ avant).

Comme dans Minecraft !

## Identification des bugs

Deux accès à des `std::vector` dans `glbasimac/tools/mesh.hpp` faisait crash le programme car il y avait un accès à des données inexistantes sur les ID de VBO (par le temps que la frame prend à s'exécuter) lors de la "vidange" du Buffer

> Qui causait l'erreur `[...] std::vector<_Tp, _Alloc>::size_type = long unsigned int]: Assertion '__n < this->size()' failed.` et parfois sans s'afficher dans la console.

---

Les chemins pour les shaders étaient en relatif (depuis le dossier `bin`) ce qui contraignait l'exécution depuis EXCLUSIVEMENT bin, si l'on exécutait le .exe sans être placé dans le dossier `bin` cela donnais l'erreur suivante : `ERROR GL : erreur dans le fichier [...]\src\main.cpp à la ligne 276 : INVALID_VALUE (A numeric argument is out of range)`.

Nous avons donc modifié `glbi_engine.cpp` pour avoir une variable de chemin pointant vers `assets/` qui se met à jour depuis le `main.cpp`.

> Avec `assetsPath = (fs::path(argv[0]).parent_path() / "../assets/").string();` qui :
>
> 1. Converti l'argument 0 (chemin du .exe) en objet `fs::path`
> 2. Récupère son dossier parent (`bin/`)
> 3. Va vers `../assets`
>
> Merci la documentation de filesystem.

## Optimisation du moteur de rendu

Les géométries et les points était initialisés de 0 dans `glbi_convex_2D_shape.cpp` et `glbi_set_of_points.cpp` ce qui faisait éventuellement crash et causait de la latence dans le programme.
Nous avons donc ajouté des `.reInit()` dans ces fichiers pour éviter cela.

## Informations ajoutées au JSON

Le JSON possède une information en plus : une liste de positions ou il y a des arbres.
