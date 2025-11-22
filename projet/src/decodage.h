#ifndef DECODAGE_H
#define DECODAGE_H

#include "types.h"

/* Charger la table des codes depuis un fichier */
int charger_table_codes(const char* fichier, TableCode* table);

/* Construire l'arbre depuis les codes */
NoeudHuffman* construire_arbre_depuis_codes(TableCode* table, int nb_codes);

/* Decompresser un fichier */
int decompresser_fichier(const char* fichier_compresse, const char* fichier_sortie, NoeudHuffman* racine);

#endif
