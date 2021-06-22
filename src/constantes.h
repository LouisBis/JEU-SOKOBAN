/*
constante.h

Par louis marais, en suivant le cours "Apprenez à programmer en C" sur Openclassroom

Rôle : définit des constantes pour tout le programme (taille de la fenêtre...)
*/


#ifndef DEF_CONSTANTES //protège des inclusiosn infinies
#define DEF_CONSTANTES

    #define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    12
    #define NB_BLOCS_HAUTEUR    12
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

    enum {HAUT, BAS, GAUCHE, DROITE}; //pour rendre le code plus lisible
    enum {VIDE ,MUR, CAISSE, OBJECTIF, PERSO, CAISSE_OK};

#endif