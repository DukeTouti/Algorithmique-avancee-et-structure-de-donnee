#ifndef TYPES_ABR_H
#define TYPES_ABR_H

/*Type des elements stockes dans l'arbre*/
typedef int element_t;

/*Structure d'un noeud*/
struct noeud_s {
	element_t e;
	struct noeud_s *gauche;
	struct noeud_s *droit;
	struct noeud_s *parent;
};

/*Type arbre binaire (pointeur sur noeud)*/
typedef struct noeud_s* ab_t;

/*Création d'un noeud*/
ab_t nouveau_noeud(element_t a);

/*Suppression d'un noeud*/
void vider(ab_t *pa);

#endif
