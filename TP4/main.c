#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "types_abr.h"
#include "abr_operations.h"
#include "abr_parcours.h"
#include "abr_affichage.h"

/* Fonction pour generer un tableau aleatoire */
static void generer_tableau_aleatoire(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 100000;
    }
}

/* Fonction pour generer un tableau trie croissant */
static void generer_tableau_croissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
}

/* Fonction pour generer un tableau trie decroissant */
static void generer_tableau_decroissant(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = n - i;
    }
}

/* Fonction pour verifier si un arbre respecte la propriete ABR */
static int verifier_abr_aux(ab_t a, int min, int max) {
    if (!a) {
        return 1;
    }
    
    if ((a->e < min) || (a->e > max)) {
        return 0;
    }
    
    return verifier_abr_aux(a->gauche, min, a->e - 1) && 
           verifier_abr_aux(a->droit, a->e + 1, max);
}

static int verifier_abr(ab_t a) {
    return verifier_abr_aux(a, -1000000, 1000000);
}

/* Insertion equilibree : insere le milieu du tableau puis recursivement */
static void inserer_equilibre_aux(ab_t *pa, int tab[], int debut, int fin) {
    if (debut > fin) {
        return;
    }
    
    int milieu = (debut + fin) / 2;
    inserer(pa, tab[milieu]);
    inserer_equilibre_aux(pa, tab, debut, milieu - 1);
    inserer_equilibre_aux(pa, tab, milieu + 1, fin);
}

static void inserer_equilibre(ab_t *pa, int tab[], int n) {
    inserer_equilibre_aux(pa, tab, 0, n - 1);
}

/* Insertion sequentielle (ordre d'arrivee) */
static void inserer_sequentiel(ab_t *pa, int tab[], int n) {
    for (int i = 0; i < n; i++) {
        inserer(pa, tab[i]);
    }
}

