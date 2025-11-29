#ifndef FREQUENCES_H
#define FREQUENCES_H

#include "types.h"

/* Lire un fichier et calculer les frequences de chaque caractere */
Frequence* calculer_frequences(const char* nom_fichier, int* nb_caracteres);

/* Afficher les frequences (pour debug) */
void afficher_frequences(Frequence* freq, int nb);

/* Liberer la memoire des frequences */
void liberer_frequences(Frequence* freq);

#endif
