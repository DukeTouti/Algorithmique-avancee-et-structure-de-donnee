#include <stdio.h>
#include <stdlib.h>
#include "frequences.h"
#include "huffman.h"
#include "compression.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <fichier_texte>\n", argv[0]);
		return 1;
	}
	
	printf("=== Compression de Huffman ===\n\n");
	
	/* Etape 1: Calculer les frequences */
	printf("Lecture du fichier: %s\n", argv[1]);
	int nb_caracteres;
	Frequence* freq = calculer_frequences(argv[1], &nb_caracteres);
	
	if (freq == NULL) {
		fprintf(stderr, "Erreur lors du calcul des frequences\n");
		return 1;
	}
	
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
	
	/* Etape 3: Generer les codes */
	printf("\n=== Generation des codes ===\n");
	TableCode table[256];
	char code[256] = "";
	int index = 0;
	
	generer_codes(racine, code, 0, table, &index);
	afficher_table_codes(table, index);
	
	/* Etape 4: Sauvegarder la table des codes */
	sauvegarder_table_codes("../tests/codes.txt", table, index);
	
	/* Etape 5: Compresser le fichier */
	printf("\n=== Compression du fichier ===\n");
	int resultat = compresser_fichier(argv[1], "../tests/compresse.txt", table, index);
	
	if (resultat != 0) {
		fprintf(stderr, "Erreur lors de la compression\n");
		liberer_frequences(freq);
		liberer_arbre(racine);
		return 1;
	}
	
	/* Etape 6: Afficher les statistiques */
	afficher_statistiques(argv[1], "../tests/compresse.txt");
	
	/* Liberer la memoire */
	liberer_frequences(freq);
	liberer_arbre(racine);
	
	printf("\nCompression terminee avec succes!\n");
	
	return 0;
}
