# NightmareBeforeChristmas

## Installation

1. Cloner le repository
2. *(Optionel, si Assimp non installé sur la machine)* Dans le dossier *GLImac-Template/assimp*, lancer les commandes suivantes (la dernière n'est peut-être pas obligatoire) :

  > $ cmake ./
  
  > $ make

  > $ updatedb 

## Utilisation

Utiliser les fleches gauche et droite pour passer d'une scène à une autre.
Alt+F4 pour quitter l'application.

Clic gauche + mouvement de la souris pour déplacer la caméra dans l'espace.

Clicl droit + mouvement vertical de la souris pour zoomer / dézoomer sur le centre de la scène.

## Code

Le dossier du projet est le dossier *GLImac-Template/dev*.
L'ensemble des *.hpp* et *.cpp* sur lesquels nous avons travaillé sont dans *GLImac-Template/projet*.

## Libraries

Jsoncpp (http://jsoncpp.sourceforge.net/) a été utilisé pour charger les fichiers JSON dans lesquels nous indiquons la structure des scènes.

## Module de tests unitaires

Le module de tests unitaires du projet utilise gtest.

Pour obtenir des éxécutables de tests il suffit de créer des fichiers .cpp contenant les tests à effectuer dans le dossier tests du projet.
Les test seront compilés en même temps que les autres fichiers du projets.
Pour lancer un éxécutable il suffit de se rendre dans le dossier de build > tests et de lancer l'éxécutable souhaité.
