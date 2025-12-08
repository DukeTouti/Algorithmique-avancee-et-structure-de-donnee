# 📊 Kit Complet d'Algorithmes sur les Graphes - Exam TP

Ensemble complet d'implémentations modulaires en C pour tous les algorithmes de graphes du cours d'Algorithmique Avancée.

---

## 📁 Structure du Projet
```
Exam_TP/
│
├── graphe.h              # Structure commune pour tous les algorithmes
├── graphe.c              # Fonctions de base (création, ajout, affichage)
│
├── bfs.h / bfs.c         # Parcours en Largeur (BFS)
├── dfs.h / dfs.c         # Parcours en Profondeur (DFS)
├── topo.h / topo.c       # Tri Topologique
├── scc.h / scc.c         # Composantes Fortement Connexes (Kosaraju)
├── kruskal.h / kruskal.c # Arbre Couvrant Minimum (Kruskal)
├── prim.h / prim.c       # Arbre Couvrant Minimum (Prim)
├── dijkstra.h / dijkstra.c      # Plus Court Chemin (Dijkstra)
├── bellman.h / bellman.c        # Plus Court Chemin (Bellman-Ford)
├── floyd.h / floyd.c            # Plus Courts Chemins (Floyd-Warshall)
├── coloration.h / coloration.c  # Coloration de Graphe
│
├── main.c                # Programme principal
└── Makefile              # Compilation automatique
```

---

## 🚀 Compilation et Exécution

### Compiler le projet
```bash
make clean
make
```

### Exécuter
```bash
./graphe_exam
```

ou directement :
```bash
make run
```

---

## 🎯 Comment Utiliser pour l'Examen

### 1️⃣ Choisir l'algorithme à tester

Ouvrir `main.c` et **décommenter** l'algorithme voulu (lignes 8-17) :
```c
// ===== ACTIVER UN SEUL ALGORITHME =====
// #define USE_BFS
// #define USE_DFS
// #define USE_TOPO
// #define USE_SCC
// #define USE_KRUSKAL
// #define USE_PRIM
// #define USE_DIJKSTRA
#define USE_BELLMAN_FORD    // ← Celui-ci sera exécuté
// #define USE_FLOYD_WARSHALL
// #define USE_COLORATION
```

### 2️⃣ Modifier les données du graphe

Dans `main.c`, section **"DONNÉES DU GRAPHE"** :

**Pour un graphe orienté :**
```c
Graphe* g = creerGraphe(5, 1);  // 5 sommets, orienté (1)
```

**Pour un graphe non orienté :**
```c
Graphe* g = creerGraphe(5, 0);  // 5 sommets, non orienté (0)
```

**Ajouter des arêtes :**
```c
ajouterArrete(g, source, destination, poids);

// Exemples :
ajouterArrete(g, 0, 1, 6);   // Arc 0 → 1 avec poids 6
ajouterArrete(g, 1, 2, -2);  // Arc 1 → 2 avec poids -2
```

### 3️⃣ Recompiler et exécuter
```bash
make clean && make && ./graphe_exam
```

---

## 📚 Liste des Algorithmes Disponibles

| Algorithme | Type de Graphe | Utilisation |
|-----------|---------------|-------------|
| **BFS** | Non orienté | Parcours en largeur, distances |
| **DFS** | Orienté/Non orienté | Parcours en profondeur |
| **Tri Topologique** | Orienté acyclique (DAG) | Ordre linéaire des sommets |
| **SCC (Kosaraju)** | Orienté | Composantes fortement connexes |
| **Kruskal** | Non orienté pondéré | Arbre couvrant minimum |
| **Prim** | Non orienté pondéré | Arbre couvrant minimum |
| **Dijkstra** | Orienté pondéré (≥0) | Plus courts chemins (origine unique) |
| **Bellman-Ford** | Orienté pondéré (avec négatifs) | Plus courts chemins + détection cycles |
| **Floyd-Warshall** | Orienté pondéré | Plus courts chemins (toutes paires) |
| **Coloration** | Non orienté | Nombre chromatique, coloration gloutonne |

---

## 🔧 Exemples de Graphes Prêts à l'Emploi

### Exemple BFS/DFS (Figure 3.6 du cours)
```c
Graphe* g = creerGraphe(8, 0);
ajouterArrete(g, 0, 1, 1);
ajouterArrete(g, 0, 3, 1);
ajouterArrete(g, 1, 2, 1);
// ... voir main.c
```

### Exemple Bellman-Ford (Figure 3.32 du cours)
```c
Graphe* g = creerGraphe(5, 1);
ajouterArrete(g, 0, 1, 6);
ajouterArrete(g, 1, 3, -4);  // Poids négatif OK
// ... voir main.c
```

### Exemple Floyd-Warshall (Figure 3.35 du cours)
```c
Graphe* g = creerGraphe(5, 1);
ajouterArrete(g, 0, 4, -4);
ajouterArrete(g, 3, 2, -5);
// ... voir main.c
```

---

## 📝 Format de Sortie

Chaque algorithme affiche :
- ✅ **La structure du graphe** (listes d'adjacence)
- ✅ **Les étapes de calcul** détaillées
- ✅ **Les résultats finaux** (distances, chemins, MST, etc.)

**Parfait pour comparer avec le calcul manuel !**

---

## ⚠️ Notes Importantes

### Types de Graphes
- **Orienté** : Les arêtes ont une direction (A → B ≠ B → A)
- **Non orienté** : Les arêtes sont bidirectionnelles (A — B)

### Poids des Arêtes
- **Dijkstra** : Nécessite des poids **≥ 0**
- **Bellman-Ford** : Accepte les poids **négatifs**
- **BFS/DFS** : Poids = 1 (ou ignoré)

### Détection de Cycles Négatifs
- **Bellman-Ford** : Détecte et signale
- **Floyd-Warshall** : Détecte et signale

---

## 📖 Guide Rapide pour l'Examen

### Stratégie Day-J 🎯

1. **Lire l'énoncé** → Identifier le type de graphe (orienté/non orienté, pondéré/non pondéré)
2. **Ouvrir `main.c`** → Décommenter le bon `#define`
3. **Modifier les données** → Changer `nbSommets` et `ajouterArrete()`
4. **Compiler et exécuter** → `make && ./graphe_exam`
5. **Comparer avec calcul manuel** → Utiliser la sortie détaillée

### Checklist Avant l'Examen ✅
- [ ] Tester chaque algorithme au moins une fois
- [ ] Vérifier que tous les fichiers compilent sans erreur
- [ ] Imprimer ce README si besoin
- [ ] Avoir le Makefile prêt

---

## 🛠️ Dépendances

- **GCC** (ou tout compilateur C)
- **Make**
- Aucune bibliothèque externe nécessaire

---

## 📧 Support

En cas de problème :
1. Vérifier que tous les fichiers `.h` et `.c` sont dans le même répertoire
2. Faire `make clean` avant de recompiler
3. Vérifier les numéros de sommets (doivent être entre 0 et nbSommets-1)

---

## 📜 Licence

Code développé pour les examens TP d'Algorithmique Avancée.  
Libre d'utilisation pour des fins académiques.

---

## 👨‍💻 Crédits

**Développé par Claude (Anthropic)** - Assistant IA spécialisé en programmation  
Préparé spécialement pour l'examen TP de graphes - Décembre 2025  
*Because even algorithms need a little AI magic* ✨

---

**Bon courage pour l'examen ! 🚀💪**
