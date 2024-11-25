#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

typedef struct Navire Navire;
struct Navire
{
    int identifiant;
    TYPE_NAVIRE type;
    ETAT_NAVIRE etat;
    float capacite_chargement;
    Navire *precedent;
    Navire *suivant;
};

typedef struct Quai
{
    int numero;
    float taille;
    float profondeur;
    TYPE_NAVIRE type_autorise;
    int capacite_max;
} Quai;

typedef struct Mouillage
{
    int capacité;
    Navire *attente;
} Mouillage;

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

void initialise_listes();
Navire *newBoat(TYPE_NAVIRE type, int capacite);
Navire *recherche_navire(int id);

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
    Navire *new = malloc(sizeof(Navire));
    new->capacite_chargement = capacite;
    new->etat = EN_ATTENTE;
    new->suivant = NULL;
    int n = 0;
    switch (type)
    {
    case PASSAGER:
        new->type = PASSAGER;
        if (Liste_passager->premier == NULL)
        {
            new->identifiant = 10000;
            Liste_passager->premier = new;
            Liste_passager->dernier = new;
            new->precedent = NULL;
            return new;
        }

        new->identifiant = Liste_passager->dernier->identifiant + 1;
        new->precedent = Liste_passager->dernier;

        return new;

        break;

    case MARCHANDISE:
        new->type = MARCHANDISE;
        if (Liste_marchandise->premier == NULL)
        {
            new->identifiant = 20000;
            Liste_marchandise->premier = new;
            Liste_marchandise->dernier = new;
            new->precedent = NULL;
            return new;
        }

        new->identifiant = Liste_marchandise->dernier->identifiant + 1;
        new->precedent = Liste_marchandise->dernier;

        return new;

        break;

    case PETROLIER:
        new->type = PETROLIER;
        if (Liste_petrolier->premier == NULL)
        {
            new->identifiant = 30000;
            Liste_petrolier->premier = new;
            Liste_petrolier->dernier = new;
            new->precedent = NULL;
            return new;
        }

        new->identifiant = Liste_petrolier->dernier->identifiant + 1;
        new->precedent = Liste_petrolier->dernier;

        return new;

        break;

    case YACHT:
        new->type = YACHT;
        if (Liste_yacht->premier == NULL)
        {
            new->identifiant = 40000;
            Liste_yacht->premier = new;
            Liste_yacht->dernier = new;
            new->precedent = NULL;
            return new;
        }

        new->identifiant = Liste_yacht->dernier->identifiant + 1;
        new->precedent = Liste_yacht->dernier;

        return new;

        break;

    case ALEATOIRE:
        n = rand() % 4 + 1;
        switch (n)
        {
        case 1:
            newBoat(PASSAGER, rand() % 8 + 4);

            break;

        case 2:
            newBoat(MARCHANDISE, rand() % 100000 + 10000);

            break;

        case 3:
            newBoat(PETROLIER, rand() % 200000 + 80000);

            break;

        case 4:
            newBoat(YACHT, rand() % 3 + 0.5);

            break;

        default:
            break;
        }

    default:
        return new;
        break;
    }
}

Navire *recherche_navire(int id)
{
    int l = log10(id);
    int pre = id / pow(10, l);
    Navire *tmp = malloc(sizeof(Navire));
    switch (pre)
    {
    case 1:
        tmp = Liste_passager->premier;
        while (tmp->identifiant != id && tmp != NULL)
        {
            tmp = tmp->suivant;
        }
        return tmp;
        break;

    case 2:
        tmp = Liste_marchandise->premier;
        while (tmp->identifiant != id && tmp != NULL)
        {
            tmp = tmp->suivant;
        }
        return tmp;
        break;

    case 3:
        tmp = Liste_petrolier->premier;
        while (tmp->identifiant != id && tmp != NULL)
        {
            tmp = tmp->suivant;
        }
        return tmp;
        break;

    case 4:
        tmp = Liste_yacht->premier;
        while (tmp->identifiant != id && tmp != NULL)
        {
            tmp = tmp->suivant;
        }
        return tmp;
        break;

    default:
        return tmp;
        break;
    }
}

void afficher_liste_passager(liste_passager Liste)
{
    Navire *tmp = Liste_passager->premier;
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %f", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
}