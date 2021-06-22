/*
fichiers.c

Par Louis Marais, en suivant le cours "Apprenez en programmer en C" sur Openclassroom

Rôle : Permet la gestion des fichiers/carte
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0}; //on crée un tab de char pour stocker temporairement le niveau
    //+1 pour le caractère de fin de chaine \0
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
    {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier, chragement du niveau %s", SDL_GetError);
        return 0;
    }
    
    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
    //on lit le fichier

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':// les '' car se sont des char stocké et non des int
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
            }
        }
    }
    //on le retranscrit dans niveau

    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
    FILE* fichier = NULL;
    int i,j;

    fichier = fopen("niveaux.lvl", "w");
    if (fichier == NULL)
        return 0;


    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)//lit en largeur
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)//lit en hauteur
        {
            fprintf(fichier, "%d", niveau[j][i]);//on save le niveau
        }
    }

    fclose(fichier);
    return 1;
}
