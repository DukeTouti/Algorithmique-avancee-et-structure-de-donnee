#include <stdio.h>
#include <stdlib.h>
#include "tas_min.h"

int main() {
	printf("=== Test du Tas-Min ===\n\n");
	
	/* Creer un tas */
	TasMin* tas = creer_tas_min(10);
	
	/* Inserer des noeuds avec differentes frequences */
	printf("Insertion des noeuds...\n");
	inserer(tas, creer_noeud('A', 5, 1));
	inserer(tas, creer_noeud('B', 2, 1));
	inserer(tas, creer_noeud('C', 8, 1));
	inserer(tas, creer_noeud('D', 1, 1));
	inserer(tas, creer_noeud('E', 3, 1));
	
	/* Afficher le tas */
	printf("\nTas apres insertions:\n");
	afficher_tas(tas);
	
	/* Extraire les minimums */
	printf("\n=== Extraction des minimums ===\n");
	while (tas->taille > 0) {
		NoeudHuffman* min = extraire_min(tas);
		printf("Extrait: '%c' (freq = %d)\n", min->caractere, min->frequence);
		free(min);
	}
	
	detruire_tas(tas);
	
	printf("\nTest termine avec succes!\n");
	
	return 0;
}
