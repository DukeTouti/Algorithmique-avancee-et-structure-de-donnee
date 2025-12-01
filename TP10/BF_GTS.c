// Algorithme Bellman-Ford

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99

//La structure pour les arêtes du graphe
struct Arc {
  int u;  //Le sommet de départ de l'arête/arc
  int v;  //Le sommet d'extrémité de l'arête
  int w;  //Le poids de l'arête (u,v)
};

//Le graphe est composé d'arcs
struct Graphe {
  int S;        //Le nombre total de Sommets dans le graphe
  int A;        //Le nombre total d'Arêtes dans le graphe
  struct Arc *arc;  //Le tableau d'arêtes
};

// Fonction d'affichage
void afficher(int tab[], int taille) {
  int i;
  for (i = 0; i < taille; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");
}

// Fonction BF
void BF(struct Graphe *g, int source) {
  //variables
  int i, j, u, v, w;
  //total des sommets du graphe g
  int tV = g->S;
  //total des sommets du graphe g
  int tE = g->A;
  // tableau de distances, taille du tableau égale au nombre de sommets
  int d[tV];
  //tableau de prédécesseurs, taille du tableau  égale au nombre de sommets
  int p[tV];

//******************Phase 1**************************
  //Remplir le tableau des distances et le tableau des prédécesseurs
  // Source-Unique-Initialisation
  for (i = 0; i < tV; i++) {
    d[i] = INFINITY;
    p[i] = 0;
  }

  //Initialiser la distance du sommet source
  d[source] = 0;

//*******************Phase 2****************************
  //Relacher les arcs, |V|-1 fois
  for (i = 1; i <= tV - 1; i++) {
    for (j = 0; j < tE; j++) {
      //Recuperer les infos concernant les arcs (u,v,w)
      u = g->arc[j].u;
      v = g->arc[j].v;
      w = g->arc[j].w;

      // Relacher l'arc (u,v,w)
      if (d[u] != INFINITY && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
  }

  //******************Phase 3*****************************
//Détecter un cycle négatif, Si la valeur change, nous avons un cycle négatif dans le graph et nous ne pouvons pas trouver les distances les plus courtes
  for (i = 0; i < tE; i++) {
    u = g->arc[i].u;
    v = g->arc[i].v;
    w = g->arc[i].w;
    if (d[u] != INFINITY && d[v] > d[u] + w) {
      printf("Cycle de poids négatif détecté !\n");
      return;
    }
  }

  //Aucun cycle de poids négatif trouvé ! Afficher la distance et le tableau des prédécesseurs
  printf("Afficher le tableau des distance: ");
  afficher(d, tV);
  printf("Afficher le tableau des predecesseurs: ");
  afficher(p, tV);
}


int main(void) {
  //creation du graphe g, voir Figure 3.32, page 102
  struct Graphe *g = (struct Graphe *)malloc(sizeof(struct Graphe));
  g->S = 5;  //Nombre total de sommets
  g->A = 10;  //Nombre total d'arcs

  //Tableau des arcs di graphe g
  g->arc = (struct Arc *)malloc(g->A * sizeof(struct Arc));

  //Ajouter les arêtes (u,v,w) du graphe de la Figure 3.32

  //Arc 0-->1
  g->arc[0].u = 0;
  g->arc[0].v = 1;
  g->arc[0].w = 6;
  //Arc 0-->4
  g->arc[1].u = 0;
  g->arc[1].v = 4;
  g->arc[1].w = 7;
  //Arc 1-->2
  g->arc[2].u = 1;
  g->arc[2].v = 2;
  g->arc[2].w = 5;
  //Arc 1 --> 3
  g->arc[3].u = 1;
  g->arc[3].v = 3;
  g->arc[3].w = -4;
  //Arc 1 --> 4
  g->arc[4].u = 1;
  g->arc[4].v = 4;
  g->arc[4].w = 8;
  //Arc 2 --> 1
  g->arc[5].u = 2;
  g->arc[5].v = 1;
  g->arc[5].w = -2;
  //Arc 3 --> 2
  g->arc[6].u = 3;
  g->arc[6].v = 2;
  g->arc[6].w = 7;
  //Arc 3 --> 0
  g->arc[7].u = 3;
  g->arc[7].v = 0;
  g->arc[7].w = 2;
  //Arc 4 --> 2
  g->arc[8].u = 4;
  g->arc[8].v = 2;
  g->arc[8].w = -3;
  //Arc 4 --> 3
  g->arc[9].u = 4;
  g->arc[9].v = 3;
  g->arc[9].w = -3;

  BF(g, 0);  // 0 est le sommet source

  return 0;
}
