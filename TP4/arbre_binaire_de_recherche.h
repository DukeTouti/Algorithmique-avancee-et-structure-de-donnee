#ifndef ARBER_BINAIRE_DE_RECHERCHE_H
#define ARBER_BINAIRE_DE_RECHERCHE_H

/*
 *  On définit un type pour les éléments et une fonction de comparaison entre éléments
 */
typedef int element_t;

/*
 *  Définition des arbres binaires. L'arbre vide est représenté par NULL.
 */
struct noeud_s {
	element_t e;
	struct noeud_s * gauche;
	struct noeud_s * droite;
	struct noeud_s * parent;
} ;

typedef struct noeud_s * ab_t;

/* Utile: max(p, q) renvoie le maximum entre ces deux entiers */

int max(int p, int q);

int comparer(element_t a, element_t b);

void affiche_element(element_t a);

void inserer(ab_t *px, element_t a);

/* 
 *  nouveau_noeud(a), crée (allocation mémoire) et renvoie un arbre à un seul noeud contenant l'élément a.
 */

ab_t nouveau_noeud(element_t a);

void afficher_arbre_aux1(ab_t x);

void afficher_arbre(ab_t x);

/* vider(&x) : libère l'espace mémoire utilisé par l'arbre x, et met x à NULL (arbre vide) */

void vider(ab_t *px);

/* parcours_infixe(x) affiche les éléments de x dans l'ordre */

void parcours_infixe(ab_t x);

/* parcours_prefixe(x) affiche les éléments de x dans l'ordre */

void parcours_prefixe(ab_t x);

/* parcours_postfixe(x) affiche les éléments de x dans l'ordre */

void parcours_postfixe(ab_t x);

/* cardinal(x) renvoie le nombre de noeuds de l'arbre x */

int cardinal(ab_t x);

/* hauteur(x) renvoie la hauteur de l'arbre x */

int hauteur(ab_t x);

/* maximum(x) renvoie NULL si x est vide et l'élément maximum sinon */

ab_t maximum(ab_t x);

/* minimum(x): de même que maximum(x), pour le minimum */

ab_t minimum(ab_t x);

/* 
 *  successeur(x) prend l'adresse d'un noeud d'un abr et renvoie le successeur de ce noeud dans l'arbre.
 */

ab_t successeur(ab_t x);

/*
 *  predecesseur(x) prend l'adresse d'un noeud d'un abr et renvoie le predecesseur de ce noeud dans l'arbre.
 */

ab_t predecesseur(ab_t x);

/* 
 *  rechercher(x, a) cherche un element b dans l'arbre x tel que a = b
 *  au sens de la fonction de comparaison des éléments, et renvoie le
 *  noeud contenant b ou NULL si un tel element n'existe pas . 
 */

ab_t rechercher(ab_t x, element_t a);

/*
 *  supprimer(px, y) supprime l'élément contenu dans le noeud d'adresse y de l'arbre d'adresse px.
 */
void supprimer(ab_t * px, ab_t y);

#endif
