#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_QUAIS 4

typedef enum 
{
    PASSAGER,
    MARCHANDISE,
    PETROLIER,
    YACHT
} TYPE_NAVIRE;

typedef enum 
{
    EN_MER,
    ACCOSTE,
    EN_ATTENTE
} ETAT_NAVIRE;

typedef struct Navire Navire;
struct Navire
{
    int identifiant;            
    TYPE_NAVIRE type;           
    ETAT_NAVIRE etat;           
    float capacite_chargement;  
    Navire* suiv;     
};

typedef struct Quai Quai;
struct Quai
{
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max; 
    Navire* attente;        
};

Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max);
void afficherQuai(Quai* quai);

Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max) 
{
    Quai* quai = malloc(sizeof(Quai));
    quai->numero = numero;
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
		temp=temp->suiv;
	}
	if(c >= quai->capacite_max)
	{
		printf("Quai %d est plein. Impossible d'ajouter un navire\n", quai->numero);
        return 0;
	}
	navire->suiv = quai->attente;
	quai->attente = navire;
	printf("Navire %d ajouté au quai %d.\n", navire->identifiant, quai->numero);
    return 1;
}

void afficherQuai(Quai* quai)
{
	if(quai == NULL)
	{
		return;
	}
	printf("Quai %d\n (Type autorisé: %d\nCapacité max: %d):\n", quai->numero, quai->type_autorise, quai->capacite_max);
	Navire* temp = quai->attente;
	while(temp != NULL)
	{
		printf("Navire\n identifiant: %d\n, Type: %d\n, État: %d\n, Capacité: %.2f\n tonnes\n", temp->identifiant, temp->type, temp->etat, temp->capacite_chargement);
		temp = temp->suiv;
	}
	if(quai->attente == NULL)
	{
		printf("Aucun navire accosté.\n");
	}
}


int main(void)
{
	Quai* quai[NB_QUAIS];
	quai[1] = createQuai(1, 300.0, 12.0, MARCHANDISE, 2); 
    quai[2] = createQuai(2, 400.0, 15.0, PETROLIER, 2);   
    quai[3] = createQuai(3, 200.0, 10.0, PASSAGER, 3);    
    quai[4] = createQuai(4, 100.0, 8.0, YACHT, 4);
    int choix;
    do
    {
    	printf("\n=== Menu de Gestion des Quais et Navires ===\n");
	    printf("1. Ajouter un navire à un quai\n");
	    printf("2. Afficher les navires d'un quai\n");
	    printf("3. Quitter\n");
	    printf("Choisissez une option : \n");
	    scanf("%d", &choix);

	    Navire* navire = NULL;

	    switch(choix)
	    {
	    	case 1: {
                int identifiant;
                int numero;
                printf("Entrez l'ID du navire à ajouter (101 à 104 pour cet exemple) : ");
                scanf("%d", &identifiant);
                printf("Entrez l'ID du quai (1 à 4) : ");
                scanf("%d", &numero);

                if (numero < 1 || numero > 4) {
                    printf("Quai invalide.\n");
                    continue;
                }

                accosterNavireQuai(quai[numero - 1], navire);
                break;
            }
            case 2: {
                int numero;
                printf("Entrez l'ID du quai (1 à 4) : ");
                scanf("%d", &numero);

                if (numero < 1 || numero > 4) {
                    printf("Quai invalide.\n");
                    continue;
                }

                afficherQuai(quai[numero - 1]);
                break;
            }
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Réessayez.\n");
	    }
    }while (choix != 3);
    return 0;
}

//à faire
//navire qui quitte le quai
//ajouter navire en attente
//retirer navire en attente
//afficher navire en attente 