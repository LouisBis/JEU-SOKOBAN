/*
jeu.h

Par Louis Marais, en suivant le cours "Apprenez en programmer en C" sur Openclassroom

Rôle : On y trouve toutes les prototype de jeu.c
*/
#ifndef DEF_JEU
#define DEF_JEU

    void jouer(SDL_Surface* ecran);
    void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
    void deplacerCaisse(int *premiereCase, int *secondeCase);


#endif