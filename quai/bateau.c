#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "bateau.h"
#include "quai.h"

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

    Liste_quai = malloc(sizeof(liste_quai));
    Liste_quai->premier = NULL;
    Liste_quai->dernier = NULL;
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

Navire *ajoute_liste_bateau(Navire *bateau)
{
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
        // printf("\n\n nb mouillage: %d\n\n", nb_mouillage());
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
        printf("type: %u\n identifiant: %d \n etat: %u\n capacite: %.f T\n\n", tmp->type, tmp->identifiant, tmp->etat, tmp->capacite_chargement);
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

void tri_mouillage(Navire *bateau, Quai *quai)
{
    // printf("dans trie mouillage\n");
    if (quai != NULL)
    {
        // printf("quai != NULL\n");
        Navire *tmp = bateau;
        // printf("tmp id %d\n", tmp->identifiant);
        while (tmp != NULL && tmp->type != quai->type_autorise && place_dans_quai(quai) < quai->capacite_max)
        {
            tmp = tmp->mouillage_suiv;
            // printf("type tmp %u, type quai %u\n", tmp->type, quai->type_autorise);
        }
        // printf("type tmp %u\n", tmp->type);
        // printf("type autorise quai %u\n", quai->type_autorise);
        if (tmp != NULL && tmp->type == quai->type_autorise && place_dans_quai(quai) < quai->capacite_max)
        {
            // printf("dans le if\n");
            if (accosterNavireQuai(quai, tmp) != 0)
            {
                enleve_mouillage(tmp->identifiant);
                // afficher_mouillage(mouillage);
                newBoat(ALEATOIRE, 0);
            }
            else
            {
                tri_mouillage(bateau, quai->suivant);
            }
            return;
        }
        else
        {
            // if (tmp == NULL)
            // {
            //     printf("tmp == NULL\n");
            //     return;
            // }
            // printf("dans le else\n");
            tri_mouillage(bateau, quai->suivant);
            // Quai *quai_dispo = test_emplacement_vide(Liste_quai);
            // if (quai_dispo != NULL && quai_dispo != quai)
            // {
            //     tri_mouillage(mouillage, quai_dispo);
            // }
        }
    }
    else
    {
        printf("quai NULL\n");
        if (bateau->mouillage_suiv != NULL)
        {
            tri_mouillage(bateau->mouillage_suiv, Liste_quai->premier);
        }
        return;
    }
}

Quai *test_emplacement_vide(liste_quai *Liste)
{
    // Vérification de la validité de la liste
    if (Liste == NULL || Liste->premier == NULL)
    {
        printf("Erreur : Liste des quais vide ou non initialisée.\n");
        return NULL;
    }

    // Parcourir la liste des quais
    Quai *tmp = Liste->premier;
    while (tmp != NULL)
    {
        // Compter le nombre de navires en attente sur ce quai
        Navire *nav = tmp->attente;
        int nbr = 0;

        while (nav != NULL)
        {
            nbr++;
            nav = nav->quai_suiv;
        }

        // Vérifier si la capacité maximale n'est pas atteinte
        if (nbr < tmp->capacite_max)
        {
            return tmp; // Retourner le quai avec de l'espace disponible
        }

        // Passer au quai suivant
        tmp = tmp->suivant;
    }

    // Aucun quai avec de l'espace trouvé
    return NULL;
}

int place_dans_quai(Quai *quai)
{
    int c = 0;
    Navire *temp = quai->attente;
    while (temp != NULL)
    {
        c = c + 1;
        temp = temp->quai_suiv;
    }

    return c;
}