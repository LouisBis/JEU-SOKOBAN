/*
main.c

Par Louis Marais, en suivant le cours "Apprenez en programmer en C" sur Openclassroom

Rôle : C'est le menu du jeu, il permet de selectionner d'accéder au jeu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "fichiers.h"


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;


    if (SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        fprintf(stderr,"Erreur d'initialisation :%s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE);
    if(!ecran)
    {
        fprintf(stderr,"Impossible de charger le mode vidéo : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Sokoban", NULL);

    menu = IMG_Load("image/menu.jpg");
    positionMenu.x=0;
    positionMenu.y=0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        jouer(ecran);//on passe au jeu
                        break;
                }
            break;
        }
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
