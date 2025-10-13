# include <stdlib.h>
# include <stdio.h>

/* Utile: max(p, q) renvoie le maximum entre ces deux entiers */

int max(int p, int q) {
  return (p > q) ? p : q;
}

/*
   On définit un type pour les éléments et une fonction de comparaison
   entre éléments
*/
typedef int element_t;

int comparer(element_t a, element_t b){
  if (a < b) return 1;
  if (a > b) return -1;
  return 0;
}

void affiche_element(element_t a) {
  printf("%2d ", a);
}


/*
  Définition des arbres binaires. L'arbre vide est représenté par NULL.
*/

struct noeud_s {
  element_t        e;
  struct noeud_s * gauche;
  struct noeud_s * droite;
  struct noeud_s * parent;
} ;

typedef  struct noeud_s * ab_t;


/* nouveau_noeud(a), crée (allocation mémoire) et renvoie un arbre à
   un seul noeud contenant l'élément a. */

ab_t nouveau_noeud(element_t a){
  ab_t x;
  x =(ab_t) malloc(sizeof(struct noeud_s));
  if (!x) {
    perror("Echec malloc");
  }
  x->parent = NULL;
  x->gauche = NULL;
  x->droite = NULL;
  x->e = a;
  return x;
}

/* inserer(&x, a) insere un élément a dans un arbre binaire de
   recherche x. S'il existe déjà un élément b égal à a dans l'arbre
   aucun noeud n'est créé (pas de répétition).  La fonction inserer()
   ne renvoie rien, l'arbre x est passé par adresse (px = adresse de
   l'arbre) pour être directement modifié (argument-résultat). */

void inserer(ab_t *px, element_t a){
  if (!(*px)) {
    *px = nouveau_noeud(a);
     printf("nouveau_noeud \n");
  }
  else {
    ab_t y, parent;
    int cote;
    y = *px;
    /* Recherche de la place de a (parent et côté où le mettre) */
    while (y) {
      parent = y;
      cote = comparer(a, y->e);

     //printf("cote=%d \n",cote);
      switch(cote){
      case 1: /* côté gauche */
        y = y->gauche;
        break;
      case -1: /* côté droit */
        y = y->droite;
        break;
      case 0: /* on a déjà cet élément, pas d'insertion */
        return;
      }
    }
    /* parent sera le parent du nouveau noeud, la valeur de cote dit
       de quel côté l'attacher à son parent.  */
    y = nouveau_noeud(a);
    y->parent = parent;
    if (1 == cote) {
      parent->gauche = y;
    }
    else {
      parent->droite = y;
    }
  }
}

/* Affichage "simple" en mode texte, exemple :

L'arbre       4
             / \
            1   7
           / \   \
          0   3   9
                 /
                8

s'affichera comme ceci :


 4 ----- 7 ----- 9
 |               |
 |               8
 |
 1 ----- 3
 |
 0

*/

/* fonction auxilliaire pour l'affichage d'une ligne de traits
   verticaux représentant la descendance à gauche. */

void afficher_arbre_aux1(ab_t x){
  if (x->parent) {
    afficher_arbre_aux1(x->parent);
    if (x == (x->parent)->droite) {
      if ((x->parent)->gauche) {
        printf(" |      "); /* 8 caractères */
      }
      else {
        printf("        "); /* 8 caractères */
      }
    }
  }
}

/* afficher_arbre(x) réalise l'affichage de x sur la sortie standard
   comme décrit plus haut. */

void afficher_arbre(ab_t x){
  if (x) { /* Si l'arbre n'est pas vide, on réalise l'affichage par
              appels récursifs sur les sous-arbres non vides. */

    affiche_element(x->e);
    if (x->droite) { /* noeuds de droite sur la même ligne */
      printf("-----");
      afficher_arbre(x->droite);
    }
    else { /* plus rien à droite : fin de ligne */
    printf("\n");
    }
    if (x->gauche) {
      afficher_arbre_aux1(x->gauche);
      printf(" |      \n"); /* 8 caractères */
      afficher_arbre_aux1(x->gauche);
      afficher_arbre(x->gauche);
    }
  }
  else { /* Si l'arbre est vide on le signale */
    printf("\n        (arbre vide)\n\n");
  }
}

/* vider(&x) : libère l'espace mémoire utilisé par l'arbre x, et met x
   à NULL (arbre vide) */

