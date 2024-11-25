#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    PASSAGER,
    MARCHANDISE,
    PETROLIER,
    YACHT,
    ALEATOIRE
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
    Navire *precedent;
    Navire *suivant;
} Navire;

typedef struct Quai
{
    int numero;
    float taille;
    float profondeur;
    TYPE_NAVIRE type_autorise;
    int capacite_max;
} Quai;

typedef struct liste_passager liste_passager;
struct liste_passager
{
    Navire *premier;
    Navire *dernier;
};

typedef struct liste_petrolier
{
    Navire *premier;
    Navire *dernier;
} liste_petrolier;

typedef struct liste_yacht
{
    Navire *premier;
    Navire *dernier;
} liste_yacht;

typedef struct liste_marchandise
{
    Navire *premier;
    Navire *dernier;
} liste_marchandise;

liste_passager *Liste_passager;
liste_marchandise *Liste_marchandise;
liste_petrolier *Liste_petrolier;
liste_yacht *Liste_yacht;

int main(void)
{
    return 0;
}

void initialise_listes()
{
    Liste_passager->premier = NULL;
    Liste_passager->dernier = NULL;

    Liste_marchandise->premier = NULL;
    Liste_marchandise->dernier = NULL;

    Liste_petrolier->premier = NULL;
    Liste_petrolier->dernier = NULL;

    Liste_yacht->premier = NULL;
    Liste_yacht->dernier = NULL;
}

Navire *newBoat(TYPE_NAVIRE type, int capacite)
{
    Navire *new;
    switch (type)
    {
    case PASSAGER:
        new->capacite_chargement = capacite;
        new->etat = EN_ATTENTE;
        new->type = PASSAGER;
        if (Liste_passager->premier == NULL)
        {
            new->identifiant = 10000;
            Liste_passager->premier = new;
            Liste_passager->dernier = new;
            new->precedent=NULL;
            new->suivant=NULL;
        }
        new->identifiant = Liste_passager->dernier->identifiant + 1;

        return new;

        break;

    default:
        break;
    }
}
