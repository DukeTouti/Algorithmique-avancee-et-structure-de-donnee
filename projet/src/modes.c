#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "modes.h"
#include "frequences.h"
#include "huffman.h"
#include "compression.h"
#include "decodage.h"

/* Mode interactif : compression de texte saisi */
void mode_interactif(void) {
	char ligne[1000];
	
	printf("\n=== Mode Interactif - Compression de Huffman ===\n");
	printf("Tapez votre texte et appuyez sur Entree.\n");
	printf("Tapez 'quit' pour quitter.\n\n");
	
	while (1) {
		printf("> ");
		if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
			break;
		}
		
		/* Verifier si l'utilisateur veut quitter */
		if (strcmp(ligne, "quit\n") == 0) {
			printf("\nAu revoir !\n");
			break;
		}
		
		/* Creer un fichier temporaire avec le texte */
		FILE* temp = fopen(".temp_input.txt", "w");
		fprintf(temp, "%s", ligne);
		fclose(temp);
		
		/* Calculer les frequences */
		int nb_caracteres;
		Frequence* freq = calculer_frequences(".temp_input.txt", &nb_caracteres);
		
		if (freq == NULL || nb_caracteres == 0) {
			printf("Erreur : texte vide ou invalide\n\n");
			continue;
		}
		
		/* Construire l'arbre */
		NoeudHuffman* racine = construire_arbre_huffman(freq, nb_caracteres);
		
		/* Generer les codes */
		TableCode table[256];
		char code[256] = "";
		int index = 0;
		generer_codes(racine, code, 0, table, &index);
		
		/* Afficher les codes */
		printf("\nCodes Huffman generes :\n");
		for (int i = 0; i < index; i++) {
			if (table[i].caractere == '\n') {
				printf("  '\\n' : %s\n", table[i].code);
			} else if (table[i].caractere == ' ') {
				printf("  ' '  : %s\n", table[i].code);
			} else {
				printf("  '%c'  : %s\n", table[i].caractere, table[i].code);
			}
		}
		
		/* Compresser */
		compresser_fichier(".temp_input.txt", ".temp_compresse.txt", table, index);
		
		/* Afficher le texte compressé */
		printf("\nTexte compresse (en bits) :\n");
		FILE* comp_display = fopen(".temp_compresse.txt", "r");
		int c_display;
		while ((c_display = fgetc(comp_display)) != EOF) {
			printf("%c", c_display);
		}
		printf("\n");
		fclose(comp_display);
		
		/* Calculer le taux de compression */
		long taille_originale = strlen(ligne) * 8;
		
		FILE* comp = fopen(".temp_compresse.txt", "r");
		long taille_compressee = 0;
		while (fgetc(comp) != EOF) {
			taille_compressee++;
		}
		fclose(comp);
		
		double taux = 100.0 * (1.0 - ((double)taille_compressee / (double)taille_originale));
		
		printf("\nTaux de compression : %.2f%%\n", taux);
		printf("(%ld bits -> %ld bits)\n\n", taille_originale, taille_compressee);
		
		/* Nettoyer */
		liberer_frequences(freq);
		liberer_arbre(racine);
		remove(".temp_input.txt");
		remove(".temp_compresse.txt");
	}
}

/* Mode fichier : compression complete d'un fichier */
void mode_fichier(const char* chemin_fichier) {
	printf("\n=== Compression de Fichier ===\n");
	printf("Fichier source : %s\n\n", chemin_fichier);
	
	/* Extraire le repertoire et le nom du fichier */
	char* chemin_copie = strdup(chemin_fichier);
	char* repertoire = dirname(chemin_copie);
	
	char* chemin_copie2 = strdup(chemin_fichier);
	char* nom_fichier = basename(chemin_copie2);
	
	/* Enlever l'extension .txt */
	char nom_base[256];
	strcpy(nom_base, nom_fichier);
	char* point = strrchr(nom_base, '.');
	if (point != NULL) {
		*point = '\0';
	}
	
	/* Creer les chemins de sortie */
	char chemin_codes[512];
	char chemin_compresse[512];
	char chemin_decompresse[512];
	
	snprintf(chemin_codes, sizeof(chemin_codes), "%s/%s_codes.txt", repertoire, nom_base);
	snprintf(chemin_compresse, sizeof(chemin_compresse), "%s/%s_compresse.txt", repertoire, nom_base);
	snprintf(chemin_decompresse, sizeof(chemin_decompresse), "%s/%s_decompresse.txt", repertoire, nom_base);
	
	/* Etape 1 : Calculer les frequences */
	printf("Etape 1/5 : Calcul des frequences...\n");
	int nb_caracteres;
	Frequence* freq = calculer_frequences(chemin_fichier, &nb_caracteres);
	
	if (freq == NULL) {
		fprintf(stderr, "Erreur lors du calcul des frequences\n");
		free(chemin_copie);
		free(chemin_copie2);
		return;
	}
	
	printf("  -> %d caracteres distincts\n", nb_caracteres);
	
	/* Etape 2 : Construire l'arbre */
	printf("Etape 2/5 : Construction de l'arbre de Huffman...\n");
	NoeudHuffman* racine = construire_arbre_huffman(freq, nb_caracteres);
	printf("  -> Arbre construit\n");
	
	/* Etape 3 : Generer les codes */
	printf("Etape 3/5 : Generation des codes...\n");
	TableCode table[256];
	char code[256] = "";
	int index = 0;
	generer_codes(racine, code, 0, table, &index);
	printf("  -> %d codes generes\n", index);
	
	/* Etape 4 : Compression */
	printf("Etape 4/5 : Compression...\n");
	sauvegarder_table_codes(chemin_codes, table, index, freq, nb_caracteres);
	compresser_fichier(chemin_fichier, chemin_compresse, table, index);
	printf("  -> Fichier compresse\n");
	
	/* Etape 5 : Decompression */
	printf("Etape 5/5 : Decompression (verification)...\n");
	TableCode table2[256];
	int nb_codes = charger_table_codes(chemin_codes, table2);
	NoeudHuffman* racine2 = construire_arbre_depuis_codes(table2, nb_codes);
	decompresser_fichier(chemin_compresse, chemin_decompresse, racine2);
	printf("  -> Fichier decompresse\n");
	
	/* Verification */
	printf("\nVerification de l'integrite...\n");
	FILE* original = fopen(chemin_fichier, "r");
	FILE* decompresse = fopen(chemin_decompresse, "r");
	
	int identique = 1;
	int c1, c2;
	while ((c1 = fgetc(original)) != EOF) {
		c2 = fgetc(decompresse);
		if (c1 != c2) {
			identique = 0;
			break;
		}
	}
	if (fgetc(decompresse) != EOF) {
		identique = 0;
	}
	
	fclose(original);
	fclose(decompresse);
	
	if (identique) {
		printf("   Verification reussie : fichiers identiques\n");
	} else {
		printf("   ERREUR : fichiers differents !\n");
	}
	
	/* Afficher les statistiques */
	printf("\n");
	afficher_statistiques(chemin_fichier, chemin_compresse);
	
	/* Afficher les fichiers crees */
	printf("\n=== Fichiers Crees ===\n");
	printf("  - %s\n", chemin_codes);
	printf("  - %s\n", chemin_compresse);
	printf("  - %s\n", chemin_decompresse);
	
	/* Nettoyer */
	liberer_frequences(freq);
	liberer_arbre(racine);
	liberer_arbre(racine2);
	free(chemin_copie);
	free(chemin_copie2);
}
