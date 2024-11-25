#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef enum {
    PASSAGER,
    MARCHANDISE,
    PETROLIER,
    YACHT,
    ALEATOIRE
} TYPE_NAVIRE;

typedef enum {
    EN_MER,
    ACCOSTE,
    EN_ATTENTE
} ETAT_NAVIRE;

typedef struct Navire {
    int identifiant;            
    TYPE_NAVIRE type;           
    ETAT_NAVIRE etat;           
    float capacite_chargement;  
} Navire;

typedef struct Quai {
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max;         
} Quai;

typedef struct passager passager;
struct passager{
    passager *precedent;
    passager *suivant;
    Navire *bateau;
};

typedef struct petrolier petrolier;
struct petrolier{
    petrolier *precendent;
    petrolier *suivant;
    Navire *bateau;
};

typedef struct yacht yacht;
struct yacht{
    yacht *precendent;
    yacht *suivant;
    Navire *bateau;
};

typedef struct marchandise marchandise;
struct marchandise{
    marchandise *precendent;
    marchandise *suivant;
    Navire *bateau;
};

int main(void){
    return 0;
}

Navire newBoat(TYPE_NAVIRE type){
    Navire new;
    switch (type)
    {
    case PASSAGER:
        
        break;
    
    default:
        break;
    }
}

