#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "types.h"

/* Compresser un fichier */
int compresser_fichier(const char* fichier_source, const char* fichier_sortie, TableCode* table, int nb_codes);

/* Sauvegarder la table des codes dans un fichier */
void sauvegarder_table_codes(const char* fichier, TableCode* table, int nb);

/* Calculer les statistiques de compression */
void afficher_statistiques(const char* fichier_source, const char* fichier_compresse);

#endif
