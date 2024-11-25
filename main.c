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
    Navire *mouillage_suiv;
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
    Navire *premier;
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
Mouillage *mouillage;

void initialise_listes();
int nb_mouillage();
Navire *newBoat(TYPE_NAVIRE type, int capacite);
Navire *recherche_navire(int id);
void afficher_mouillage(Mouillage *Liste);
void afficher_liste_passager(liste_passager *Liste);
void afficher_liste_marchandise(liste_marchandise *Liste);
void afficher_liste_petrolier(liste_petrolier *Liste);
void afficher_liste_yacht(liste_yacht *Liste);

int main(void)
{
    initialise_listes();
    for (int i = 0; i < 10; i++)
    {
        newBoat(ALEATOIRE, 0);
    }

    afficher_liste_passager(Liste_passager);
    afficher_liste_marchandise(Liste_marchandise);
    afficher_liste_petrolier(Liste_petrolier);
    afficher_liste_yacht(Liste_yacht);
    afficher_mouillage(mouillage);

    return 0;
}

void initialise_listes()
{
    Liste_passager = malloc(sizeof(liste_passager));
    Liste_passager->premier = NULL;
    Liste_passager->dernier = NULL;

    Liste_marchandise = malloc(sizeof(liste_marchandise));
    Liste_marchandise->premier = NULL;
    Liste_marchandise->dernier = NULL;

    Liste_petrolier = malloc(sizeof(liste_petrolier));
    Liste_petrolier->premier = NULL;
    Liste_petrolier->dernier = NULL;

    Liste_yacht = malloc(sizeof(liste_yacht));
    Liste_yacht->premier = NULL;
    Liste_yacht->dernier = NULL;

    mouillage = malloc(sizeof(Mouillage));
    mouillage->capacité = 5;
    mouillage->premier = NULL;
}

int nb_mouillage()
{
    int nb = 0;
    Navire *tmp = mouillage->premier;
    while (tmp != NULL)
    {
        nb++;
        tmp = tmp->mouillage_suiv;
    }

    return nb;
}

void ajoute_mouillage(Navire *bateau)
{
    if (mouillage->premier == NULL)
    {
        mouillage->premier = bateau;
        return;
    }
    Navire *tmp = mouillage->premier;
    while (tmp->mouillage_suiv != NULL)
    {
        tmp = tmp->mouillage_suiv;
    }
    tmp->mouillage_suiv=bateau;
}

Navire *newBoat(TYPE_NAVIRE type, int capacite)
{
    Navire *new = malloc(sizeof(Navire));
    if (nb_mouillage() < mouillage->capacité)
    {
        printf("\n\n nb mouillage: %d\n\n", nb_mouillage());
        new->capacite_chargement = capacite;
        new->etat = EN_ATTENTE;
        new->suivant = NULL;
        new->mouillage_suiv = NULL;
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

                ajoute_mouillage(new);

                return new;
            }

            new->identifiant = Liste_passager->dernier->identifiant + 1;
            new->precedent = Liste_passager->dernier;
            new->precedent->suivant = new;
            Liste_passager->dernier = new;

            ajoute_mouillage(new);

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

                ajoute_mouillage(new);
                return new;
            }

            new->identifiant = Liste_marchandise->dernier->identifiant + 1;
            new->precedent = Liste_marchandise->dernier;
            new->precedent->suivant = new;
            Liste_marchandise->dernier = new;

            ajoute_mouillage(new);

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

                ajoute_mouillage(new);
                return new;
            }

            new->identifiant = Liste_petrolier->dernier->identifiant + 1;
            new->precedent = Liste_petrolier->dernier;
            new->precedent->suivant = new;
            Liste_petrolier->dernier = new;

            ajoute_mouillage(new);

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

                ajoute_mouillage(new);
                return new;
            }

            new->identifiant = Liste_yacht->dernier->identifiant + 1;
            new->precedent = Liste_yacht->dernier;
            new->precedent->suivant = new;
            Liste_yacht->dernier = new;

            ajoute_mouillage(new);

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
    return new;
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

void afficher_mouillage(Mouillage *Liste)
{
    Navire *tmp = mouillage->premier;
    printf("attente mouillage\n");
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->mouillage_suiv;
    }
    printf("\n\n\n");
}

void afficher_liste_passager(liste_passager *Liste)
{
    Navire *tmp = Liste_passager->premier;
    printf("liste passsager\n");
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
    printf("\n\n\n");
}

void afficher_liste_marchandise(liste_marchandise *Liste)
{
    Navire *tmp = Liste_marchandise->premier;
    printf("liste marchandise\n");
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
    printf("\n\n\n");
}

void afficher_liste_petrolier(liste_petrolier *Liste)
{
    Navire *tmp = Liste_petrolier->premier;
    printf("liste petrolier\n");
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
    printf("\n\n\n");
}

void afficher_liste_yacht(liste_yacht *Liste)
{
    Navire *tmp = Liste_yacht->premier;
    printf("liste yacht\n");
    while (tmp != NULL)
    {
        printf("identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
    printf("\n\n\n");
}