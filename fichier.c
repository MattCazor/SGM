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

const char *typeNavireEnChaine(TYPE_NAVIRE type);
int saveNavire(Navire *liste,char*navire);
const char *etatNavireToString(ETAT_NAVIRE etat);

int main(void){

Navire *liste=NULL;

if (saveNavire(liste, "navires.txt")) {
        printf("Les données des navires ont été sauvegardées avec succès.\n");
    } else {
        printf("Erreur lors de la sauvegarde des données.\n");
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

int saveNavire(Navire *liste,char*navire){
    
    FILE*fichier=NULL;
    fichier=fopen("navire.txt","w");

    if(fichier==NULL){
        printf("Impossible d'ouvrir ce fichier\n");

        return 0;
    }

    Navire*tmp=liste;

    while(tmp!=NULL){
        fprintf(fichier,"id:%d, type:%s, état:%s, capacité de chargement:%.2f\n",tmp->identifiant,typeNavireEnChaine(tmp->type),etatNavireEnChaine(tmp->etat));
        tmp=tmp->suivant;
    }
    fclose(fichier);
    return 1; 

}

