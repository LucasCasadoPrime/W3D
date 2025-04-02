# W3D - Wolfenstein 3D Remake avec SFML

## Description
W3D est un remake en C++ du célèbre jeu **Wolfenstein 3D**, utilisant la bibliothèque **SFML**. Ce projet propose une reproduction fidèle du gameplay original tout en permettant aux joueurs de créer leurs propres cartes.

## Fonctionnalités
- Moteur de rendu en **raycasting**
- Déplacements fluides inspirés du jeu original
- Gestion des collisions et des interactions
- Possibilité de créer et charger des **maps personnalisées**
- Support de textures et animations
- Effets sonores et musique immersive

## Prérequis
Avant de compiler et exécuter W3D, assurez-vous d'avoir installé :
- **C++17** ou une version ultérieure
- **SFML 2.5** ou plus récent

## Installation
1. **Cloner le dépôt** :
   ```sh
   git clone https://github.com/votre-utilisateur/W3D.git
   cd W3D
   ```
2. **Compiler le projet** :
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. **Lancer le jeu** :
   ```sh
   ./W3D
   ```

## Création de cartes personnalisées
Le jeu supporte des fichiers de cartes personnalisées en format **.txt**.
- Chaque caractère représente un type de bloc (mur, sol, porte...)
- Exemple de structure simple :
  ```
  PX=22
  PY=11
  888888888884464464644464
  800000000084000000000004
  803000000884000000000006
  800300000000000000000006
  803300000884000000000004
  800000000084000006660646
  888808888884444446000006
  777707777090808084040606
  770000007808080886000006
  700000000000000086000004
  700000000000000086060606
  770000007800080886460666
  777707777884068483330333
  222202222464006063000003
  220000022400000043000003
  200000002400000043000003
  100000001444446063300033
  200000002221222660050505
  220000022200022050500055
  200000002000002505050505
  100000000000000000000005
  200000002000002505050505
  220000022200022050500055
  222212222221222555555555
  ```
- Placez vos cartes dans le dossier `maps/` et chargez-les via le menu du jeu.

## Contribuer
Les contributions sont les bienvenues !
1. Forkez le repo
2. Créez une branche (`git checkout -b feature-ma-fonctionnalite`)
3. Faites vos modifications et committez (`git commit -m 'Ajout d'une nouvelle fonctionnalité'`)
4. Poussez votre branche (`git push origin feature-ma-fonctionnalite`)
5. Créez une Pull Request

## Licence
Ce projet est sous licence **MIT** - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Auteur
- **Votre Nom** - [Votre Profil GitHub](https://github.com/votre-utilisateur)

