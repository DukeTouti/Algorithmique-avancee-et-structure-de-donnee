#ifndef TYPES_TAS_H
#define TYPES_TAS_H

/*Structure d'un noeud*/
typedef struct { 
	int* tab;  /* Tableau */
	int mem;  /* Nombre maximum d'éléments dans le tableau */
	int taille; /* Nombre d’éléments de l'arbre */
} *noeud;
  
#endif
