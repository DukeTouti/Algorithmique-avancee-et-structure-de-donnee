#ifndef TRI_FUSION_H
#define TRI_FUSION_H

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param tab tableau d'entiers
 * @param debut indice de debut
 * @param fin indice de fin
 */
int *copier_tableau(int[] tab, int debut, int fin)

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param gauche tableau d'entiers trié par ordre croissant
 * @param size_gauche taille du tableau gauche
 * @param droite tableau d'entiers trié par ordre croissant
 * @param size_droite taille du tableau droite
 */
int fusionner(int[] gauche, int size_gauche, int[] droite, int size_droite);

/**
 * Recherche linéaire naïve d'une valeur encadrée (pour comparaison)
 * @param tab tableau d'entiers
 * @param size taille du tableau tab
 */
int[] tri_fusion(int[] tab, int size);

#endif
