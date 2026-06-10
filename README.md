Projet initialisé sur la base du TD04 de synthèse d'image, et remaniée de manière archaïque au niveau des `CMakeLists.txt` et de la structure des librairies

# Structure

```
├───📁 assets : shaders & textures
├───📁 data : fichiers JSON de rails
│   └─── 📄 DATADESC.md : description des données JSON
├───📁 docs : documents et diagrammes
├───📁 lib : librairies
├───📁 src : code source
│   ├───📁 camera : gestion des caméras et des entrées utilisateur
│   ├───📁 lighting : gestion de l'éclairage (placement des lights)
│   ├───📁 global : éléments partagés
│   ├───📁 texture : utilitaires de chargement et de gestion de textures
│   ├───📁 draw : rendu des objets 3D (rails, train, gare, arbres, scène)
│   │   └───📄 shared.cpp : helpers et constantes partagées entre les dessins
│   ├───📄 main.cpp : point d'entrée, initialisation et boucle principale
│   └───📄 json_data.hpp : structures de sérialisation JSON
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
> ✅ = Fait 🚧 = En cours ❌ = À faire

| Status | Catégorie      | En + | Description                           | Commentaire                              | Qui      |
| ------ | -------------- | ---- | ------------------------------------- | ---------------------------------------- | -------- |
| ✅     | 📁Structure    |      | Créer la structure du projet          | Reprendre la base du TD04                | 🔵Nils   |
| ✅     | 📁Structure    |      | Fragmentation du draw_scene           |                                          | 🔵Nils   |
| ✅     | ⚒️Modélisation |      | Faire les Rails                       | Faire Courbé et Droit                    | 🟠Yanis  |
| ✅     | ⚒️Modélisation |      | Faire le Train                        | + Faire triangle et cylindre fermé       | 🔵Nils   |
| ✅     | ⚒️Modélisation |      | Faire la Gare                         |                                          | 🔵Nils   |
| ✅     | 📝JSON         |      | Lire le JSON (JsonData)               | Serialisé en `JsonData`                  | 🔵Nils   |
| ✅     | 📝JSON         |      | Créer le parcours                     | Depuis `JsonData`                        | 🔵Nils   |
| ✅     | 📝JSON         |      | Placer la gare                        |                                          | 🔵Nils   |
| ✅     | 📝JSON         |      | Placer le train                       |                                          | 🔵Nils   |
| ✅     | 📝JSON         |      | Lancement avec JSON en argument       |                                          | 🔵Nils   |
| ✅     | 🖥️IHM          |      | Touche pour quitter                   | Touche Échap                             | 🔵Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes d'éclairages | Touche F                                 | 🔵Nils   |
| ✅     | 🖥️IHM          |      | Caméra FPS                            | ZQSD to move where facing, Pan to rotate | 🔵Nils   |
| ✅     | 🖥️IHM          |      | Caméra ORBITAL                        | ZQSD to rotate, Scroll to zoom           | 🔵Nils   |
| ✅     | 🖥️IHM          |      | Touche pour toggle modes camera       | Touche C                                 | 🔵Nils   |
| ✅     | 👁️Rendu        |      | Éclairage "flat"                      | Par défaut sur OpenGL                    | 🟢OpenGL |
| ✅     | 👁️Rendu        |      | Éclairage "réaliste" `*`              | Un soleil et phares du train             | 🔵Nils   |
| ✅     | 👁️Rendu        |      | Texturé un truc                       | Avant du train OU le sol                 | 🟠Yanis  |
| ✅     | 📁Structure    | ♒   | Refactorisation des coordonnées       | Voir Informations supplémentaires        | 🔵Nils   |
| ✅     | 📁Structure    | ♒   | Correction des bugs                   | Voir Informations supplémentaires        | 🔵Nils   |
| ✅     | 📁Structure    | ♒   | Optimisation du moteur de rendu       | Voir Informations supplémentaires        | 🔵Nils   |
| ✅     | 🖥️IHM          | ♒   | Touche pour toggle modes de rendu     | Touche R                                 | 🔵Nils   |
| ✅     | 🖥️IHM          | ♒   | Caméra TOP                            | ZQSD to move (X,Z), Scroll to zoom (Y)   | 🔵Nils   |
| ✅     | 🖥️IHM          | ♒   | Touche pour toggle grille             | Touche G                                 | 🔵Nils   |
| ✅     | ⚒️Modélisation | ♒   | Grille des cellules de rails          | Pour visualiser le placement             | 🔵Nils   |
| ✅     | ⚒️Modélisation | ♒   | Primitives supplémentaires            | Triangle rectangle et cylindre fermé     | 🔵Nils   |
| ✅     | ⚒️Modélisation | ☑️   | Modéliser (+ placer) du décors        | Genre un arbre                           | 🔵Nils   |
| ✅     | 📝JSON         | ☑️   | Ajouter des trucs dans le JSON        | Placement d'arbres                       | 🔵Nils   |
| ❌     | 👁️Rendu        | ☑️   | Animer le train                       | Ptet avec des fonctions dans les rails   | -        |
| ❌     | 👁️Rendu        | ☑️   | Ajouter des lumières                  | Genre à la gare                          | -        |

> `*` = D'après le PDF : _"vous devrez positionner une lumière directionnelle (orientée selon votre choix mais qui éclaire la scène comme un soleil), et une source de lumière ponctuelle au niveau de l’avant de votre train. Par ailleurs au moins un élément de votre application devra être texturé !"_
