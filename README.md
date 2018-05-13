# ==== TM2DHASHI ==== 

Dans ce dépot vous trouverez, après compilation, deux exécutables du jeu HASHIWOKAKERO.
La première version est la version texte (hashi_graph) jouable directement depuis
le terminal et la seconde est la version graphique (hashi_sdl2) compilé à l'aide
la bibliothèque graphique SDL2.

# Dependences

### Paquet SDL (version 2.0 ou supérieur)

$ sudo apt-get install libsdl2-dev libsdl2-image-dev  libsdl2-ttf-dev

# Compilation

Avec CMake: (Pour ne pas polluer le dépôt il est préférable de creer un dossier build)

$ cd build ; cmake .. ; make ; make install ; cd .. ;



# Run hashi_text

$ ./hashi_text

Sélectionner les deux iles que vous voulez relier à l'aide des options proposées.


# Run hashi_graph

$ ./hashi_graph/nom-du-fichier.txt

 Cliques gauche : ajout de ponts.
 Cliques droit : suppression de ponts.

 # Autre

 1 - Un solveur récursif est aussi disponible dans le dossier solveur/
 Pour l'exécuter, il suffit de lancer aprés la compilation

 $ ./hashi_solve/le_nom_du_fichier.txt

 2 - Les differentes instances du jeu ce trouve dans le dossier map/

 3 - Exécuter le script ./cleanbuil.sh pour suprimer tous les exécutables générés
