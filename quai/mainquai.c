#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "quai.h"
#include "bateau.h"
#include "sauvegarde.h"
#include "structures.h"

#define TYPE_NAVIRE 4
#define NB_QUAIS 4

Mouillage zoneMouillage = {0, NULL};
Navire *naviresEnMer = NULL;
Quai *listeQuais = NULL;

int main(void)
{
    srand(time(NULL));
    initialise_listes();
    for (int i = 0; i < 10; i++)
    {
        newBoat(ALEATOIRE, 0);
    }

    // afficher_liste_bateau(Liste_bateau);
    // afficher_mouillage(mouillage);

    // Quai* quai[NB_QUAIS];
    // quai[0] = createQuai(0, 300.0, 12.0, MARCHANDISE, 1);
    // quai[1] = createQuai(1, 400.0, 15.0, PETROLIER, 1);
    // quai[2] = createQuai(2, 200.0, 10.0, PASSAGER, 3);
    // quai[3] = createQuai(3, 100.0, 8.0, YACHT, 4);

    createQuai(0, 200.0, 10.0, PASSAGER, PASSAGER, 3);
    createQuai(1, 300.0, 12.0, MARCHANDISE, PETROLIER, 2);
    createQuai(2, 100.0, 8.0, YACHT, YACHT, 4);

    // newBoat(PASSAGER, 45);
    // newBoat(MARCHANDISE, 12);
    // newBoat(PETROLIER, 20);

    afficher_liste_bateau(Liste_bateau);
    afficher_mouillage(mouillage);
    // accosterNavireQuai(Liste_quai->premier, mouillage->premier);
    // afficherQuai(Liste_quai->premier);
    // quitterQuai(Liste_quai->premier);

    for (int i = 0; i < 12; i++)
    {
        tri_mouillage(mouillage->premier, Liste_quai->premier);
    }

    // accosterNavireQuai(Liste_quai->premier, mouillage->premier);
    // accosterNavireQuai(Liste_quai->premier, mouillage->premier->mouillage_suiv);
    // accosterNavireQuai(Liste_quai->premier, mouillage->premier->mouillage_suiv->mouillage_suiv);

    // afficherQuai(Liste_quai->premier);
    // afficherQuai(Liste_quai->premier->suivant);
    // afficherQuai(Liste_quai->dernier);

    afficher_mouillage(mouillage);

    while (1)
    {
        sleep(2);
        int n = rand() % 3 + 1;
        switch (n)
        {
        case 1:
            quitterQuai(Liste_quai->premier);
            printf("quitte quai 1\n");

            break;

        case 2:
            quitterQuai(Liste_quai->premier->suivant);
            printf("quitte quai 2\n");

            break;

        case 3:
            quitterQuai(Liste_quai->dernier);
            printf("quitte quai \n");

            break;

        default:
            break;
        }
        tri_mouillage(mouillage->premier, Liste_quai->premier);
        afficher_mouillage(mouillage);
        afficherQuai(Liste_quai->premier);
        afficherQuai(Liste_quai->premier->suivant);
        afficherQuai(Liste_quai->dernier);
        savePort(listeQuais, &zoneMouillage, naviresEnMer, "port.txt");
    }

    // while(1)
    // {

    // 	Navire* navire = newBoat(ALEATOIRE, 0);
    //     if (navire == NULL)
    //     {
    //         printf("Erreur lors de la création du navire !\n");
    //         continue;
    //     }
    //     int numero = -1;
    //     switch(navire->type)
    //     {
    //     	case MARCHANDISE:
    //     		numero = 1;
    //     		break;
    //         case PETROLIER:
    //         	numero = 2;
    //         	break;
    //         case PASSAGER:
    //         	numero = 3;
    //         	break;
    //         case YACHT:
    //         	numero = 4;
    //         	break;
    //         default:
    //         	break;
    //     }
    //     if(numero != -1)
    //     {
    //     	if(accosterNavireQuai(quai[numero - 1], navire))
    //             {
    //                  printf("Navire %d accosté sur le quai %d.\n", navire->identifiant, numero);
    //             }
    //         else
    //         {
    //             printf("Échec de l'accostage du navire %d sur le quai %d. Peut-être que le quai est plein.\n", navire->identifiant, numero);
    //             free(navire);
    //         }
    //     }
    //     else
    //     {
    //     	free(navire);
    //     }

    //     for (int i = 0; i < NB_QUAIS; i++)
    //     {
    //         afficherQuai(quai[i]);
    //     }
    //     sleep(5);
    // }
    // Mouillage zoneMouillage = {0, NULL};
    // Navire *naviresEnMer = NULL;
    // Quai *listeQuais = NULL;

    // chargePort(&listeQuais, &zoneMouillage, &naviresEnMer, "port.txt");

    // while (1) {
    //     savePort(listeQuais, &zoneMouillage, naviresEnMer, "port.txt");
    //     sleep(3);
    // }
    return 0;
}