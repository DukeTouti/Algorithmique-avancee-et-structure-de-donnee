#include <stdio.h>
#include <stdlib.h>
#include "tri_fusion.h"

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param tab tableau d'entiers
 * @param res tableau d'entiers vide
 */
int[] copier_tableau(int[] tab, int[] res);

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param gauche tableau d'entiers trié par ordre croissant
 * @param droite tableau d'entiers trié par ordre croissant
 */
int fusionner(int[] gauche, int[] droite);

/**
 * Recherche linéaire naïve d'une valeur encadrée (pour comparaison)
 * @param tab tableau d'entiers
 */
int[] tri_fusion(int[] tab);

