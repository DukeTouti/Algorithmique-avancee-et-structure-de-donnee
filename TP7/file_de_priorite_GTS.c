#include<stdio.h>
#include<stdlib.h>


/*Macro pour simplifier l’accès aux tableau.*/

#define x(indice) (x->tab[indice])
# define MEM_SEG 256
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
    int imax; // l'indice de la valeur max dans le tableu
    imax = i;
    if ((gauche(i) <= dernier(x)) && (x(gauche(i)) > x(imax)))
        imax = gauche(i);
    if ((droite(i) <= dernier(x)) && (x(droite(i)) > x(imax)))
        imax = droite(i);
    if ( imax != i) 
    { 
        echangenoeud(x, i, imax);
        entasserMax(x, imax);
    }
 }
// Construction d'un Tas max

void construireTasMax(noeud x){
   int i;
   if (tailleTas(x) > 1)
     {
       for (i = parent(dernier(x)); i >= racine(x); i--)  //en commance du milieu du tableu
        {
            entasserMax(x, i);
        }
     }
 }
 //fonction entasser Min
void entasserMin(noeud x, int i){
    int imin; // l'indice de la valeur min dans le tableu
    imin = i;
    if ((gauche(i) <= dernier(x)) && (x(gauche(i)) < x(imin)))
        imin = gauche(i);
    if ((droite(i) <= dernier(x)) && (x(droite(i)) < x(imin)))
        imin = droite(i);
    if ( imin != i) 
    { 
        echangenoeud(x, i, imin);
        entasserMin(x, imin);
    }
 }

 // Construction d'un Tas min

void construireTasMin(noeud x){
   int i;
   if (tailleTas(x) > 1)
     {
       for (i = parent(dernier(x)); i >= racine(x); i--)//en commance du milieu du tableu
        {
            entasserMin(x, i);
        }
     }
 }
//afficher les elements d'un noeud
void affichernoeud(noeud x){
    printf("[ ");
    for(int i=0; i<x->taille; i++)
            printf("%d\t ", x->tab[i]);
    printf(" ]\n");
 }
 

void augmenterArbre(noeud x){

  
 }

void diminuerArbre(noeud x){


 }


/****************************************** TAS MAX ******************/
//Augmenter cle, recursivité

void augmenterCle(noeud x, int i){

 
}
//Augmenter cle, boucle
void augmenterCle2(noeud x, int i,int cle){


}
//Ajout d'éléments
void insererTasMax(noeud x, int e){
   
}


// Supprimer des éléments
int extraireMax(noeud x){
  int max;
  
  return max;
}


/****************************************** TAS MIN ******************/

//diminuer cle, recursivité
void diminuerCle(noeud x, int i){

}
//diminuer cle, boucle
void diminuerCle2(noeud x, int i,int cle){

}
//Ajout d'éléments
void insererTasMin(noeud x, int e){
  
}

// Supprimer des éléments

int extraireMin(noeud x){
  int min;
  
  return min;
}

/*-------------Main---------------------------------------------------*/
int main() {
   

    


}
