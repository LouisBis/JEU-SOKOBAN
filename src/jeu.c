/*
jeu.c

Par Louis Marais, en suivant le cours "Apprenez en programmer en C" sur Openclassroom

Rôle : C'est le jeu en lui même
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "fichiers.h"


void jouer(SDL_Surface* ecran)
{
    SDL_Surface *perso[4]={NULL}; //pour les 4 positions du personnage
    SDL_Surface *persoActuel = NULL, *caisse = NULL, *caisseOK=NULL, *objectif=NULL, *mur = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;

    int continuer = 1, objectifRestants, i,j;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0}; //on crée un tableau de 12x12 comme carte

    mur = IMG_Load("image/mur.jpg");
    caisse = IMG_Load("image/caisse.png");
    caisseOK = IMG_Load("image/caisseOK.png");
    objectif = IMG_Load("image/objectif.png");
    perso[BAS] = IMG_Load("image/perso_bas.png");
    perso[GAUCHE] = IMG_Load("image/perso_gauche.png");
    perso[HAUT] = IMG_Load("image/perso_haut.png");
    perso[DROITE] = IMG_Load("image/perso_droite.png");

    persoActuel = perso[BAS];

    if (!chargerNiveau(carte))//on charge le niveau avec test d'erreur
    {
        fprintf(stderr,"Erreur lors du chargement de la carte : %s",SDL_GetError);
        exit(EXIT_FAILURE);
    }

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)//on cherche la position du perso
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == PERSO) // Si le personnage se trouve à cette position
            {
                positionJoueur.x = i;//alors on enregistre les coordonées
                positionJoueur.y = j;
                carte[i][j] = VIDE;//et on le retire de la carte
            }
        }
    }

    SDL_EnableKeyRepeat(100, 100); //on active l'appuie continu

    while(continuer)//boucle pour afficher le jeu
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: //Pour quitter
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE://Pour quitter
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        persoActuel = perso[HAUT];//on change l'image du perso
                        deplacerJoueur(carte, &positionJoueur, HAUT);//et sa position 
                        break;
                    case SDLK_DOWN:
                        persoActuel = perso[BAS];
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;
                    case SDLK_RIGHT:
                        persoActuel = perso[DROITE];
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;
                    case SDLK_LEFT:
                        persoActuel = perso[GAUCHE];
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;
                }
                break;
        }
    

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 63, 65, 78));//on efface l'écran

        objectifRestants = 0; //on initialise le nb d'objectifs

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)//on défile en largeur
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)//on défile en hauteur
            {
                position.x = i * TAILLE_BLOC;//pour avoir les coordonnées en pixel et non en bloc
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j]) //on va coller le niveau selon la carte
                {   
                    case MUR: 
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifRestants = 1;
                        break;
                }
            }
        }

        if (!objectifRestants)//si plus d'objectif on sort de la boucle jeu
            continuer = 0;

        position.x = positionJoueur.x * TAILLE_BLOC;//pour avori les coordonnées du perso en pixel et non bloc
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(persoActuel, NULL, ecran, &position);//on colle le perso

        SDL_Flip(ecran);
    } //on sort du jeu


    SDL_EnableKeyRepeat(0, 0);//on désactive l'appuie continue

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(perso[i]);//on libère les 4 surface du perso
} 

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
    switch(direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur dépasse de l'écran
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur au dessus
                break;

            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) && //S'il y a une caisse ou une caisse OK
            (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||//et que au dessus c'est hors map ou il y a un mur
            carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))//ou il y a une caisse ou une caisse OK
                break;

            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);// si non on peu déplacer la caisse et le perso
            pos->y--; //On déplace le joueur
            break;
            
        case BAS:
            if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
                break;
            if (carte[pos->x][pos->y + 1] == MUR) 
                break;
            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
            (pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
            carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
                break;
            
            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
            pos->y++; //On déplace le joueur
            break;

        case DROITE:
            if (pos->x +1 >= NB_BLOCS_LARGEUR) // Si le joueur dépasse de l'écran en haut
                break;
            if (carte[pos->x + 1 ][pos->y] == MUR) // S'il y a un mur au dessus
                break;

            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
            (pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
            carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
                break;

            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
            pos->x++;
            break;
            
        case GAUCHE:
            if (pos->x - 1 < 0) // Si le joueur dépasse de l'écran en haut
                break;
            if (carte[pos->x - 1 ][pos->y] == MUR) // S'il y a un mur au dessus
                break;

            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
            (pos->x - 2 >= NB_BLOCS_LARGEUR || carte[pos->x - 2][pos->y] == MUR ||
            carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
                break;

            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
            pos->x--;
            break;
    }
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)//Si la premiere case est une caisse ou caisse OK
    {
        if (*secondeCase == OBJECTIF)//Et si la seconde case est l'objectif
            *secondeCase = CAISSE_OK;//Alors la seconde case devient caisse OK
        else
            *secondeCase = CAISSE;//Sinon la seconde case devient caisse

        if (*premiereCase == CAISSE_OK)//Si la premiere case est une caisse OK
            *premiereCase = OBJECTIF;//Alors elle devient objectif(car on vient de deplacer la caisse)
        else
            *premiereCase = VIDE;//sinon elle devient vide
    }
    //ça marche car on a déja limité les déplacement lors de la fonction deplacerJoueur
}
