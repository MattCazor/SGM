#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "quai.h"

#define TYPE_NAVIRE 4
#define NB_QUAIS 4

int main(void)
{
	Quai* quai[NB_QUAIS];
	quai[0] = createQuai(0, 300.0, 12.0, MARCHANDISE, 2); 
    quai[1] = createQuai(1, 400.0, 15.0, PETROLIER, 2);   
    quai[2] = createQuai(2, 200.0, 10.0, PASSAGER, 3);    
    quai[3] = createQuai(3, 100.0, 8.0, YACHT, 4);
	srand(time(NULL));
	while(1)
	{
		// fonction créant les navires via Matt
		// pour le code ->
		Navire* navire = malloc(sizeof(Navire));
        if (navire == NULL)
        {
            printf("Erreur d'allocation mémoire pour le navire !\n");
            continue;
        }

        
        navire->identifiant = rand() % 1000 + 1;

        
        navire->type = rand() % TYPE_NAVIRE;

        
        navire->capacite_chargement = (rand() % 451) + 50; 

        navire->etat = EN_MER;
        navire->suiv = NULL;

        int numero = -1;
        switch(navire->type)
        {
        	case MARCHANDISE: 
        		numero = 1; 
        		break;
            case PETROLIER: 
            	numero = 2;
            	break;
            case PASSAGER: 
            	numero = 3; 
            	break;
            case YACHT: 
            	numero = 4; 
            	break;
            default: 
            	break;
        }
        if(numero != -1)
        {
        	accosterNavireQuai(quai[numero - 1], navire);
        }
        else
        {
        	free(navire);
        }

        for (int i = 0; i < NB_QUAIS; i++) 
        {
            afficherQuai(quai[i]);
        }
        sleep(5);
	}
}