Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

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

- Modélisation
    - Rails
        - Courbé
        - Droit
    - Train ✅
    - Gare
- JSON
    - Lire le JSON ✅ (+ il se sérialise en `Railways`)
    - Créer le parcours de rail en conséquence
    - Placer la gare
    - Placer le train
    - Permettre le lancement de l'application avec le json (que le nom askip, mais pourquoi pas le chemin direct ?) en argument de la ligne de commande
- Commandes
    - Une touche pour quitter l'application ✅ (Q)
    - Une touche pour activer/désactiver l'éclairage
    - Caméra FPS (et pas orbitale comme il y a de base ici)
- Illumination
    - Éclairage "flat" : celui par défaut sur OpenGL ✅
    - Éclairage "réaliste"
    - > vous devrez positionner une lumière directionnelle (orientée selon
      > votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au
      > niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être
      > texturé !
      >
      > **Théorie** : c'est le [phong_shading](./assets/shaders/phong_shading.frag) qu'il faut utiliser

# Informations supplémentaires

> Extension pratique pour naviguer dans des endroits du code :<br>
> [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree)<br>
> Avec `NOTE:` et `SOURCE:` d'ajoutée dans [todo-tree.general.tags](vscode://settings/todo-tree.general.tags)
