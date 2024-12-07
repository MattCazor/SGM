#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sauvegarde.h"
#include "structures.h"

int main(void){

Mouillage zoneMouillage = {0, NULL};
Navire *naviresEnMer = NULL;
Quai *listeQuais = NULL;

    while (1) {

        if (savePort(listeQuais, &zoneMouillage, naviresEnMer, "port.txt")) {
            printf("Les données ont été sauvegardées.\n");
        } else {
             printf("Erreur lors de la sauvegarde des données.\n");
        }
        sleep(3);
    }

    return 0;
}

const char *typeNavireEnChaine(TYPE_NAVIRE type){
    switch (type) {
        case PASSAGER: return "PASSAGER";
        case MARCHANDISE: return "MARCHANDISE";
        case PETROLIER: return "PETROLIER";
        case YACHT: return "YACHT";
        default: return "INCONNU";
    }
}

const char *etatNavireEnChaine(ETAT_NAVIRE etat){
    switch (etat) {
        case EN_MER: return "EN_MER";
        case ACCOSTE: return "ACCOSTE";
        case EN_ATTENTE: return "EN_ATTENTE";
        default: return "INCONNU";
    }
}

const char *typeNavireAutoriseEnChaine(TYPE_NAVIRE type_autorise){
    switch (type_autorise) {
        case PASSAGER: return "PASSAGER";
        case MARCHANDISE: return "MARCHANDISE";
        case PETROLIER: return "PETROLIER";
        case YACHT: return "YACHT";
        default: return "INCONNU";
    }
}



int savePort(Quai *listeQuais, Mouillage *zoneMouillage, Navire *naviresEnMer, char *port){

    FILE *fichier = fopen("port.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    if(listeQuais==NULL && zoneMouillage==NULL && naviresEnMer==NULL){
        printf("Il n'y a aucun navire.\n");
        fclose(fichier);
        return 1;
    }

    fprintf(fichier, "----BATEAUX ACCOSTES----\n");
    Quai *quai = listeQuais;
    while (quai != NULL) {
        fprintf(fichier,"Quais N°%d, Taille:%.2f, Profondeur:%.2f, Type autorisé:%s, Capacité maximale:%d\n",quai->numero,quai->taille, quai->profondeur,typeNavireAutoriseEnChaine(quai->type_autorise),quai->capacite_max);
        Navire *navire = quai->navire;
        while (navire != NULL) {
            fprintf(fichier, "° Bateaux ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n",navire->identifiant, typeNavireEnChaine(navire->type), etatNavireEnChaine(navire->etat), navire->capacite_chargement);
            navire = navire->suivant;
        }
        fprintf(fichier, "\n");
        quai = quai->suivant;
    }

    
    fprintf(fichier, "----BATEAUX EN ZONE DE MOUILLAGE----\n");

    int cpt=0;
    Navire *tmp = zoneMouillage->premier;

        while (tmp) {
            cpt++;
            tmp = tmp->suivant;
        }
    
        if (cpt > zoneMouillage->capacité) {
            fprintf(fichier, "Il y a trop de navires dans la zone de mouillage.\n");
        }       
  
    Navire *mouillageNavire = zoneMouillage->premier;
    while (mouillageNavire != NULL) {
        fprintf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n", mouillageNavire->identifiant, typeNavireEnChaine(mouillageNavire->type),etatNavireEnChaine(mouillageNavire->etat), mouillageNavire->capacite_chargement);

        mouillageNavire = mouillageNavire->suivant;
    }

    fprintf(fichier, "----BATEAUX EN MER----\n");
    Navire *enMerNavire = naviresEnMer;
    while (enMerNavire != NULL) {
        fprintf(fichier, "° ID : %d, Type : %s, Etat : %s, Capacité de chargement : %.2f\n",enMerNavire->identifiant, typeNavireEnChaine(enMerNavire->type),etatNavireEnChaine(enMerNavire->etat), enMerNavire->capacite_chargement);
        enMerNavire = enMerNavire->suivant;
    }

    fclose(fichier);
    return 1;
}
