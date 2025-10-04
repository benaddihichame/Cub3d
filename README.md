cub3D
Description
cub3D est un projet de l'école 42 qui consiste à créer un moteur de rendu 3D basé sur le raycasting, inspiré du célèbre jeu Wolfenstein 3D. Ce projet permet de découvrir les bases de la programmation graphique et de comprendre comment fonctionnait le rendu 3D dans les années 90.
Objectifs du projet

Créer une vue en 3D première personne à l'intérieur d'un labyrinthe
Implémenter l'algorithme de raycasting
Gérer les textures sur les murs
Gérer les événements clavier et souris
Respecter la norme de 42

Technologies utilisées

Langage : C
Bibliothèque graphique : MiniLibX
Makefile pour la compilation

Fonctionnalités
Fonctionnalités obligatoires

✅ Affichage d'une vue 3D en temps réel
✅ Gestion des textures différentes selon l'orientation du mur (Nord, Sud, Est, Ouest)
✅ Couleurs différentes pour le sol et le plafond
✅ Déplacement avec les touches W, A, S, D
✅ Rotation de la vue avec les flèches gauche/droite
✅ Fermeture propre de la fenêtre avec ESC ou le bouton de fermeture
✅ Parsing d'un fichier de configuration .cub

Fonctionnalités bonus (optionnelles)

Collisions avec les murs
Minimap
Portes qui s'ouvrent et se ferment
Objets animés (sprites)
Rotation de la vue avec la souris

Structure du fichier .cub
Le fichier de configuration définit la carte et les paramètres du jeu :
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

111111111111111111111111
100000000000000000000001
101100000111000000001101
100100000000000000000001
111110111N00111000000001
100000001000001000000001
100000000000000000000001
111111111111111111111111
Légende

NO, SO, WE, EA : Chemins vers les textures des murs
F : Couleur RGB du sol
C : Couleur RGB du plafond
1 : Mur
0 : Espace vide
N, S, E, W : Position et orientation de départ du joueur

Installation
bash# Cloner le repository
git clone [votre-repo] cub3d
cd cub3d

# Compiler le projet
make

# Compiler avec les bonus (si implémentés)
make bonus
Utilisation
bash./cub3D maps/map.cub
Contrôles

W/A/S/D : Se déplacer
←/→ : Tourner la caméra
ESC : Quitter le jeu

Architecture du projet
cub3d/
├── srcs/
│   ├── main.c
│   ├── parsing/
│   │   ├── parser.c
│   │   ├── map_validation.c
│   │   └── texture_loader.c
│   ├── rendering/
│   │   ├── raycasting.c
│   │   ├── draw.c
│   │   └── textures.c
│   ├── game/
│   │   ├── player.c
│   │   ├── movement.c
│   │   └── events.c
│   └── utils/
│       ├── error.c
│       ├── free.c
│       └── utils.c
├── includes/
│   └── cub3d.h
├── maps/
│   ├── valid_map.cub
│   └── test_maps/
├── textures/
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm
├── Makefile
└── README.md
Concepts clés
Raycasting
Le raycasting est une technique de rendu 3D qui consiste à lancer des rayons depuis la position du joueur pour déterminer la distance aux murs et calculer leur hauteur à l'écran.
DDA (Digital Differential Analysis)
Algorithme utilisé pour parcourir la grille et détecter les intersections avec les murs.
Projection
Transformation des coordonnées du monde 3D vers l'écran 2D en utilisant une projection perspective.
Gestion des erreurs
Le programme doit gérer proprement les erreurs suivantes :

Fichier .cub invalide ou manquant
Carte non fermée par des murs
Textures manquantes ou invalides
Couleurs RGB hors limites
Plusieurs positions de départ
Caractères invalides dans la carte

Ressources utiles

Tutoriel Raycasting de Lodev
Documentation MiniLibX
Wolfenstein 3D Source Code
