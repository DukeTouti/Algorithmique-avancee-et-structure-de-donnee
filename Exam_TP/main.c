#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

// ===== ACTIVER UN SEUL ALGORITHME (décommenter celui que tu veux) =====
// #define USE_BFS
// #define USE_DFS
// #define USE_TOPO
// #define USE_SCC
// #define USE_KRUSKAL
// #define USE_PRIM
// #define USE_DIJKSTRA
#define USE_BELLMAN_FORD
// #define USE_FLOYD_WARSHALL
// #define USE_COLORATION

// ===== Includes conditionnels =====
#ifdef USE_BFS
#include "bfs.h"
#endif

#ifdef USE_DFS
#include "dfs.h"
#endif

#ifdef USE_TOPO
#include "topo.h"
#endif

#ifdef USE_SCC
#include "scc.h"
#endif

#ifdef USE_KRUSKAL
#include "kruskal.h"
#endif

#ifdef USE_PRIM
#include "prim.h"
#endif

#ifdef USE_DIJKSTRA
#include "dijkstra.h"
#endif

#ifdef USE_BELLMAN_FORD
#include "bellman.h"
#endif

#ifdef USE_FLOYD_WARSHALL
#include "floyd.h"
#endif

#ifdef USE_COLORATION
#include "coloration.h"
#endif

