#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quai.h"
#include "menuquai.h"
#include "bateau.h"
#include "sauvegarde.h"

#define NB_QUAIS 4

int main(void)
{
	initialise_listes();
    for (int i = 0; i < 10; i++)
    {
        newBoat(ALEATOIRE, 0);
    }

    afficher_liste_bateau(Liste_bateau);
    afficher_mouillage(mouillage);

	Quai* quai[NB_QUAIS];
	quai[0] = createQuai(0, 300.0, 12.0, MARCHANDISE, 2); 
    quai[1] = createQuai(1, 400.0, 15.0, PETROLIER, 2);   
    quai[2] = createQuai(2, 200.0, 10.0, PASSAGER, 3);    
    quai[3] = createQuai(3, 100.0, 8.0, YACHT, 4);
	int choix;
	do
    {
    	afficheMenu();
	    scanf("%d", &choix);

	    Navire* navire = NULL;
	    int identifiant;
        int numero;

	    switch(choix)
	    {
	    	case 1:
			    printf("Entrez l'ID du navire à ajouter : \n");
			    scanf("%d", &identifiant);

			    navire = malloc(sizeof(Navire));
			    if (navire == NULL) 
			    {
			        printf("Erreur d'allocation mémoire pour le navire !\n");
			        continue;
			    }
			    navire->identifiant = identifiant;
			    printf("Entrez le type du navire (1: Marchandise, 2: Pétrolier, 3: Passager, 4: Yacht) : \n");
			    int type;
			    scanf("%d", &type);
			    if (type < 1 || type > 4) 
			    {
			        printf("Type de navire invalide.\n");
			        free(navire);
			        continue;
			    }
			    navire->type = (TYPE_NAVIRE)type;
			    printf("Entrez la capacité de chargement du navire (en tonnes) : \n");
			    scanf("%f", &navire->capacite_chargement);
			    navire->etat = EN_MER;
			    navire->suivant = NULL;
			    printf("Entrez l'ID du quai :\n");
			    scanf("%d", &numero);

			    if (numero < 1 || numero > 4) 
			    {
			        printf("Quai invalide.\n");
			        free(navire);
			        continue;
			    }

			    accosterNavireQuai(quai[numero - 1], navire);
			    break;

            case 2:
                printf("Entrez l'ID du quai :\n");
                scanf("%d", &numero);

                if (numero < 1 || numero > 4) {
                    printf("Quai invalide.\n");
                    continue;
                }

                afficherQuai(quai[numero - 1]);
                break;
            
            case 3:
			    printf("Entrez l'ID du navire à retirer : \n");
			    scanf("%d", &identifiant);
			    printf("Entrez l'ID du quai : \n");
			    scanf("%d", &numero);

			    if (numero < 1 || numero > 4) {
			        printf("Quai invalide.\n");
			        continue;
			    }

			    quitterQuai(quai[numero - 1], identifiant);
			    break;

			case 4:
			    printf("Entrez l'ID du quai : \n");
			    scanf("%d", &numero);

			    if (numero < 1 || numero > 4) {
			        printf("Quai invalide.\n");
			        continue;
			    }

			    afficheAttente(quai[numero - 1]);
			    break;


            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Réessayez.\n");
	    }

    }while (choix != 5);
}