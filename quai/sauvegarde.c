#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sauvegarde.h"
#include "structures.h"

// int main(void) {
//     Mouillage zoneMouillage = {0, NULL};
//     Navire *naviresEnMer = NULL;
//     Quai *listeQuais = NULL;

//     chargePort(&listeQuais, &zoneMouillage, &naviresEnMer, "port.txt");

//     while (1) {
//         savePort(listeQuais, &zoneMouillage, naviresEnMer, "port.txt");
//         sleep(3);
//     }

//     return 0;
// }

const char *typeNavireEnChaine(TYPE_NAVIRE type) {
    switch (type) {
        case PASSAGER: return "PASSAGER";
        case MARCHANDISE: return "MARCHANDISE";
        case PETROLIER: return "PETROLIER";
        case YACHT: return "YACHT";
        default: return "INCONNU";
    }
}

const char *etatNavireEnChaine(ETAT_NAVIRE etat) {
    switch (etat) {
        case EN_MER: return "EN_MER";
        case ACCOSTE: return "ACCOSTE";
        case EN_ATTENTE: return "EN_ATTENTE";
        default: return "INCONNU";
    }
}

const char *typeNavireAutoriseEnChaine(TYPE_NAVIRE type_autorise) {
    switch (type_autorise) {
        case PASSAGER: return "PASSAGER";
        case MARCHANDISE: return "MARCHANDISE";
        case PETROLIER: return "PETROLIER";
        case YACHT: return "YACHT";
        default: return "INCONNU";
    }
}

int savePort(Quai *listeQuais, Mouillage *zoneMouillage, Navire *naviresEnMer, char *port) {
    FILE *fichier = fopen(port, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    if (listeQuais == NULL && zoneMouillage == NULL && naviresEnMer == NULL) {
        printf("Il n'y a aucun navire.\n");
        fclose(fichier);
        return 1;
    }

    fprintf(fichier, "----BATEAUX ACCOSTES----\n");
    Quai *quai = listeQuais;
    while (quai != NULL) {
        fprintf(fichier, "Quai N°%d, Taille:%.2f, Profondeur:%.2f, Type autorisé 1:%s, Type autorisé 2:%s, Capacité maximale:%d\n", quai->numero, quai->taille, quai->profondeur, typeNavireAutoriseEnChaine(quai->type_autorise1),typeNavireAutoriseEnChaine(quai->type_autorise1), quai->capacite_max);
        Navire *navire = quai->attente;
        while (navire != NULL) {
            fprintf(fichier, "° Bateau ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", navire->identifiant, typeNavireEnChaine(navire->type), etatNavireEnChaine(navire->etat), navire->capacite_chargement);
            navire = navire->quai_suiv;
        }
        fprintf(fichier, "\n");
        quai = quai->suivant;
    }

    fprintf(fichier, "----BATEAUX EN ZONE DE MOUILLAGE----\n");

    int cpt = 0;
    Navire *tmp = zoneMouillage->premier;
    while (tmp) {
        cpt++;
        tmp = tmp->mouillage_suiv;
    }

    if (cpt > zoneMouillage->capacité) {
        fprintf(fichier, "Il y a trop de navires dans la zone de mouillage.\n");
    }

    Navire *mouillageNavire = zoneMouillage->premier;
    while (mouillageNavire != NULL) {
        fprintf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", mouillageNavire->identifiant, typeNavireEnChaine(mouillageNavire->type), etatNavireEnChaine(mouillageNavire->etat), mouillageNavire->capacite_chargement);
        mouillageNavire = mouillageNavire->mouillage_suiv;
    }

    fprintf(fichier, "----BATEAUX EN MER----\n");
    Navire *enMerNavire = naviresEnMer;
    while (enMerNavire != NULL) {
        fprintf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", enMerNavire->identifiant, typeNavireEnChaine(enMerNavire->type), etatNavireEnChaine(enMerNavire->etat), enMerNavire->capacite_chargement);
        enMerNavire = enMerNavire->en_mer_suiv;
    }

    fclose(fichier);
    return 1;
}

int chargePort(Quai **listeQuais, Mouillage *zoneMouillage, Navire **naviresEnMer, const char *port) {
    FILE *fichier = fopen(port, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    printf("----BATEAUX ACCOSTES----\n");

    Quai *quai = *listeQuais;

    while (quai != NULL) {
        char typeNavire1[50]; 
        char typeNavire2[50]; 
        fscanf(fichier, "Quai N°%d, Taille:%f, Profondeur:%f, Type autorisé 1:%s, Type autorisé 2:%s, Capacité maximale:%d\n", 
                &quai->numero, &quai->taille, &quai->profondeur, typeNavire1, typeNavire2, &quai->capacite_max);
        printf("Quai N°%d, Taille:%.2f, Profondeur:%.2f, Type autorisé 1:%s, Type autorisé 2:%s, Capacité maximale:%d\n", 
                quai->numero, quai->taille, quai->profondeur, typeNavire1, typeNavire2, quai->capacite_max);
        Navire *navire = quai->navire;
        
        while (navire != NULL) {
            char typeNavire[50];
            char etatNavire[50]; 
            fscanf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %f\n", 
                    &navire->identifiant, typeNavire, etatNavire, &navire->capacite_chargement);
            printf("° Bateau ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", 
                    navire->identifiant, typeNavire, etatNavire, navire->capacite_chargement);
            navire = navire->suivant;
        }
        printf("\n");
        quai = quai->suivant;
    }

    printf("----BATEAUX EN ZONE DE MOUILLAGE----\n");

    int cpt = 0;
    Navire *tmp = zoneMouillage->premier;
    while (tmp) {
        cpt++;
        tmp = tmp->suivant;
    }

    if (cpt > zoneMouillage->capacité) {
        printf("Il y a trop de navires dans la zone de mouillage.\n");
    }

    Navire *mouillageNavire = zoneMouillage->premier;

    while (mouillageNavire != NULL){
        char typeNavire[50];  
        char etatNavire[50];  
        fscanf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %f\n", 
                &mouillageNavire->identifiant, typeNavire, etatNavire, &mouillageNavire->capacite_chargement);
        printf("° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", 
                mouillageNavire->identifiant, typeNavire, etatNavire, mouillageNavire->capacite_chargement);
        mouillageNavire = mouillageNavire->suivant;
    }

    printf("----BATEAUX EN MER----\n");

    Navire *enMerNavire = *naviresEnMer;

    while (enMerNavire != NULL){
        char typeNavire[50];
        char etatNavire[50]; 
        fscanf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %f\n", 
                &enMerNavire->identifiant, typeNavire, etatNavire, &enMerNavire->capacite_chargement);
        printf("° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", 
                enMerNavire->identifiant, typeNavire, etatNavire, enMerNavire->capacite_chargement);
        enMerNavire = enMerNavire->suivant;
    }

    fclose(fichier);
    return 1;
}
