#include "tri_insertion.h"

/**
 * Algorithme de tri par insertion
 * Complexité : O(n²) dans le pire cas, O(n) si déjà trié
 * Avantage : Tri sur place (pas de mémoire supplémentaire)
 */
void tri_insertion(int tab[], int n) {
    int i, j, cle;
    
    for (i = 1; i < n; i++) {
        cle = tab[i];
        j = i - 1;
        
        // Déplacer les éléments plus grands que cle
        // vers la droite
        while (j >= 0 && tab[j] > cle) {
            tab[j + 1] = tab[j];
            j--;
        }
        
        // Insérer cle à sa position
        tab[j + 1] = cle;
    }
}
