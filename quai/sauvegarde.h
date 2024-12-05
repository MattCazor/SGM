#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "structures.h"

const char *typeNavireEnChaine(TYPE_NAVIRE type);
int saveNavire(Navire *liste,char*navire);
const char *etatNavireToString(ETAT_NAVIRE etat);
int saveQuais(Quai *liste, char*quai);

#endif