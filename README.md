# NightmareBeforeChristmas

## Installation

1. Cloner le repository
2. Dans le dossier *GLImac-Template/assimp*, lancer les commandes suivantes (la dernière n'est peut-être pas obligatoire) :

  > $ cmake ./
  
  > $ make

  > $ updatedb 

## Code

Le dossier du projet est le dossier *GLImac-Template/dev*

## Module de tests unitaires

Le module de tests unitaires du projet utilise gtest.

Pour obtenir des éxécutables de tests il suffit de créer des fichiers .cpp contenant les tests à effectuer dans le dossier tests du projet.
Les test seront compilés en même temps que les autres fichiers du projets.
Pour lancer un éxécutable il suffit de se rendre dans le dossier de build > tests et de lancer l'éxécutable souhaité.
