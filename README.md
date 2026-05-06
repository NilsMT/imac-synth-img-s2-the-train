Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

# Lancement

Avec les extensions :

Avec [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) et [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) il suffit d'exécuter la cible `[main]`

Avec la ligne de commande (à la racine) :

```
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles"
cd .. && cmake --build ./build --target all --config Debug -j 16
cd bin && ./main.exe
```

> ⚠️ Vous devez exécuter **IMPÉRATIVEMENT** le .exe depuis `/bin` autrement OpenGL donnera cette erreur :
> ERROR GL : erreur dans le fichier E:\IMAC\S2\Synthese Image\imac-synth-img-s2-the-train\src\main.cpp ├á la ligne 204 : INVALID_VALUE (A numeric argument is out of range)

# Structure

```
├───assets : shaders & textures
├───docs : des documents
├───lib : les librairies externes
├───src : les fichiers sources
│   ├───main.cpp : moteur de rendus
│   ├───draw_scene.cpp : les rendus 3D
│   ├───draw_scene.hpp : header de draw_scene
│   ├───railways.hpp : header de railways
│   ├───railways.cpp : structure de sérialisation du JSON
│   └───train_path.json : configuration du circuit de train
└───README.md : ce fichier
```

# Listes des tâches

| Status | Catégorie      | Description                            | Commentaire                              | Qui    |
| ------ | -------------- | -------------------------------------- | ---------------------------------------- | ------ |
| ✅     | 📁Structure    | Créer la structure du projet           | Reprendre la base du TD04 et la modifier | Nils   |
| ❌     | ⚒️Modélisation | Faire les Rails                        | Faire Courbé et Droit                    | Yanis  |
| ✅     | ⚒️Modélisation | Faire le Train                         | + Faire triangle et cylindre fermé       | Nils   |
| ❌     | ⚒️Modélisation | Faire la gare                          |                                          | -      |
| ✅     | 📝JSON         | Lire le JSON (Railways)                | Serialisé en `Railways`                  | Nils   |
| ❌     | 📝JSON         | Créer le parcours                      | Depuis `Railways`                        | Yanis  |
| ❌     | 📝JSON         | Placer la gare et le train             | ez                                       | -      |
| ❌     | 📝JSON         | Lancement avec JSON en argument        | ez                                       | -      |
| ✅     | 🖥️IHM          | Touche pour quitter                    | Touche Q ==> TODO: changer en échap      | Nils   |
| ❌     | 🖥️IHM          | Touche pour toggle modes d'éclairages  | ez                                       | -      |
| ❌     | 🖥️IHM          | Caméra FPS                             | (ZQSD + mouse pan ?)                     | -      |
| ✅     | 👁️Visuel       | Éclairage "flat"                       | Par défaut sur OpenGL                    | OpenGL |
| ❌     | 👁️Visuel       | Éclairage "réaliste" (Phong Shading ?) | Un soleil et phare du train              | -      |
| ❌     | 👁️Visuel       | Texturé un truc                        | Le train ?                               | -      |

> vous devrez positionner une lumière directionnelle (orientée selon
> votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au
> niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être
> texturé !
>
> **Théorie** : c'est le [phong_shading](./assets/shaders/phong_shading.frag) qu'il faut utiliser

# Informations supplémentaires

> Extension pratique pour naviguer dans des endroits du code :<br>
> [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)<br>
> Avec `NOTE:` et `SOURCE:` d'ajoutée dans [todo-tree.general.tags](vscode://settings/todo-tree.general.tags)
