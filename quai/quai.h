#ifndef QUAI_H
#define QUAI_H 

#include "structures.h"

<<<<<<< HEAD
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
=======
>>>>>>> cf781ca6bbe3038ec4aa8bcc0a5288d677fa3a34
 
char* typenavire(TYPE_NAVIRE type); 
char* etatnavire(ETAT_NAVIRE etat);
int TempsAttente(TYPE_NAVIRE type_navire);
Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max);
int accosterNavireQuai(Quai* quai, Navire* navire);
void afficherQuai(Quai* quai);
void quitterQuai(Quai* quai);
int attenteAccoster(Quai* quai, Navire* navire);
void afficheAttente(Quai* quai);
// Navire* createNavire(int id, TYPE_NAVIRE type, float capacite);

#endif