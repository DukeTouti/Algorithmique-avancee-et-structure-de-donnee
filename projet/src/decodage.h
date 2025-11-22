#ifndef DECODAGE_H
#define DECODAGE_H

#include "types.h"

/* Charger la table des codes depuis un fichier */
int charger_table_codes(const char* fichier, TableCode* table);

/* Decompresser un fichier */
int decompresser_fichier(const char* fichier_compresse, const char* fichier_sortie, NoeudHuffman* racine);

#endif
