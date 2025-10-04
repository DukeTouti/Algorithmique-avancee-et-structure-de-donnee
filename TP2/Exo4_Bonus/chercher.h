#ifndef CHERCHER_H
#define CHERCHER_H

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param A tableau d'entiers trié par ordre croissant
 * @param s indice de début
 * @param f indice de fin
 * @param a borne inférieure
 * @param b borne supérieure
 * @return l'indice d'un élément tel que a <= A[i] <= b, ou -1 si non trouvé
 */
int chercher_recursif(int A[], int s, int f, int a, int b);

/**
 * Recherche linéaire naïve d'une valeur encadrée (pour comparaison)
 * @param A tableau d'entiers
 * @param n taille du tableau
 * @param a borne inférieure
 * @param b borne supérieure
 * @return l'indice d'un élément tel que a <= A[i] <= b, ou -1 si non trouvé
 */
int chercher_lineaire(int A[], int n, int a, int b);

#endif
