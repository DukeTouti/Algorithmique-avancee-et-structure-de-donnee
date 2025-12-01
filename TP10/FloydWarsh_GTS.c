// L'algorithme Floyd-Warshall

#include <stdio.h>

// Nombre de sommets
#define V 5

#define INF 99

void printMatrix(int matrix[][V]);

// Fonction Floyd-Warshall
void FW(int graph[][V]) {
  int matrix[V][V], i, j, k;

  for (i = 0; i < V; i++)
    for (j = 0; j < V; j++)
      matrix[i][j] = graph[i][j];

  printMatrix(matrix);

  // Ajouter sommets
  for (k = 0; k < V; k++) {
    for (i = 0; i < V; i++) {
      for (j = 0; j < V; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
    }

    printMatrix(matrix);
  }
  //printMatrix(matrix);
}

void printMatrix(int matrix[][V]) {
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (matrix[i][j] == INF)
        printf("%4s", "INF");
      else
        printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");

}

int main() {
  
  printf("Utiliser l'exemple de la Figure 3.35\n");
  int M[V][V] = {
	     {0, 3, 8, INF, -4},
             {INF, 0, INF, 1, 7},
             {INF, 4, 0, INF, INF},
             {2, INF, -5, 0, INF},
	     {INF, INF, INF, 6, 0},

           };
}
