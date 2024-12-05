#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quai.h"

#define NB_QUAIS 4

char* typenavire(TYPE_NAVIRE type) 
{
    switch (type) 
    {
        case PASSAGER: 
        	return "Passager";
        case MARCHANDISE: 
        	return "Marchandise";
        case PETROLIER: 
        	return "Pétrolier";
        case YACHT: 
        	return "Yacht";
        default: 
        	return "Inconnu";
    }
}

char* etatnavire(ETAT_NAVIRE etat) 
{
    switch (etat) 
    {
        case EN_MER: 
        	return "En mer";
        case ACCOSTE: 
        	return "Accosté";
        case EN_ATTENTE: 
        	return "En attente";
        default: 
        	return "Inconnu";
    }
}

int TempsAttente(TYPE_NAVIRE type)
{
    switch (type)
    {
        case PASSAGER:
            return 10; 
        case MARCHANDISE:
            return 15; 
        case PETROLIER:
            return 15; 
        case YACHT:
            return 5; 
        default:
            return 0; 
    }
}


Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max) 
{
    Quai* quai = malloc(sizeof(Quai));
    if (quai == NULL)
    {
    	printf("Erreur d'allocation !");
    	return NULL;
    }
    quai->numero = numero + 1;
    quai->taille = taille;
    quai->profondeur = profondeur;
    quai->type_autorise = type_autorise;
    quai->capacite_max = capacite_max;
    quai->attente = NULL; 
    return quai;
}

int accosterNavireQuai(Quai* quai, Navire* navire)
{
	if (quai == NULL || navire == NULL)
	{
		return 0;
	}
	if(navire->type != quai->type_autorise)
	{
		printf("Navire %d non autorisé sur le quai %d\n", navire->identifiant, quai->numero);
        return 0;
	}
	int c = 0;
	Navire* temp = quai->attente;
	while(temp != NULL)
	{
		c=c+1;
		temp=temp->suivant;
	}
	if(c >= quai->capacite_max)
	{
		printf("Quai %d est plein. Impossible d'ajouter un navire\n", quai->numero);
        return attenteAccoster(quai, navire);
	}
	navire->suivant = quai->attente;
	quai->attente = navire;
	navire->etat = ACCOSTE;
	navire->temps_restant = TempsAttente(navire->type);
	printf("Navire %d ajouté au quai %d.\n", navire->identifiant, quai->numero);
    return 1;
}

void afficherQuai(Quai* quai)
{
	if(quai == NULL)
	{
		return;
	}
	printf("Quai %d:\nType autorisé: %s\nCapacité max de navire: %d:\n", quai->numero, typenavire(quai->type_autorise), quai->capacite_max);
	Navire* temp = quai->attente;
	while(temp != NULL)
	{
		printf("Navire\nIdentifiant: %d,\n Type: %s,\n État: %s,\n Capacité: %.2f tonnes\n", temp->identifiant, typenavire(temp->type), etatnavire(temp->etat), temp->capacite_chargement);
		temp = temp->suivant;
	}
	if(quai->attente == NULL)
	{
		printf("Aucun navire accosté.\n");
	}
}

void quitterQuai(Quai* quai)
{
	if(quai == NULL || quai->attente == NULL)
	{
        return;
	}

	Navire* tmp = quai->attente;
	Navire* ptmp = NULL;
	while(tmp != NULL)
	{
<<<<<<< HEAD
		tmp->temps_restant--;

        if (tmp->temps_restant <= 0) // Navire doit partir
        {
            printf("Navire %d quitte le quai %d.\n", tmp->identifiant, quai->numero);
            if (ptmp == NULL)
            {
                quai->attente = tmp->suivant;
            }
            else
            {
                ptmp->suivant = tmp->suivant;
            }
            Navire* to_free = tmp;
            tmp = tmp->suivant;
            free(to_free);
        }
		// if(tmp->identifiant == identifiant)
		// {
		// 	if(ptmp != NULL)
		// 	{
		// 		ptmp->suiv=tmp->suiv;
		// 	}
		// 	else
		// 	{
		// 		quai->attente=tmp->suiv;
		// 	}
		// 	printf("Navire %d a quitté le quai %d.\n", identifiant, quai->numero);
  //           free(tmp); 
  //           return 1;
		// }
=======
		if(tmp->identifiant == identifiant)
		{
			if(ptmp != NULL)
			{
				ptmp->suivant=tmp->suivant;
			}
			else
			{
				quai->attente=tmp->suivant;
			}
			printf("Navire %d a quitté le quai %d.\n", identifiant, quai->numero);
            free(tmp); 
            return 1;
		}
>>>>>>> cf781ca6bbe3038ec4aa8bcc0a5288d677fa3a34
		ptmp=tmp;
		tmp=tmp->suivant;
	}
}

int attenteAccoster(Quai* quai, Navire* navire)
{
	if (quai == NULL || navire == NULL)
	{
		return 0;
	}
	if(quai->attente == NULL)
	{
		quai->attente = navire;
		navire->suivant = NULL;
	}
	else
	{
		Navire* temp = quai->attente;
		while(temp->suivant != NULL)
		{
			temp = temp->suivant;
		}
		temp->suivant = navire;
		navire->suivant = NULL;
	}
	printf("Navire %d ajouté en attente dans le quai %d.\n", navire->identifiant, quai->numero);
    return 1;
}

