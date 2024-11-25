#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Navire 
{
    int identifiant;            
    TYPE_NAVIRE type;           
    ETAT_NAVIRE etat;           
    float capacite_chargement;  
    Navire* suiv;     
} Navire;

typedef struct Quai 
{
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max; 
    Navire* attente;        
} Quai;

Quai* initialiserQuai(int numero, TYPE_NAVIRE type_autorise, int capacite_max);
int accosterNavire(Quai* quai, Navire* navire);
int quitter(Quai* quai, int identifiant);

Quai* initialiserQuai(int numero, TYPE_NAVIRE type_autorise, int capacite_max) 
{
    Quai* quai = (Quai*)malloc(sizeof(Quai));
    quai->numero = numero;
    quai->type_autorise = type_autorise;
    quai->capacite_max = capacite_max;
    quai->attente = NULL; 
    return quai;
}

int accosterNavire(Quai* quai, Navire* navire)
{
	if(navire->type != quai->type_autorise)
	{
		printf("Erreur le navire %d ne peut pas accoster au quai %d\n", navire->identifiant, quai->numero);
		return 0;
	}

	int c = 0;
	Navire* temp = quai->attente;
	while(temp != NULL)
	{
		c = c+1;
		temp = temp->suiv;
	}
	if(c >= quai->numero->suiv)
	{
		printf("Quai %d plein, le navire %d ne peut pas accoster\n", quai->numero, navire->identifiant);
		return 0;
	}
	navire->etat = ACCOSTE;
	navire->suiv=quai->attente;
	quai->attente=navire;
	printf("Le navire %d accosté au quai %d\n", navire->identifiant, quai->numero);
	return 1;
}

int quitter(Quai* quai, int identifiant)
{
	Navire* prev = NULL;
	Navire* temp = quai->attente;

	while(temp != NULL && temp->Navire.identifiant != identifiant)
	{
		prev = temp;
		temp = temp->suiv;
	}
	if(temp == NULL)
	{
		printf("Erreur\n");
		return 0;
	}
	if(prev == NULL)
	{
		quai->attente = temp->suiv;	
	}
	else
	{
		prev->suiv = tmp->suiv;
	}

	free(temp);
	printf("Le navire %d a quitté le quai %d\n", navire->identifiant, quai->numero);
	return 1;
}

int main(void)
{
	Quai* quaiPassager = initialiserQuai(1, PASSAGER, 3);  
    Quai* quaiMarchandise = initialiserQuai(2, MARCHANDISE, 2); 
    Quai* quaiPetrolier = initialiserQuai(3, PETROLIER, 2);
    Quai* quaiYacht = initialiserQuai(4, YACHT, 4);
    return 0;
}



