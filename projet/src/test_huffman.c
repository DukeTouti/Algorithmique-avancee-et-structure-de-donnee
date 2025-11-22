#include <stdio.h>
#include <stdlib.h>
#include "frequences.h"
#include "huffman.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <fichier_texte>\n", argv[0]);
		return 1;
	}
	
	printf("=== Test du Codage de Huffman ===\n\n");
	
	/* Etape 1: Calculer les frequences */
	printf("Lecture du fichier: %s\n", argv[1]);
	int nb_caracteres;
	Frequence* freq = calculer_frequences(argv[1], &nb_caracteres);
	
	if (freq == NULL) {
		fprintf(stderr, "Erreur lors du calcul des frequences\n");
		return 1;
	}
	
	/* Afficher les frequences */
	afficher_frequences(freq, nb_caracteres);
	
	/* Etape 2: Construire l'arbre de Huffman */
	printf("\n=== Construction de l'arbre de Huffman ===\n");
	NoeudHuffman* racine = construire_arbre_huffman(freq, nb_caracteres);
	
	if (racine == NULL) {
		fprintf(stderr, "Erreur lors de la construction de l'arbre\n");
		liberer_frequences(freq);
		return 1;
	}
	
	printf("Arbre construit avec succes!\n");
	
	/* Afficher l'arbre */
	printf("\n=== Arbre de Huffman ===\n");
	afficher_arbre(racine, 0);
	
	/* Etape 3: Generer les codes */
	printf("\n=== Generation des codes ===\n");
	TableCode table[256];
	char code[256] = "";
	int index = 0;
	
	generer_codes(racine, code, 0, table, &index);
	
	/* Afficher la table des codes */
	afficher_table_codes(table, index);
	
	/* Liberer la memoire */
	liberer_frequences(freq);
	liberer_arbre(racine);
	
	printf("\nTest termine avec succes!\n");
	
	return 0;
}
