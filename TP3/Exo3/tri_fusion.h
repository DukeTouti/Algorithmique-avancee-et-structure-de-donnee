#ifndef TRI_FUSION_H
#define TRI_FUSION_H

/**
 * Copie une portion d'un tableau dans un nouveau tableau alloué
 * @param tab tableau d'entiers source
 * @param debut indice de début (inclus)
 * @param fin indice de fin (exclus)
 * @return pointeur vers le nouveau tableau alloué
 */
int *copier_tableau(int tab[], int debut, int fin);

/**
 * Fusionne deux tableaux triés en un seul tableau trié
 * @param gauche tableau d'entiers trié par ordre croissant
 * @param size_gauche taille du tableau gauche
 * @param droite tableau d'entiers trié par ordre croissant
 * @param size_droite taille du tableau droite
 * @return pointeur vers le nouveau tableau fusionné alloué
 */
int *fusionner(int gauche[], int size_gauche, int droite[], int size_droite);

/**
 * Trie un tableau d'entiers par l'algorithme de tri fusion
 * @param tab tableau d'entiers à trier
 * @param debut indice de début (inclus)
 * @param fin indice de fin (exclus)
 */
void tri_fusion(int tab[], int debut, int fin);

#endif
