# NightmareBeforeChristmas

## Installation

1. Cloner le repository.
2. *(Optionel, si Assimp non installé sur la machine)* Dans le dossier *GLImac-Template/assimp*, lancer les commandes suivantes :

  > $ cmake ./
  
  > $ make

  > $ updatedb 
  
3. Créer un dossier de build (ici nous crerons un dossier *build* au même niveau que le dossier *GLImac-Template*).
4. Dans le dossier créé, faire un cmake du dossier *GLImac-Template*. Exemple ici dans notre dossier *build* :

  > $ cd /build
  
  > $ cmake ../GLImac-Template
  
  > $ make
  
5. Pour lancer l'application, lancer le fichier *dev_main*. Exemple ici dans notre dossier *build* :

  > $ cd /build
  
  > $ ./dev/dev_main

## Utilisation

Utiliser les fleches gauche et droite pour passer d'une scène à une autre.

Alt+F4 pour quitter l'application.

Clic gauche + mouvement de la souris pour déplacer la caméra dans l'espace.

Clicl droit + mouvement vertical de la souris pour zoomer / dézoomer sur le centre de la scène.

## Code

Le dossier du projet est le dossier *GLImac-Template/dev*.

L'ensemble des *.hpp* et *.cpp* sur lesquels nous avons travaillé sont dans *GLImac-Template/projet*.

Le dossier *assets* contient les fichiers pour les scènes, les fichiers 3D et les textures.

## Libraries

Jsoncpp (http://jsoncpp.sourceforge.net/) a été utilisé pour charger les fichiers JSON dans lesquels nous indiquons la structure des scènes.

## Module de tests unitaires

Le module de tests unitaires du projet utilise gtest.

Pour obtenir des éxécutables de tests il suffit de créer des fichiers .cpp contenant les tests à effectuer dans le dossier tests du projet.
Les test seront compilés en même temps que les autres fichiers du projets.
Pour lancer un éxécutable il suffit de se rendre dans le dossier de build > tests et de lancer l'éxécutable souhaité.
