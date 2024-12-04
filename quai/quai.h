#ifndef QUAI_H
#define QUAI_H 

#include "structures.h"

 
char* typenavire(TYPE_NAVIRE type); 
char* etatnavire(ETAT_NAVIRE etat);
Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise, int capacite_max);
int accosterNavireQuai(Quai* quai, Navire* navire);
void afficherQuai(Quai* quai);
int quitterQuai(Quai* quai, int identifiant);
int attenteAccoster(Quai* quai, Navire* navire);
void afficheAttente(Quai* quai);
// Navire* createNavire(int id, TYPE_NAVIRE type, float capacite);

#endif