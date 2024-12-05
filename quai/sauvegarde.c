#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sauvegarde.h"


const char *typeNavireEnChaine(TYPE_NAVIRE type)
{
    switch (type)
    {
    case PASSAGER:
        return "PASSAGER";
    case MARCHANDISE:
        return "MARCHANDISE";
    case PETROLIER:
        return "PETROLIER";
    case YACHT:
        return "YACHT";
    default:
        return "INCONNU";
    }
}

const char *etatNavireEnChaine(ETAT_NAVIRE etat)
{
    switch (etat)
    {
    case EN_MER:
        return "EN_MER";
    case ACCOSTE:
        return "ACCOSTE";
    case EN_ATTENTE:
        return "EN_ATTENTE";
    default:
        return "INCONNU";
    }
}

const char *typeNavireAutoriseEnChaine(TYPE_NAVIRE type_autorise)
{
    switch (type_autorise)
    {
    case PASSAGER:
        return "PASSAGER";
    case MARCHANDISE:
        return "MARCHANDISE";
    case PETROLIER:
        return "PETROLIER";
    case YACHT:
        return "YACHT";
    default:
        return "INCONNU";
    }
}

int saveNavire(Navire *liste, char *navire)
{

    FILE *fichier = NULL;
    fichier = fopen("navire.txt", "w");

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir ce fichier\n");

        return 0;
    }

    Navire *tmp = liste;

    while (tmp != NULL)
    {
        fprintf(fichier, "id:%d, type:%s, état:%s, capacité de chargement:%.2f\n", tmp->identifiant, typeNavireEnChaine(tmp->type), etatNavireEnChaine(tmp->etat));
        tmp = tmp->suivant;
    }
    fclose(fichier);
    return 1;
}

int saveQuais(Quai *liste, char *quai)
{

    FILE *fichier = NULL;
    fichier = fopen("quais.txt", "w");

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir ce fichier\n");

        return 0;
    }

    Quai *tmp = liste;

    while (tmp != NULL)
    {
        fprintf(fichier, "numero:%d, taille:%.2f, profondeur:%.2f, type autorisé:%s, capacité maximale:%d\n", tmp->numero, tmp->taille, tmp->profondeur, typeNavireAutoriseEnChaine(tmp->type_autorise), tmp->capacite_max);
        tmp = tmp->suivant;
    }
    fclose(fichier);
    return 1;
}
