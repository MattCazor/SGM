#ifndef BATEAU_H
#define BATEAU_H 

#include "structures.h"


void initialise_listes();
int nb_mouillage();
Navire *ajoute_liste_bateau(Navire *bateau);
Navire *newBoat(TYPE_NAVIRE type, int capacite);
Navire *recherche_navire(int id);
void afficher_mouillage(Mouillage *Liste);
void afficher_liste_bateau(liste_bateau *Liste);
void enleve_mouillage(int id);
void tri_mouillage(Navire *bateau, Quai *quai);
Quai* test_emplacement_vide(liste_quai *Liste);
int place_dans_quai(Quai* quai);
void sauve_moi();

#endif