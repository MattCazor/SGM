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

typedef struct liste_passager{
    passager *premier;
    passager *dernier;
};

typedef struct liste_petrolier{
    petrolier *premier;
    petrolier *dernier;
};

typedef struct liste_yacht{
    yacht *premier;
    yacht *dernier;
};

typedef struct liste_marchandise{
    marchandise *premier;
    marchandise *dernier;
};


int main(void){
    return 0;
}

Navire newBoat(TYPE_NAVIRE type, int capacite){
    Navire new;
    switch (type)
    {
    case PASSAGER:
        new.capacite_chargement=capacite;
        new.etat=EN_ATTENTE;
        new.type=PASSAGER;
        new.identifiant=
        
        break;
    
    default:
        break;
    }
}

