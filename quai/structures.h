#ifndef STRUCTURES_H
#define STRUCTURES_H 


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
    int temps_restant;
    Navire *precedent;
    Navire *suivant;
    Navire *mouillage_suiv;
    Navire *quai_suiv;
};

typedef struct Quai Quai;
struct Quai
{
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max; 
    Navire *navire;
    Navire* attente;   
    Quai *suivant;  
    Quai *precedent;   
    struct Quai *suivant;
};

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

typedef struct liste_quai liste_quai;
struct liste_quai{
    Quai *premier;
    Quai *dernier;
};

// extern liste_bateau *Liste_bateau;  // Déclaration
// extern Mouillage *mouillage;          // Déclaration
// extern id_dispo *Id_Dispo;            // Déclaration
// extern liste_quai *Liste_quai;

liste_bateau *Liste_bateau;
Mouillage *mouillage;
id_dispo *Id_Dispo;
liste_quai *Liste_quai;
#endif