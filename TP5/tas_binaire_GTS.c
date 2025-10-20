#include<stdio.h>
#include<stdlib.h>


/*Macro pour simplifier l’accès aux tableau.*/

#define x(indice) (x->tab[indice])

/*----------------- La structure d'un noeud-------------*/
typedef struct
  { 
    int* tab;  // le tableau
    int mem;  // Nombre maximum d'éléments dans le tableau
    int taille; // nombre d’éléments de l'arbre

  } *noeud;

noeud nouveauTas(void){  //fonction pour créer un nouveau noeud
  noeud x;
  x = malloc(sizeof(noeud));
  if (x == NULL) perror("Echec malloc");
  x->tab= NULL;
  x->taille = 0;
  x->mem = 0;
  return x;
}
/*----------------Fonctions Utiles-----------------------------------*/

// Retourner le parent du noeud i
int parent(int i) {
    return (i - 1) / 2;
}

// Retourner le fils gauche du noeud i
int gauche(int i) {
    return 2*i + 1;
}

// Retourner le fils droite du noeud i
int droite(int i) {
    return 2*i + 2;
}

// La racine de l'arbre
int racine(noeud x){
   return 0;
 }

// indice du dernier élément
int dernier(noeud x){
   return x->taille - 1;
 }

// nb d’éléments dans l’arbre

int tailleTas(noeud x){
    return x->taille;
 }

// fonction permettenat l'échange d'elements similaire à celle des tableaux
void echangenoeud(noeud x, int i, int j){
    int e;
    e = x(i);
    x(i) = x(j);
    x(j) = e;
 }

// fonction entasser Max
void entasserMax(noeud x, int i){
   // à compléter
 }

 //fonction entasser Min
void entasserMin(noeud x, int i){
   // à compléter
 }

// Construction d'un Tas max

void construireTasMax(noeud x){
   // à compléter
 }
 
 // Construction d'un Tas min

void construireTasMin(noeud x){
   // à compléter
 }
//afficher les elements d'un noeud
void affichernoeud(noeud x){
    printf("[ ");
    for(int i=0; i<x->taille; i++)
            printf("%d\t ", x->tab[i]);
    printf(" ]\n");
 }
/*-------------Main---------------------------------------------------*/
int main() {
    // int t[10]={5, 8, 9, 10, 18, 56, 7, 11, 14, 45};

    // noeud x;
    // x = nouveauTas(); /* allocation mémoire */
    // x->tab = t; /* On fait juste référence au tableau sans le recopier. On travaille donc "en place".*/
    // x->mem = 0;///sizeof(*t);
    // x->taille = sizeof(t)/sizeof(*t);
    // printf("le tas binaire: ");
    // affichernoeud(x);
    // construireTasMax(x);
    // printf("le tas binaire Max: ");
    // affichernoeud(x);

    printf("-------------------TRAVAIL DEMANDE-----------------------------\n");
    printf("\t\t -> construction d'un tas max\n");
    printf("\t\t -> entasser max\n");
    printf("\t\t -> construction d'un tas min\n");
    printf("\t\t -> entasser min\n");
  
 }
