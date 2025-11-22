#ifndef TYPES_H
#define TYPES_H

/* Structure d'un noeud de l'arbre de Huffman */
typedef struct NoeudHuffman {
	char caractere;
	int frequence;
	struct NoeudHuffman* gauche;
	struct NoeudHuffman* droit;
	int est_feuille;		/* 1 si feuille, 0 si noeud interne */
} NoeudHuffman;

/* Structure du tas min */
typedef struct {
	NoeudHuffman** noeuds;		/* Tableau de pointeurs vers les noeuds */
	int taille;			/* Nombre actuel d'elements */
	int capacite;			/* Capacite maximale */
} TasMin;

/* Structure pour les frequences */
typedef struct {
	char caractere;
	int frequence;
} Frequence;

/* Structure pour la table des codes */
typedef struct {
	char caractere;
	char code[256];
} TableCode;

#endif
