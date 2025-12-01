// L'algorithme de Dijkstra

#include <stdio.h>
#define INFINITY 99
#define V 5

void Dijkstra(int Graph[V][V], int n, int start);
void Afficher(int Graph[V][V]);

void Dijkstra(int Graph[V][V], int n, int start) {
  int cost[V][V], distance[V], pred[V];
  int visited[V], count, mindistance, nextnode, i, j;

  // Initialisation de la matrice coût
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];
   
   printf("Après  initialisation\n");    
   Afficher(cost); 
  
   for (i = 0; i < n; i++) {
    distance[i] = INFINITY;//cost[start][i];
    pred[i] = -1; //Nil
    visited[i] = 0;
  }
 // A l'initialisation 
  distance[start] = 0; //Noeud source

  for (i = 0; i < n; i++) 
    printf("Initialement la distance de noeud source %d au noeud %d: %d\n", start, i, distance[i]);

  count = 0;

  while (count < n ) {
    mindistance = INFINITY;
   // Sélectionner, parmi les nœuds non visités, le nœud "nextnode" ayant la distance minimale de sommet
    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i; // noeud suivant à visiter
      }
    
   printf("\nA itiration %d le noeud à visiter est %d\n", count, nextnode);
   for (i = 0; i < n; i++)
      printf("Distance de noeud source %d au noeud %d: %d\n", start, i, distance[i]);
    
    //Marquer comme visité : similaire à supprimer de la FILE de priorité (EXTRAIRE)
    visited[nextnode] = 1; // Marquer ce noeud comme visité

    //Relachement de tous les arcs sortants de nextnode vers les voisins
    for (i = 0; i < n; i++)
      if(Graph[nextnode][i] != 0) // si nextnode et i sont voisins (arc sortant de nextnode vers i)
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  //Aficher les distances de la source
 /* for (i = 0; i < n; i++)
    if (i != start) {
      printf("\nDistance de noeud source %d au noeud %d: %d\n", start, i, distance[i]);
    }*/
}

// Afficher les elements de la matrice
void Afficher(int G[][V]) {
  int i, j;

  for (i = 0; i < V; i++) {
    printf("%d: ", i);
    for (j = 0; j < V; j++) {
      printf("%d ", G[i][j]);
    }
    printf("\n");
  }
  printf("\n");

}

int main() {
  int M[V][V], i, j, u;

  // Graphe de la Figure 3.30 page 100
  // s(0); t(1); x(2); z(3); y(4); 
  
  printf("A Completer en utilisant le graphe de la figure 3.30\n");   

  return 0;
}
