#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teubi
typedef enum {
    PASSAGER,
    MARCHANDISE,
    PETROLIER,
    YACHT
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
    struct Navire* suiv;     
} Navire;

typedef struct Quai {
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max;         
} Quai;
