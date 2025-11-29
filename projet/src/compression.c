#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compression.h"

/* Trouver le code d'un caractere dans la table */
static char* trouver_code(char c, TableCode* table, int nb_codes) {
	for (int i = 0; i < nb_codes; i++) {
		if (table[i].caractere == c) {
			return table[i].code;
		}
	}
	return NULL;
}

/* Compresser un fichier */
int compresser_fichier(const char* fichier_source, const char* fichier_sortie, TableCode* table, int nb_codes) {
	FILE* source = fopen(fichier_source, "r");
	FILE* sortie = fopen(fichier_sortie, "w");
	
	if (source == NULL || sortie == NULL) {
		perror("Erreur d'ouverture des fichiers");
		if (source) fclose(source);
		if (sortie) fclose(sortie);
		return -1;
	}
	
	int c;
	long nb_bits = 0;
	
	/* Lire chaque caractere et ecrire son code */
	while ((c = fgetc(source)) != EOF) {
		char* code = trouver_code((char)c, table, nb_codes);
		
		if (code == NULL) {
			fprintf(stderr, "Erreur: caractere '%c' non trouve dans la table\n", c);
			fclose(source);
			fclose(sortie);
			return -1;
		}
		
		/* Ecrire le code dans le fichier */
		fprintf(sortie, "%s", code);
		nb_bits += strlen(code);
	}
	
	fclose(source);
	fclose(sortie);
	
	printf("\nCompression terminee!\n");
	printf("Nombre de bits dans le fichier compresse: %ld\n", nb_bits);
	
	return 0;
}


/* Sauvegarder la table des codes ET les frequences dans un fichier */
void sauvegarder_table_codes(const char* fichier, TableCode* table, int nb, Frequence* freq, int nb_freq) {
	FILE* f = fopen(fichier, "w");
	
	if (f == NULL) {
		perror("Erreur d'ouverture du fichier de codes");
		return;
	}
	
	/* Ecrire le nombre de codes */
	fprintf(f, "%d\n", nb);
	
	/* Ecrire chaque code AVEC sa frequence correspondante */
	for (int i = 0; i < nb; i++) {
		/* Chercher la frequence correspondante */
		int frequence = 0;
		for (int j = 0; j < nb_freq; j++) {
			if (freq[j].caractere == table[i].caractere) {
				frequence = freq[j].frequence;
				break;
			}
		}
		
		if (table[i].caractere == '\n') {
			fprintf(f, "\\n %s %d\n", table[i].code, frequence);
		} else if (table[i].caractere == ' ') {
			fprintf(f, "\\s %s %d\n", table[i].code, frequence);
		} else if (table[i].caractere == '\t') {
			fprintf(f, "\\t %s %d\n", table[i].code, frequence);
		} else {
			fprintf(f, "%c %s %d\n", table[i].caractere, table[i].code, frequence);
		}
	}
	
	fclose(f);
	printf("\nTable des codes sauvegardee dans: %s\n", fichier);
}

/* Calculer les statistiques de compression */
void afficher_statistiques(const char* fichier_source, const char* fichier_compresse) {
	FILE* source = fopen(fichier_source, "r");
	FILE* compresse = fopen(fichier_compresse, "r");
	
	if (source == NULL || compresse == NULL) {
		perror("Erreur d'ouverture des fichiers pour statistiques");
		if (source) fclose(source);
		if (compresse) fclose(compresse);
		return;
	}
	
	/* Compter les caracteres du fichier source */
	long nb_caracteres = 0;
	while (fgetc(source) != EOF) {
		nb_caracteres++;
	}
	
	/* Compter les bits du fichier compresse */
	long nb_bits = 0;
	while (fgetc(compresse) != EOF) {
		nb_bits++;
	}
	
	fclose(source);
	fclose(compresse);
	
	/* Calculer les tailles */
	long taille_originale = nb_caracteres * 8;	/* 8 bits par caractere */
	long taille_compressee = nb_bits;
	double taux_compression = 100.0 * (1.0 - ((double)taille_compressee / (double)taille_originale));
	
	/* Afficher les statistiques */
	printf("\n=== Statistiques de Compression ===\n");
	printf("Fichier source:        %s\n", fichier_source);
	printf("Nombre de caracteres:  %ld\n", nb_caracteres);
	printf("Taille originale:      %ld bits (%ld octets)\n", taille_originale, taille_originale / 8);
	printf("\nFichier compresse:     %s\n", fichier_compresse);
	printf("Taille compressee:     %ld bits (%ld octets)\n", taille_compressee, taille_compressee / 8);
	printf("\nTaux de compression:   %.2f%%\n", taux_compression);
	printf("Gain:                  %ld bits\n", taille_originale - taille_compressee);
}
