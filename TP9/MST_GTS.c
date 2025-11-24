#include <stdio.h>
#include <limits.h>

#define V 9
int printMST(int parent[], int n, int graph[V][V]);

// Fonction permettant d'extraire le min
int minKey(int key[], int mstSet[]) {
   int min = INT_MAX, min_index; // La valeur minimale et son index
   for (int v = 0; v < V; v++)
     if (mstSet[v] == 0 && key[v] < min)
         min = key[v], min_index = v;
     
 return min_index;
}

/**************PrimAlgo A complter *************************/
void primMST(int graph[V][V]) {
 // List pour stocker l'arbre MST
 int parent[V]; 
// Les valeurs utilisées pour selectionner le poids minimal d'un arc
 int key[V]; 
 // Pour representer l'enssemble de sommets qui ne sont pas inclus ds le MST
 int mstSet[V]; 
 // Initialiser la clé de chaque sommet à ∞
  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, mstSet[i] = 0;
 // Exception faite de la racine 0 , dont la clé est initialisée à 0 pour qu'elle soit le premier sommet traité
  key[0] = 0; 
  parent[0] = -1; // initialiser le parent à NIL


// Le MST inclut V arcs
   for (int count = 0; count < V - 1; count++) {
     
   // a complter
   
   
   }
     
 // Afficher le MST
    printMST(parent, V, graph);
}

/************Afficher l'arbre************/
int printMST(int parent[], int n, int graph[V][V]) {

 printf("Arc   Poids\n");
 for (int  i = 1; i < V; i++)
   printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

// Afficher les elements de la matrice
void Afficher(int M[V][V]) {
  int i, j;

  for (i = 0; i < V; i++) {
    printf("%d: ", i);
    for (j = 0; j < V; j++) {
      printf("%d ", M[i][j]);
    }
    printf("\n");
  }
}

// Programme principal
int main() {

// On considere le graphe de la Figure 3.24 

  int M[V][V] = { 
	 { 0, 4, 0, 0, 0 , 0, 0, 8, 0},
	 { 4, 0, 8, 0, 0 , 0, 0, 11, 0},
	 {  0, 8, 0, 7, 0 , 4, 0, 0, 2},
	 {  0, 0, 7, 0, 9 , 14, 0, 0, 0},
	 {  0, 0, 0, 9, 0 , 10, 0, 0, 0},
	 {  0, 0, 4, 14, 10 , 0, 2, 0, 0},
	 {  0, 0, 0, 0, 0 , 2, 0, 1, 6},
	 {  8, 11, 0, 0, 0 , 0, 1, 0, 7},
	 {  0, 0, 2, 0, 0 , 0, 6, 7, 0},
      };
        Afficher(M);

return 0;

}