int main() {
    srand(time(NULL));
    
    printf("=== COMPARAISON DES METHODES D'INSERTION DANS LES ABR ===\n\n");
    
    /* ============================================
       TEST 1 : Exemple simple avec affichage
       ============================================ */
    printf("--- TEST 1 : Demonstration sur petit tableau ---\n");
    int tab1[] = {5, 2, 4, 3, 7, 6, 1, 9, 8, 0};
    int n1 = 10;
    
    printf("Tableau initial : [ ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", tab1[i]);
    }
    printf("]\n\n");
    
    /* Insertion sequentielle (desequilibre) */
    ab_t arbre_seq = NULL;
    for (int i = 0; i < n1; i++) {
        inserer(&arbre_seq, tab1[i]);
    }
    
    printf("Arbre avec insertion sequentielle :\n");
    afficher_arbre(arbre_seq);
    printf("Hauteur : %d\n", hauteur(arbre_seq));
    printf("Cardinal : %d\n", cardinal(arbre_seq));
    printf("Validation ABR : %s\n\n", verifier_abr(arbre_seq) ? "VALIDE" : "ERREUR");
    
    /* Insertion equilibree */
    int tab1_trie[10];
    memcpy(tab1_trie, tab1, n1 * sizeof(int));
    
    /* Trier le tableau pour insertion equilibree */
    for (int i = 0; i < n1 - 1; i++) {
        for (int j = i + 1; j < n1; j++) {
            if (tab1_trie[i] > tab1_trie[j]) {
                int tmp = tab1_trie[i];
                tab1_trie[i] = tab1_trie[j];
                tab1_trie[j] = tmp;
            }
        }
    }
    
    ab_t arbre_eq = NULL;
    inserer_equilibre(&arbre_eq, tab1_trie, n1);
    
    printf("Arbre avec insertion equilibree :\n");
    afficher_arbre(arbre_eq);
    printf("Hauteur : %d\n", hauteur(arbre_eq));
    printf("Cardinal : %d\n", cardinal(arbre_eq));
    printf("Validation ABR : %s\n\n", verifier_abr(arbre_eq) ? "VALIDE" : "ERREUR");
    
    vider(&arbre_seq);
    vider(&arbre_eq);
    
    /* ============================================
       TEST 2 : Comparaison de performance
       ============================================ */
    printf("--- TEST 2 : Analyse de performance ---\n\n");
    
    FILE *f = fopen("resultats_abr.csv", "w");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    
    fprintf(f, "Taille,Type,Hauteur_Equilibre,Hauteur_Sequentiel,Temps_Insertion_Equilibre,Temps_Insertion_Sequentiel,Temps_Recherche_Equilibre,Temps_Recherche_Sequentiel\n");
    
    int sizes[] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    int nb_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    char* types[] = {"aleatoire", "croissant", "decroissant"};
    int nb_types = 3;
    
    for (int type_idx = 0; type_idx < nb_types; type_idx++) {
        printf("\n=== Tests avec donnees %s ===\n", types[type_idx]);
        
        for (int i = 0; i < nb_sizes; i++) {
            int n = sizes[i];
            
            int *tab = malloc(n * sizeof(int));
            int *tab_trie = malloc(n * sizeof(int));
            
            if (tab == NULL || tab_trie == NULL) {
                perror("Erreur d'allocation memoire");
                free(tab);
                free(tab_trie);
                fclose(f);
                return 1;
            }
            
            /* Generer le tableau selon le type */
            if (type_idx == 0) {
                generer_tableau_aleatoire(tab, n);
            } else if (type_idx == 1) {
                generer_tableau_croissant(tab, n);
            } else {
                generer_tableau_decroissant(tab, n);
            }
            
            /* Copier et trier pour insertion equilibree */
            memcpy(tab_trie, tab, n * sizeof(int));
            for (int a = 0; a < n - 1; a++) {
                for (int b = a + 1; b < n; b++) {
                    if (tab_trie[a] > tab_trie[b]) {
                        int tmp = tab_trie[a];
                        tab_trie[a] = tab_trie[b];
                        tab_trie[b] = tmp;
                    }
                }
            }
            
            printf("Test avec n = %d elements (%s)\n", n, types[type_idx]);
            
            /* ========== INSERTION EQUILIBREE ========== */
            ab_t arbre_equilibre = NULL;
            
            clock_t start_eq = clock();
            inserer_equilibre(&arbre_equilibre, tab_trie, n);
            clock_t end_eq = clock();
            
            int hauteur_eq = hauteur(arbre_equilibre);
            int validation_eq = verifier_abr(arbre_equilibre);
            
            double temps_insertion_eq = ((double)(end_eq - start_eq) / CLOCKS_PER_SEC) * 1000000;
            
            printf("  Insertion equilibree : %s (h=%d)\n", 
                   validation_eq ? "OK" : "ERREUR", hauteur_eq);
            
            /* Recherche sur arbre equilibre */
            clock_t start_recherche_eq = clock();
            for (int j = 0; j < n; j++) {
                rechercher(arbre_equilibre, tab[j]);
            }
            clock_t end_recherche_eq = clock();
            
            double temps_recherche_eq = ((double)(end_recherche_eq - start_recherche_eq) / CLOCKS_PER_SEC) * 1000000;
            
            /* ========== INSERTION SEQUENTIELLE ========== */
            ab_t arbre_sequentiel = NULL;
            
            clock_t start_seq = clock();
            inserer_sequentiel(&arbre_sequentiel, tab, n);
            clock_t end_seq = clock();
            
            int hauteur_seq = hauteur(arbre_sequentiel);
            int validation_seq = verifier_abr(arbre_sequentiel);
            
            double temps_insertion_seq = ((double)(end_seq - start_seq) / CLOCKS_PER_SEC) * 1000000;
            
            printf("  Insertion sequentielle : %s (h=%d)\n", 
                   validation_seq ? "OK" : "ERREUR", hauteur_seq);
            
            /* Recherche sur arbre sequentiel */
            clock_t start_recherche_seq = clock();
            for (int j = 0; j < n; j++) {
                rechercher(arbre_sequentiel, tab[j]);
            }
            clock_t end_recherche_seq = clock();
            
            double temps_recherche_seq = ((double)(end_recherche_seq - start_recherche_seq) / CLOCKS_PER_SEC) * 1000000;
            
            /* Affichage des resultats */
            printf("  Temps insertion equilibre : %.2f µs\n", temps_insertion_eq);
            printf("  Temps insertion sequentiel : %.2f µs\n", temps_insertion_seq);
            printf("  Temps recherche equilibre : %.2f µs\n", temps_recherche_eq);
            printf("  Temps recherche sequentiel : %.2f µs\n", temps_recherche_seq);
            
            if (validation_eq && validation_seq) {
                double ratio_insertion = temps_insertion_seq / temps_insertion_eq;
                double ratio_recherche = temps_recherche_seq / temps_recherche_eq;
                printf("  Ratio insertion : %.2fx\n", ratio_insertion);
                printf("  Ratio recherche : %.2fx\n", ratio_recherche);
            }
            printf("\n");
            
            /* Sauvegarde dans CSV */
            fprintf(f, "%d,%s,%d,%d,%.2f,%.2f,%.2f,%.2f\n", 
                    n, types[type_idx], 
                    hauteur_eq, hauteur_seq,
                    temps_insertion_eq, temps_insertion_seq,  // ✅ CORRIGÉ : variable complète
                    temps_recherche_eq, temps_recherche_seq);
            
            /* Liberation memoire */
            vider(&arbre_equilibre);
            vider(&arbre_sequentiel);
            free(tab);
            free(tab_trie);
        }
    }
    
    fclose(f);
    
    printf("=== ANALYSE THEORIQUE ===\n");
    printf("Arbre equilibre :\n");
    printf("  - Hauteur : O(log n)\n");
    printf("  - Insertion : O(log n)\n");
    printf("  - Recherche : O(log n)\n\n");
    
    printf("Arbre desequilibre (pire cas) :\n");
    printf("  - Hauteur : O(n)\n");
    printf("  - Insertion : O(n)\n");
    printf("  - Recherche : O(n)\n\n");
    
    printf("Les resultats ont ete sauvegardes dans 'resultats_abr.csv'\n");
    printf("Executez 'python3 generer_graphiques_abr.py' pour visualiser les courbes.\n");
    
    return 0;
}