void afficheAttente(Quai* quai)
{
	if(quai != NULL || quai->attente == NULL)
	{
		printf("Aucun navire en attente dans le quai %d.\n", quai->numero);
        return;
	}
	printf("Navires en attente dans le quai %d :\n", quai->numero);
    Navire* temp = quai->attente;
    while (temp != NULL) 
    {
    	if(temp == NULL)
    	{
    		printf("Navire invalide dans la liste d'attente.\n");
            break;
    	}
        printf(" - Navire ID : %d, Type : %s, État : %s, Capacité : %.2f\n", temp->identifiant, typenavire(temp->type), etatnavire(temp->etat), temp->capacite_chargement);
        temp = temp->suivant;
    }
}


// faire un quai automatique 
















// Navire* createNavire(int id, TYPE_NAVIRE type, float capacite) 
// {
//     Navire* navire = malloc(sizeof(Navire));
//     if (navire == NULL) {
//         printf("Erreur d'allocation mémoire pour le navire !\n");
//         return NULL;
//     }

//     navire->identifiant = id;
//     navire->type = type;
//     navire->capacite_chargement = capacite;
//     navire->etat = EN_MER;
//     navire->suiv = NULL;

//     return navire;
// }


// int main(void)
// {
// 	Quai* quai[NB_QUAIS];
// 	quai[0] = createQuai(0, 300.0, 12.0, MARCHANDISE, 2); 
//     quai[1] = createQuai(1, 400.0, 15.0, PETROLIER, 2);   
//     quai[2] = createQuai(2, 200.0, 10.0, PASSAGER, 3);    
//     quai[3] = createQuai(3, 100.0, 8.0, YACHT, 4);
//     int choix;
//     do
//     {
//     	printf("\n=== Menu de Gestion des Quais ===\n");
// 	    printf("1. Ajouter un navire à un quai\n");
// 	    printf("2. Afficher les navires d'un quai\n");
// 	    printf("3. Faire quitter un navire d'un quai\n");
// 	    printf("4. Afficher les navires en attente\n");
// 	    printf("5. Quitter\n");
// 	    printf("===================================\n");
// 	    printf("Choisissez une option : \n");
// 	    scanf("%d", &choix);

// 	    Navire* navire = NULL;
// 	    int identifiant;
//         int numero;

// 	    switch(choix)
// 	    {
// 	    	case 1:
// 			    printf("Entrez l'ID du navire à ajouter : \n");
// 			    scanf("%d", &identifiant);

// 			    navire = malloc(sizeof(Navire));
// 			    if (navire == NULL) 
// 			    {
// 			        printf("Erreur d'allocation mémoire pour le navire !\n");
// 			        continue;
// 			    }
// 			    navire->identifiant = identifiant;
// 			    printf("Entrez le type du navire (1: Marchandise, 2: Pétrolier, 3: Passager, 4: Yacht) : \n");
// 			    int type;
// 			    scanf("%d", &type);
// 			    if (type < 1 || type > 4) 
// 			    {
// 			        printf("Type de navire invalide.\n");
// 			        free(navire);
// 			        continue;
// 			    }
// 			    navire->type = (TYPE_NAVIRE)type;
// 			    printf("Entrez la capacité de chargement du navire (en tonnes) : \n");
// 			    scanf("%f", &navire->capacite_chargement);
// 			    navire->etat = EN_MER;
// 			    navire->suiv = NULL;
// 			    printf("Entrez l'ID du quai :\n");
// 			    scanf("%d", &numero);

// 			    if (numero < 1 || numero > 4) 
// 			    {
// 			        printf("Quai invalide.\n");
// 			        free(navire);
// 			        continue;
// 			    }

// 			    accosterNavireQuai(quai[numero - 1], navire);
// 			    break;

//             case 2:
//                 printf("Entrez l'ID du quai :\n");
//                 scanf("%d", &numero);

//                 if (numero < 1 || numero > 4) {
//                     printf("Quai invalide.\n");
//                     continue;
//                 }

//                 afficherQuai(quai[numero - 1]);
//                 break;
            
//             case 3:
// 			    printf("Entrez l'ID du navire à retirer : \n");
// 			    scanf("%d", &identifiant);
// 			    printf("Entrez l'ID du quai : \n");
// 			    scanf("%d", &numero);

// 			    if (numero < 1 || numero > 4) {
// 			        printf("Quai invalide.\n");
// 			        continue;
// 			    }

// 			    quitterQuai(quai[numero - 1], identifiant);
// 			    break;

// 			case 4:
// 			    printf("Entrez l'ID du quai : \n");
// 			    scanf("%d", &numero);

// 			    if (numero < 1 || numero > 4) {
// 			        printf("Quai invalide.\n");
// 			        continue;
// 			    }

// 			    afficheAttente(quai[numero - 1]);
// 			    break;


//             case 5:
//                 printf("Au revoir !\n");
//                 break;
//             default:
//                 printf("Option invalide. Réessayez.\n");
// 	    }
//     }while (choix != 5);
//     return 0;
// }



//reste à faire


//retirer navire en attente
