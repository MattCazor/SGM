#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "structures.h"

int savePort(Quai *listeQuais, Mouillage *zoneMouillage, Navire *naviresEnMer, char *port);
const char *typeNavireEnChaine(TYPE_NAVIRE type);
const char *etatNavireEnChaine(ETAT_NAVIRE etat);
const char *typeNavireAutoriseEnChaine(TYPE_NAVIRE type_autorise);

#endif