int main() {
	
	// ========================================
	// DONNÉES DU GRAPHE (À MODIFIER ICI)
	// ========================================
	
	/* Exemple pour BFS / DFS / Coloration (graphe non orienté) */
	#if defined(USE_BFS) || defined(USE_DFS) || defined(USE_COLORATION)
	Graphe* g = creerGraphe(8, 0);  // 8 sommets, non orienté
	
	// Graphe Figure 3.6 (exemple du cours)
	// s(0); r(1); v(2); w(3); t(4); u(5); x(6); y(7)
	ajouterArrete(g, 0, 1, 1);
	ajouterArrete(g, 0, 3, 1);
	ajouterArrete(g, 1, 2, 1);
	ajouterArrete(g, 3, 4, 1);
	ajouterArrete(g, 3, 6, 1);
	ajouterArrete(g, 4, 5, 1);
	ajouterArrete(g, 4, 6, 1);
	ajouterArrete(g, 5, 6, 1);
	ajouterArrete(g, 5, 7, 1);
	ajouterArrete(g, 6, 7, 1);
	
	int sommetDepart = 0;  // Sommet de départ pour BFS/DFS
	#endif
	
	/* Exemple pour Tri Topologique / SCC (graphe orienté) */
	#if defined(USE_TOPO) || defined(USE_SCC)
	Graphe* g = creerGraphe(6, 1);  // 6 sommets, orienté
	
	// Exemple tri topologique classique
	ajouterArrete(g, 5, 2, 1);
	ajouterArrete(g, 5, 0, 1);
	ajouterArrete(g, 4, 0, 1);
	ajouterArrete(g, 4, 1, 1);
	ajouterArrete(g, 2, 3, 1);
	ajouterArrete(g, 3, 1, 1);
	#endif
	
	/* Exemple pour Kruskal / Prim (graphe non orienté pondéré) */
	#if defined(USE_KRUSKAL) || defined(USE_PRIM)
	Graphe* g = creerGraphe(9, 0);  // 9 sommets, non orienté
	
	// Graphe Figure 3.24 (exemple MST du cours)
	ajouterArrete(g, 0, 1, 4);
	ajouterArrete(g, 0, 7, 8);
	ajouterArrete(g, 1, 2, 8);
	ajouterArrete(g, 1, 7, 11);
	ajouterArrete(g, 2, 3, 7);
	ajouterArrete(g, 2, 5, 4);
	ajouterArrete(g, 2, 8, 2);
	ajouterArrete(g, 3, 4, 9);
	ajouterArrete(g, 3, 5, 14);
	ajouterArrete(g, 4, 5, 10);
	ajouterArrete(g, 5, 6, 2);
	ajouterArrete(g, 6, 7, 1);
	ajouterArrete(g, 6, 8, 6);
	ajouterArrete(g, 7, 8, 7);
	#endif
	
	/* Exemple pour Dijkstra (graphe orienté pondéré) */
	#ifdef USE_DIJKSTRA
	Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté
	
	// Graphe Figure 3.30 (exemple Dijkstra du cours)
	// s(0); t(1); x(2); z(3); y(4)
	ajouterArrete(g, 0, 1, 10);
	ajouterArrete(g, 0, 4, 5);
	ajouterArrete(g, 1, 2, 1);
	ajouterArrete(g, 1, 4, 2);
	ajouterArrete(g, 2, 3, 4);
	ajouterArrete(g, 3, 2, 6);
	ajouterArrete(g, 3, 0, 7);
	ajouterArrete(g, 4, 1, 3);
	ajouterArrete(g, 4, 2, 9);
	ajouterArrete(g, 4, 3, 2);
	
	int sommetSource = 0;  // Sommet source
	#endif
	
	/* Exemple pour Bellman-Ford (graphe orienté pondéré avec poids négatifs) */
	#ifdef USE_BELLMAN_FORD
	Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté
	
	// Graphe Figure 3.32 (exemple Bellman-Ford du cours)
	// s(0); t(1); x(2); z(3); y(4)
	ajouterArrete(g, 0, 1, 6);
	ajouterArrete(g, 0, 4, 7);
	ajouterArrete(g, 1, 2, 5);
	ajouterArrete(g, 1, 3, -4);
	ajouterArrete(g, 1, 4, 8);
	ajouterArrete(g, 2, 1, -2);
	ajouterArrete(g, 3, 2, 7);
	ajouterArrete(g, 3, 0, 2);
	ajouterArrete(g, 4, 2, -3);
	ajouterArrete(g, 4, 3, 9);
	
	int sommetSource = 0;  // Sommet source
	#endif
	
	/* Exemple pour Floyd-Warshall (graphe orienté pondéré) */
	#ifdef USE_FLOYD_WARSHALL
	Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté
	
	// Graphe Figure 3.35 (exemple Floyd-Warshall du cours)
	ajouterArrete(g, 0, 1, 3);
	ajouterArrete(g, 0, 2, 8);
	ajouterArrete(g, 0, 4, -4);
	ajouterArrete(g, 1, 3, 1);
	ajouterArrete(g, 1, 4, 7);
	ajouterArrete(g, 2, 1, 4);
	ajouterArrete(g, 3, 0, 2);
	ajouterArrete(g, 3, 2, -5);
	ajouterArrete(g, 4, 3, 6);
	#endif
	
	// ========================================
	// AFFICHER LE GRAPHE
	// ========================================
	afficherGraphe(g);
	
	#if defined(USE_DIJKSTRA) || defined(USE_BELLMAN_FORD) || defined(USE_FLOYD_WARSHALL)
	afficherMatrice(g);
	#endif
	
	// ========================================
	// EXÉCUTION DE L'ALGORITHME SÉLECTIONNÉ
	// ========================================
	
	#ifdef USE_BFS
	bfs(g, sommetDepart);
	#endif
	
	#ifdef USE_DFS
	dfs(g, sommetDepart);
	#endif
	
	#ifdef USE_TOPO
	triTopologique(g);
	#endif
	
	#ifdef USE_SCC
	kosaraju(g);
	#endif
	
	#ifdef USE_KRUSKAL
	kruskal(g);
	#endif
	
	#ifdef USE_PRIM
	prim(g);
	#endif
	
	#ifdef USE_DIJKSTRA
	dijkstra(g, sommetSource);
	#endif
	
	#ifdef USE_BELLMAN_FORD
	bellmanFord(g, sommetSource);
	#endif
	
	#ifdef USE_FLOYD_WARSHALL
	floydWarshall(g);
	#endif
	
	#ifdef USE_COLORATION
	colorationGraphe(g);
	#endif
	
	// ========================================
	// LIBÉRER LA MÉMOIRE
	// ========================================
	libererGraphe(g);
	
	return 0;
}