void vider(ab_t *px){
  ab_t x;
  x = *px;
  if (x) {
    vider(&(x->gauche));
    vider(&(x->droite));
    free(x);
    *px = NULL;
  }
}





/* parcours_infixe(x) affiche les éléments de x dans l'ordre */

void parcours_infixe(ab_t x)
  { // à compléter



  }

/* parcours_prefixe(x) affiche les éléments de x dans l'ordre */

void parcours_prefixe(ab_t x)
 { // à compléter



  
 }


/* parcours_postfixe(x) affiche les éléments de x dans l'ordre */

void parcours_postfixe(ab_t x)
  {// à compléter
  



  }


/* cardinal(x) renvoie le nombre de noeuds de l'arbre x */

int cardinal(ab_t x)
  {// à compléter, homework



  }


/* hauteur(x) renvoie la hauteur de l'arbre x */

int hauteur(ab_t x)
  {
   // à compléter, homework


  }

/* maximum(x) renvoie NULL si x est vide et l'élément maximum sinon */

ab_t maximum(ab_t x)
  {// à compléter



  }


/* minimum(x): de même que maximum(x), pour le minimum */

ab_t minimum(ab_t x)
 { // à compléter



  }


/* successeur(x) prend l'adresse d'un noeud d'un abr et renvoie le
   successeur de ce noeud dans l'arbre. */

ab_t successeur(ab_t x)
 { // à compléter




  }




/* predecesseur(x) prend l'adresse d'un noeud d'un abr et renvoie le
   predecesseur de ce noeud dans l'arbre. */

ab_t predecesseur(ab_t x)
  { // à compléter, home work



  }

/* rechercher(x, a) cherche un element b dans l'arbre x tel que a = b
   au sens de la fonction de comparaison des éléments, et renvoie le
   noeud contenant b ou NULL si un tel element n'existe pas . */

ab_t rechercher(ab_t x, element_t a)
  { // à compléter
  



  }


/* supprimer(px, y) supprime l'élément contenu dans le noeud d'adresse
   y de l'arbre d'adresse px.

*/

void supprimer(ab_t * px, ab_t y)
  { // à compléter



  }




/************************Main*******************************/

int main() {
    ab_t            x = NULL;
    element_t       i;
    element_t       tab[] = {5, 2, 4, 3, 7, 6, 1, 9, 8, 0};
    element_t       tab2[] = {1, 4, 5, 3, 2};
 // printf("ds du parcours \n");
    for (i = 0; i < 10; i++) {
     inserer(&x, tab[i]);
     // printf("i=%d \n",i);
     //
    }

    afficher_arbre(x); 

    printf("-------------------TRAVAIL DEMANDE-----------------------------\n");
    printf("\t\t -> parcours_infixe\n");
    printf("\t\t -> parcours_prefixe\n");
    printf("\t\t -> parcours_postfixe\n");
    printf("\t\t -> maximum\n");
    printf("\t\t -> minimum\n");
    printf("\t\t -> successeur\n");
    printf("\t\t -> rechercher\n");
    printf("\t\t -> supprimer\n");
    printf("\t\t -> predecesseur\n");
    printf("\t\t -> cardinal\n");
    printf("\t\t -> hauteur\n");




   /*parcours_infixe(x);
    printf("fin du parcours \n");
    printf("\nAffichage ***************************\n");
    afficher_arbre(x);

    supprimer(&x, rechercher(x, 2));
    printf("\nAffichage (supprimer 2)**************\n");
    afficher_arbre(x);

    supprimer(&x, rechercher(x, 5));
    printf("\nAffichage (supprimer 5)**************\n");
    afficher_arbre(x);

    supprimer(&x, rechercher(x, 2));
    printf("\nAffichage (supprimer 2)**************\n");
    afficher_arbre(x);

    supprimer(&x, rechercher(x, 7));
    printf("\nAffichage (supprimer 7)**************\n");
    afficher_arbre(x);

    vider(&x);
    printf("\nAffichage (vider)********************\n");
    afficher_arbre(x);

    for (i = 0; i < 5; i++) {
     inserer(&x, tab2[i]);
    }

    printf("\nAffichage ***************************\n");
    afficher_arbre(x);

    vider(&x);
    printf("\nAffichage (vider)********************\n");
    afficher_arbre(x);
*/
    return EXIT_SUCCESS;
}
