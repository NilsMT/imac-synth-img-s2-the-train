Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

# Lancement

Avec les extensions :

Avec [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) et [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) il suffit d'exécuter la cible `[main]`

Avec la ligne de commande (à la racine) :

```sh
mkdir -p build && cd build
cmake .. -G "MinGW Makefiles"
cd .. && cmake --build ./build --target all --config Debug -j 16
cd bin && ./main.exe fichier/a/lire.json
```

> ⚠️ Vous devez **IMPÉRATIVEMENT** exécuter le .exe depuis `/bin` autrement OpenGL donnera cette erreur :
> `ERROR GL : erreur dans le fichier E:\IMAC\S2\Synthese Image\imac-synth-img-s2-the-train\src\main.cpp ├á la ligne 204 : INVALID_VALUE (A numeric argument is out of range)`
>
> ℹ️ L'erreur `terminate called after throwing an instance of 'nlohmann::detail::parse_error'
  what():  [json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '[', '{', or a literal` signifie que le fichier JSON est inexistant ou invalide

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

| Status | Catégorie      | En + | Description                            | Commentaire                         | Qui    |
| ------ | -------------- | ---- | -------------------------------------- | ----------------------------------- | ------ |
| ✅     | 📁Structure    |      | Créer la structure du projet           | Reprendre la base du TD04           | Nils   |
| ❌     | ⚒️Modélisation |      | Faire les Rails                        | Faire Courbé et Droit               | Yanis  |
| ✅     | ⚒️Modélisation |      | Faire le Train                         | + Faire triangle et cylindre fermé  | Nils   |
| ❌     | ⚒️Modélisation |      | Faire la Gare                          |                                     | -      |
| ✅     | 📝JSON         |      | Lire le JSON (Railways)                | Serialisé en `Railways`             | Nils   |
| ❌     | 📝JSON         |      | Créer le parcours                      | Depuis `Railways`                   | Yanis  |
| ❌     | 📝JSON         |      | Placer la gare et le train             |                                     | -      |
| ✅     | 📝JSON         |      | Lancement avec JSON en argument        |                                     | Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes d'éclairages  | Touche F                            | Nils   |
| ❌     | 🖥️IHM          |      | Caméra FPS                             | ZQSD/WASD to move, Pan to rotate    | -      |
| ✅     | 🖥️IHM          |      | Caméra ORBITAL                         | ZQSD/WASD to rotate, Scroll to zoom | Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes camera        | Touche C                            | -      |
| ✅     | 👁️Rendu        |      | Éclairage "flat"                       | Par défaut sur OpenGL               | OpenGL |
| ❌     | 👁️Rendu        |      | Éclairage "réaliste" (Phong Shading ?) | Un soleil et phares du train        | -      |
| ❌     | 👁️Rendu        |      | Texturé un truc                        | Avant du train                      | -      |
| ✅     | 📁Structure    | ☑️   | Refactorisation des coordonnées        | Voir informations supplémentaires   | Nils   |
| ✅     | ⚒️Modélisation | ☑️   | Grille des cellules de rails           | Pour visualiser le placement        | Nils   |
| ❌     | ⚒️Modélisation | ☑️   | Modéliser (+ placer) du décors         | Genre un arbre                      | -      |
| ❌     | 📝JSON         | ☑️   | Ajouter des trucs dans le JSON         |                                     | Nils   |
| ✅     | 🖥️IHM          | ☑️   | Touche pour quitter                    | Touche Échap                        | Nils   |
| ✅     | 🖥️IHM          | ☑️   | Touche pour toggle modes de rendu      | Touche R                            | Nils   |
| ✅     | 🖥️IHM          | ☑️   | Caméra TOP                             | ZQSD/WASD to move, Scroll to zoom   | Nils   |
| ✅     | 🖥️IHM          | ☑️   | Touche pour toggle grille              | Touche G                            | Nils   |
| ❌     | 👁️Rendu        | ☑️   | Animer le train                        |                                     | -      |
| ❌     | 👁️Rendu        | ☑️   | Ajouter des lumières                   | Genre à la gare                     | -      |

> vous devrez positionner une lumière directionnelle (orientée selon
> votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au
> niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être
> texturé !

# Informations supplémentaires

> Extension pratique pour naviguer dans des endroits du code sur `VS Code` :<br>
> [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)<br>
> Avec `NOTE:` et `SOURCE:` d'ajoutée dans [todo-tree.general.tags](vscode://settings/todo-tree.general.tags)
>
> Il est aussi recommandé d'utiliser l'`Outline` dans le panneau de droite de `VS Code`

> La refactorisation des coordonnées a été effectué pour plus de clarté car le système était en **Right-handed Z-up**
> (X+ derrière, Y+ droite, Z+ haut), ce qui n'est pas standard, en **Right-handed Y-up** (X+ gauche, Y+ haut, Z+ avant)
> Comme dans Minecraft !

> Temps passée Nils :
>
> - Structure : 8h
> - Modélisation du train : 3h30
> - Création des primitives + utilisation sur le train : 5h
> - Lecture du JSON + en ligne de commande : 2h
> - Grille : 1h
> - Camera TOP + Refactorisation : 2h
> - Refactorisation des coordonnées : 4h30
>
> Total : 26h
