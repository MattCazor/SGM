#ifndef QUAI_H
#define QUAI_H 

typedef enum 
{
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
    Navire* suiv;     
};

typedef struct Quai Quai;
struct Quai
{
    int numero;
    float taille;              
    float profondeur;            
    TYPE_NAVIRE type_autorise;   
    int capacite_max; 
    Navire* attente;        
};
 
char* typenavire(TYPE_NAVIRE type); 
char* etatnavire(ETAT_NAVIRE etat);
Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max);
void afficherQuai(Quai* quai);
int quitterQuai(Quai* quai, int identifiant);
int attenteAccoster(Quai* quai, Navire* navire);
void afficheAttente(Quai* quai);
Navire* createNavire(int id, TYPE_NAVIRE type, float capacite);

#endif