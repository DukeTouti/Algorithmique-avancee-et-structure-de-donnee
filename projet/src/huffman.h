#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "types.h"
#include "tas_min.h"
#include "frequences.h"

/* Construire l'arbre de Huffman a partir des frequences */
NoeudHuffman* construire_arbre_huffman(Frequence* freq, int nb_caracteres);

/* Generer les codes pour chaque caractere (parcours recursif) */
void generer_codes(NoeudHuffman* racine, char* code_actuel, int profondeur, TableCode* table, int* index);

/* Afficher l'arbre de Huffman (pour debug) */
void afficher_arbre(NoeudHuffman* racine, int niveau);

/* Afficher la table des codes */
void afficher_table_codes(TableCode* table, int nb);

/* Liberer l'arbre de Huffman */
void liberer_arbre(NoeudHuffman* racine);

#endif
