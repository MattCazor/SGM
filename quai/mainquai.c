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

// liste_bateau *Liste_bateau = NULL;  // Définition
// Mouillage *mouillage = NULL;          // Définition
// id_dispo *Id_Dispo = NULL;            // Définition
// liste_quai *Liste_quai = NULL;

int main(void)
{
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

    createQuai(0, 200.0, 10.0, PASSAGER, 3);
    createQuai(1, 300.0, 12.0, MARCHANDISE, 2);
    createQuai(2, 400.0, 15.0, PETROLIER, 2);
    createQuai(3, 100.0, 8.0, YACHT, 4);

    // newBoat(MARCHANDISE, 45);
    // newBoat(MARCHANDISE, 12);
    // newBoat(PETROLIER, 20);

    afficher_liste_bateau(Liste_bateau);
    afficher_mouillage(mouillage);

    for(int i=0; i<12; i++){
        tri_mouillage(mouillage->premier, Liste_quai->premier);
    }

    // accosterNavireQuai(Liste_quai->premier, mouillage->premier);
    // accosterNavireQuai(Liste_quai->premier, mouillage->premier->mouillage_suiv);
    // accosterNavireQuai(Liste_quai->premier, mouillage->premier->mouillage_suiv->mouillage_suiv);

    afficherQuai(Liste_quai->premier);
    afficherQuai(Liste_quai->premier->suivant);
    afficherQuai(Liste_quai->dernier->precedent);
    afficherQuai(Liste_quai->dernier);

    afficher_mouillage(mouillage);

    srand(time(NULL));
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
    return 0;
}