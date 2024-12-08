#ifndef QUAI_H
#define QUAI_H 

#include "structures.h"

char* typenavire(TYPE_NAVIRE type); 
char* etatnavire(ETAT_NAVIRE etat);
int TempsAttente(TYPE_NAVIRE type_navire);
Quai* createQuai(int numero, float taille, float profondeur, TYPE_NAVIRE type_autorise1, TYPE_NAVIRE type_autorise2, int capacite_max);
int accosterNavireQuai(Quai* quai, Navire* navire);
void afficherQuai(Quai* quai);
void quitterQuai(Quai* quai);
int attenteAccoster(Quai* quai, Navire* navire);
void afficheAttente(Quai* quai);
// Navire* createNavire(int id, TYPE_NAVIRE type, float capacite);

#endif