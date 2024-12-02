#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef enum
{
    ALEATOIRE,
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

typedef struct liste_bateau liste_bateau;
struct liste_bateau
{
    Navire *premier;
    Navire *dernier;
};

typedef struct id_dispo id_dispo;
struct id_dispo
{
    int id_passager;
    int id_marchandise;
    int id_petrolier;
    int id_yacht;
};

liste_bateau *Liste_bateau;
Mouillage *mouillage;
id_dispo *Id_Dispo;

void initialise_listes();
int nb_mouillage();
Navire *ajoute_liste_bateau(Navire *bateau);
Navire *newBoat(TYPE_NAVIRE type, int capacite);
Navire *recherche_navire(int id);
void afficher_mouillage(Mouillage *Liste);
void afficher_liste_bateau(liste_bateau *Liste);

int main(void)
{
    initialise_listes();
    for (int i = 0; i < 10; i++)
    {
        newBoat(ALEATOIRE, 0);
    }

    afficher_liste_bateau(Liste_bateau);
    afficher_mouillage(mouillage);

    return 0;
}

void initialise_listes()
{
    Liste_bateau = malloc(sizeof(liste_bateau));
    Liste_bateau->premier = NULL;
    Liste_bateau->dernier = NULL;

    mouillage = malloc(sizeof(Mouillage));
    mouillage->capacité = 5;
    mouillage->premier = NULL;

    Id_Dispo = malloc(sizeof(id_dispo));
    Id_Dispo->id_passager = 10000;
    Id_Dispo->id_marchandise = 20000;
    Id_Dispo->id_petrolier = 30000;
    Id_Dispo->id_yacht = 40000;
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
    tmp->mouillage_suiv = bateau;
}

Navire *ajoute_liste_bateau(Navire *bateau){
    if (Liste_bateau->premier == NULL)
        {
            Liste_bateau->premier = bateau;
            Liste_bateau->dernier = bateau;
            bateau->precedent = NULL;
        }
        else
        {
            bateau->precedent = Liste_bateau->dernier;
            bateau->precedent->suivant = bateau;
            Liste_bateau->dernier = bateau;
        }
    return bateau;
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
            new->identifiant = Id_Dispo->id_passager + 1;
            Id_Dispo->id_passager++;

            ajoute_liste_bateau(new);

            ajoute_mouillage(new);

            return new;

            break;

        case MARCHANDISE:
            new->type = MARCHANDISE;
            new->identifiant = Id_Dispo->id_marchandise + 1;
            Id_Dispo->id_marchandise++;

            ajoute_liste_bateau(new);

            ajoute_mouillage(new);

            return new;

            break;

        case PETROLIER:
            new->type = PETROLIER;
            new->identifiant = Id_Dispo->id_petrolier + 1;
            Id_Dispo->id_petrolier++;

            ajoute_liste_bateau(new);

            ajoute_mouillage(new);

            return new;

            break;

        case YACHT:
            new->type = YACHT;
            new->identifiant = Id_Dispo->id_yacht + 1;
            Id_Dispo->id_yacht++;

            ajoute_liste_bateau(new);

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
    Navire *tmp = Liste_bateau->premier;
    while (tmp != NULL && tmp->identifiant != id)
    {
        tmp = tmp->suivant;
    }
    return tmp;
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

void afficher_liste_bateau(liste_bateau *Liste)
{
    Navire *tmp = Liste_bateau->premier;
    printf("liste bateau\n");
    while (tmp != NULL)
    {
        printf("type: %u\nidentifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->type, tmp->identifiant, tmp->etat, tmp->capacite_chargement);
        tmp = tmp->suivant;
    }
    printf("\n\n\n");
}

void enleve_mouillage(int id)
{
    Navire *tmp = mouillage->premier;
    Navire *ptmp = tmp;
    while (tmp != NULL && tmp->identifiant != id)
    {
        ptmp = tmp;
        tmp = tmp->mouillage_suiv;
    }

    if (tmp == NULL)
    {
        return;
    }

    if (tmp == mouillage->premier)
    {
        mouillage->premier = tmp->mouillage_suiv;
        return;
    }

    ptmp->mouillage_suiv = tmp->mouillage_suiv;
}