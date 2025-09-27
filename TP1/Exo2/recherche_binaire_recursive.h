#ifndef RECHERCHE_BINAIRE_RECURSIVE_H
#define RECHERCHE_BINAIRE_RECURSIVE_H

/**
 * Recherche binaire itérative dans un tableau trié
 * @param t tableau d'entiers trié par ordre croissant
 * @param d indice de début
 * @param f indice de fin
 * @param v valeur à rechercher
 * @return l'indice de la valeur si trouvée, -1 sinon
 */
int recherche_binaire_recursive(int tab[], int d, int f, int v);

#endif /* RECHERCHE_BINAIRE_RECURSIVE_H */
