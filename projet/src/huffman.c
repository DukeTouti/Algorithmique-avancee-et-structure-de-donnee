#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/* Construire l'arbre de Huffman a partir des frequences */
NoeudHuffman* construire_arbre_huffman(Frequence* freq, int nb_caracteres) {
	/* Creer un tas-min */
	TasMin* tas = creer_tas_min(nb_caracteres);
	
	/* Inserer tous les caracteres comme des feuilles */
	for (int i = 0; i < nb_caracteres; i++) {
		NoeudHuffman* noeud = creer_noeud(freq[i].caractere, freq[i].frequence, 1);
		inserer(tas, noeud);
	}
	
	/* Construire l'arbre en fusionnant les noeuds */
	while (!est_singleton(tas)) {
		/* Extraire les deux noeuds de frequence minimale */
		NoeudHuffman* gauche = extraire_min(tas);
		NoeudHuffman* droit = extraire_min(tas);
		
		/* Creer un nouveau noeud interne */
		int freq_totale = gauche->frequence + droit->frequence;
		NoeudHuffman* parent = creer_noeud('\0', freq_totale, 0);
		parent->gauche = gauche;
		parent->droit = droit;
		
		/* Reinserer dans le tas */
		inserer(tas, parent);
	}
	
	/* Extraire la racine */
	NoeudHuffman* racine = extraire_min(tas);
	
	/* Liberer le tas (mais pas les noeuds) */
	detruire_tas(tas);
	
	return racine;
}

/* Generer les codes pour chaque caractere (parcours recursif) */
void generer_codes(NoeudHuffman* racine, char* code_actuel, int profondeur, TableCode* table, int* index) {
	if (racine == NULL) {
		return;
	}
	
	/* Si c'est une feuille, enregistrer le code */
	if (racine->est_feuille) {
		code_actuel[profondeur] = '\0';
		table[*index].caractere = racine->caractere;
		strcpy(table[*index].code, code_actuel);
		(*index)++;
		return;
	}
	
	/* Parcourir le fils gauche (ajouter '0') */
	if (racine->gauche != NULL) {
		code_actuel[profondeur] = '0';
		generer_codes(racine->gauche, code_actuel, profondeur + 1, table, index);
	}
	
	/* Parcourir le fils droit (ajouter '1') */
	if (racine->droit != NULL) {
		code_actuel[profondeur] = '1';
		generer_codes(racine->droit, code_actuel, profondeur + 1, table, index);
	}
}

/* Afficher l'arbre de Huffman (pour debug) */
void afficher_arbre(NoeudHuffman* racine, int niveau) {
	if (racine == NULL) {
		return;
	}
	
	/* Afficher le fils droit (en haut) */
	afficher_arbre(racine->droit, niveau + 1);
	
	/* Afficher le noeud actuel avec indentation */
	for (int i = 0; i < niveau; i++) {
		printf("    ");
	}
	
	if (racine->est_feuille) {
		if (racine->caractere == '\n') {
			printf("'\\n' : %d\n", racine->frequence);
		} else if (racine->caractere == ' ') {
			printf("' '  : %d\n", racine->frequence);
		} else {
			printf("'%c'  : %d\n", racine->caractere, racine->frequence);
		}
	} else {
		printf("*    : %d\n", racine->frequence);
	}
	
	/* Afficher le fils gauche (en bas) */
	afficher_arbre(racine->gauche, niveau + 1);
}

/* Afficher la table des codes */
void afficher_table_codes(TableCode* table, int nb) {
	printf("\n=== Table des codes de Huffman ===\n");
	
	for (int i = 0; i < nb; i++) {
		if (table[i].caractere == '\n') {
			printf("'\\n' : %s\n", table[i].code);
		} else if (table[i].caractere == ' ') {
			printf("' '  : %s\n", table[i].code);
		} else if (table[i].caractere == '\t') {
			printf("'\\t' : %s\n", table[i].code);
		} else {
			printf("'%c'  : %s\n", table[i].caractere, table[i].code);
		}
	}
}

/* Liberer l'arbre de Huffman */
void liberer_arbre(NoeudHuffman* racine) {
	if (racine == NULL) {
		return;
	}
	
	/* Liberer recursivement */
	liberer_arbre(racine->gauche);
	liberer_arbre(racine->droit);
	free(racine);
}
