#include <stdio.h>
#include <stdlib.h>
#include "frequences.h"
#include "huffman.h"
#include "decodage.h"

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Usage: %s <fichier_compresse> <fichier_codes>\n", argv[0]);
		return 1;
	}
	
	printf("=== Decompression de Huffman ===\n\n");
	
	/* Etape 1: Charger la table des codes */
	printf("Chargement de la table des codes: %s\n", argv[2]);
	TableCode table[256];
	int nb_codes = charger_table_codes(argv[2], table);
	
	if (nb_codes < 0) {
		fprintf(stderr, "Erreur lors du chargement de la table\n");
		return 1;
	}
	
	printf("Table chargee: %d codes\n", nb_codes);
	
	/* Etape 2: Construire l'arbre depuis les codes */
	printf("\n=== Reconstruction de l'arbre ===\n");
	NoeudHuffman* racine = construire_arbre_depuis_codes(table, nb_codes);
	
	if (racine == NULL) {
		fprintf(stderr, "Erreur lors de la reconstruction de l'arbre\n");
		return 1;
	}
	
	printf("Arbre reconstruit avec succes!\n");
	
	/* Etape 3: Decompresser */
	printf("\n=== Decompression ===\n");
	int resultat = decompresser_fichier(argv[1], "../tests/decompresse.txt", racine);
	
	if (resultat != 0) {
		fprintf(stderr, "Erreur lors de la decompression\n");
		liberer_arbre(racine);
		return 1;
	}
	
	printf("Fichier decompresse: ../tests/decompresse.txt\n");
	
	/* Liberer la memoire */
	liberer_arbre(racine);
	
	printf("\nDecompression terminee avec succes!\n");
	
	return 0;
}
