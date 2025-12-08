#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

// ===== ACTIVER UN SEUL ALGORITHME =====
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
	// CHOIX DU GRAPHE (décommenter UN SEUL)
	// ========================================
	
	// ===== BFS : Exemple simple =====
	#if 0
	#ifdef USE_BFS
	Graphe* g = creerGraphe(8, 0);  // 8 sommets, non orienté
	// Modifier les arêtes selon le sujet :
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
	int sommetDepart = 0;  // Modifier selon le sujet
	#endif
	#endif
	
	// ===== DFS : Exemple simple =====
	#if 0
	#ifdef USE_DFS
	Graphe* g = creerGraphe(8, 0);  // 8 sommets, non orienté
	// Modifier les arêtes selon le sujet :
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
	int sommetDepart = 0;  // Modifier selon le sujet
	#endif
	#endif
	
	// ===== KRUSKAL : Exemple MST =====
	#if 0
	#ifdef USE_KRUSKAL
	Graphe* g = creerGraphe(9, 0);  // 9 sommets, non orienté
	// Modifier les arêtes et poids selon le sujet :
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
	#endif
	
	// ===== PRIM : Exemple MST =====
	#if 0
	#ifdef USE_PRIM
	Graphe* g = creerGraphe(9, 0);  // 9 sommets, non orienté
	// Modifier les arêtes et poids selon le sujet :
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
	#endif

	#if 1
	#ifdef USE_BELLMAN_FORD
	Graphe* g = creerGraphe(7, 1);  // 5 sommets, orienté
	// s=0, t=1, x=2, z=3, y=4
	ajouterArrete(g, 0, 1, 1);  // z -> s (2)
	ajouterArrete(g, 0, 2, 4);  // z -> x (7)
	ajouterArrete(g, 0, 3, -1);  // s -> t (6)
	ajouterArrete(g, 1, 2, 1);  // s -> y (7)
	ajouterArrete(g, 1, 5, -2);  // t -> x (5)
	ajouterArrete(g, 2, 3, 2); // t -> z (-4)
	ajouterArrete(g, 2, 4, 0);  // t -> y (8)
	ajouterArrete(g, 2, 5, 4);  // t -> y (8)
	ajouterArrete(g, 2, 6, 1); // x -> t (-2)
	ajouterArrete(g, 3, 4, 1); // y -> x (-3)
	ajouterArrete(g, 4, 6, 2);  // y -> z (9)
	ajouterArrete(g, 5, 6, -1);  // y -> z (9)
	int sommetSource = 0;  // Depuis z
	#endif
	#endif
	
	// ===== ANNALE 1 : Dijkstra (graphe avec a,b,c,d,e,f,g) =====
	#if 0
	#ifdef USE_DIJKSTRA
	Graphe* g = creerGraphe(7, 1);  // 7 sommets, orienté
	// a=0, b=1, c=2, d=3, e=4, f=5, g=6
	ajouterArrete(g, 0, 1, 2);  // a -> b (2)
	ajouterArrete(g, 0, 3, 4);  // a -> d (4)
	ajouterArrete(g, 1, 2, 3);  // b -> c (3)
	ajouterArrete(g, 1, 3, 2);  // b -> d (2)
	ajouterArrete(g, 2, 4, 1);  // c -> e (1)
	ajouterArrete(g, 3, 2, 1);  // d -> c (1)
	ajouterArrete(g, 3, 4, 2);  // d -> e (2)
	ajouterArrete(g, 4, 5, 3);  // e -> f (3)
	ajouterArrete(g, 4, 6, 2);  // e -> g (2)
	int sommetSource = 0;  // Depuis a
	#endif
	#endif
	
	// ===== ANNALE 2 : Dijkstra (graphe avec 6 sommets a,b,c,d,e,f) =====
	#if 0
	#ifdef USE_DIJKSTRA
	Graphe* g = creerGraphe(6, 1);  // 6 sommets, orienté
	// a=0, b=1, c=2, d=3, e=4, f=5
	ajouterArrete(g, 0, 1, 4);  // a -> b (4)
	ajouterArrete(g, 0, 2, 2);  // a -> c (2)
	ajouterArrete(g, 1, 2, 5);  // b -> c (5)
	ajouterArrete(g, 1, 3, 10); // b -> d (10)
	ajouterArrete(g, 2, 4, 3);  // c -> e (3)
	ajouterArrete(g, 3, 5, 11); // d -> f (11)
	ajouterArrete(g, 4, 3, 4);  // e -> d (4)
	int sommetSource = 0;  // Depuis a
	#endif
	#endif
	
	// ===== ANNALE 3 : Floyd-Warshall (graphe 1,2,3,4,5) =====
	#if 0
	#ifdef USE_FLOYD_WARSHALL
	Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté
	// Numérotation : 1=0, 2=1, 3=2, 4=3, 5=4
	ajouterArrete(g, 1, 0, 3);  // 2 -> 1 (3)
	ajouterArrete(g, 1, 2, 1);  // 2 -> 3 (1)
	ajouterArrete(g, 1, 3, 4);  // 2 -> 4 (4)
	ajouterArrete(g, 0, 3, -4); // 1 -> 4 (-4)
	ajouterArrete(g, 0, 2, 7);  // 1 -> 3 (7)
	ajouterArrete(g, 2, 1, 8);  // 3 -> 2 (8)
	ajouterArrete(g, 4, 3, 2);  // 5 -> 4 (2)
	ajouterArrete(g, 3, 4, -5); // 4 -> 5 (-5)
	#endif
	#endif
	
	// ===== ANNALE 4 : Floyd-Warshall (graphe 1,2,3,4 simple) =====
	#if 0
	#ifdef USE_FLOYD_WARSHALL
	Graphe* g = creerGraphe(4, 1);  // 4 sommets, orienté
	// Numérotation : 1=0, 2=1, 3=2, 4=3
	ajouterArrete(g, 0, 1, 1);  // 1 -> 2 (1)
	ajouterArrete(g, 0, 3, 4);  // 1 -> 4 (4)
	ajouterArrete(g, 0, 2, 8);  // 1 -> 3 (8)
	ajouterArrete(g, 1, 2, 2);  // 2 -> 3 (2)
	ajouterArrete(g, 3, 2, 9);  // 4 -> 3 (9)
	ajouterArrete(g, 2, 3, 1);  // 3 -> 4 (1)
	#endif
	#endif
	
	// ===== ANNALE 5 : Bellman-Ford depuis z =====
	#if 0
	#ifdef USE_BELLMAN_FORD
	Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté
	// s=0, t=1, x=2, z=3, y=4
	ajouterArrete(g, 3, 0, 2);  // z -> s (2)
	ajouterArrete(g, 3, 2, 7);  // z -> x (7)
	ajouterArrete(g, 0, 1, 6);  // s -> t (6)
	ajouterArrete(g, 0, 4, 7);  // s -> y (7)
	ajouterArrete(g, 1, 2, 5);  // t -> x (5)
	ajouterArrete(g, 1, 3, -4); // t -> z (-4)
	ajouterArrete(g, 1, 4, 8);  // t -> y (8)
	ajouterArrete(g, 2, 1, -2); // x -> t (-2)
	ajouterArrete(g, 4, 2, -3); // y -> x (-3)
	ajouterArrete(g, 4, 3, 9);  // y -> z (9)
	int sommetSource = 3;  // Depuis z
	#endif
	#endif
	
	
	
	// ===== ANNALE 6 : SCC (Composantes Fortement Connexes) =====
	#if 0
	#ifdef USE_SCC
	Graphe* g = creerGraphe(10, 1);  // 10 sommets, orienté
	// s=0, q=1, f=2, y=3, r=4, v=5, w=6, z=7, x=8, u=9
	ajouterArrete(g, 0, 1, 1);  // s -> q
	ajouterArrete(g, 1, 2, 1);  // q -> f
	ajouterArrete(g, 2, 3, 1);  // f -> y
	ajouterArrete(g, 3, 4, 1);  // y -> r
	ajouterArrete(g, 4, 9, 1);  // r -> u
	ajouterArrete(g, 5, 6, 1);  // v -> w
	ajouterArrete(g, 6, 0, 1);  // w -> s
	ajouterArrete(g, 7, 8, 1);  // z -> x
	ajouterArrete(g, 8, 2, 1);  // x -> f
	#endif
	#endif
	
	// ===== ANNALE 7 : Coloration Welsh-Powell =====
	#if 0
	#ifdef USE_COLORATION
	Graphe* g = creerGraphe(5, 0);  // 5 sommets, non orienté
	// Modifier les arêtes selon le sujet :
	ajouterArrete(g, 0, 1, 1);
	ajouterArrete(g, 1, 2, 1);
	ajouterArrete(g, 2, 3, 1);
	ajouterArrete(g, 3, 0, 1);
	ajouterArrete(g, 0, 2, 1);  // Diagonale
	ajouterArrete(g, 1, 4, 1);
	#endif
	#endif
	
	// ===== ANNALE 8 : Tri Topologique (UV universitaires) =====
	#if 0
	#ifdef USE_TOPO
	Graphe* g = creerGraphe(9, 1);  // 9 cours, orienté
	// UV1=0, UV2=1, UV3=2, UV4=3, UV5=4, UV6=5, UV7=6, UV8=7, UV9=8
	// Modifier les arêtes selon le sujet :
	ajouterArrete(g, 0, 1, 1);  // UV1 -> UV2
	ajouterArrete(g, 0, 2, 1);  // UV1 -> UV3
	ajouterArrete(g, 1, 3, 1);  // UV2 -> UV4
	ajouterArrete(g, 2, 4, 1);  // UV3 -> UV5
	ajouterArrete(g, 3, 5, 1);  // UV4 -> UV6
	ajouterArrete(g, 4, 5, 1);  // UV5 -> UV6
	ajouterArrete(g, 5, 6, 1);  // UV6 -> UV7
	ajouterArrete(g, 5, 7, 1);  // UV6 -> UV8
	ajouterArrete(g, 6, 8, 1);  // UV7 -> UV9
	ajouterArrete(g, 7, 8, 1);  // UV8 -> UV9
	#endif
	#endif
	
	// ===== GRAPHE VIDE POUR L'EXAMEN (à remplir le jour J) =====
	#if 0
	Graphe* g = creerGraphe(5, 1);  // Modifier nb sommets et orienté(1)/non orienté(0)
	
	// Ajouter les arêtes selon le sujet d'examen :
	// ajouterArrete(g, src, dest, poids);
	
	#if defined(USE_DIJKSTRA) || defined(USE_BELLMAN_FORD)
	int sommetSource = 0;  // Modifier selon le sujet
	#endif
	
	#if defined(USE_BFS) || defined(USE_DFS)
	int sommetDepart = 0;  // Modifier selon le sujet
	#endif
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
