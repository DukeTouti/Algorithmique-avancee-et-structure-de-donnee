# Projet Huffman - Compression de Données

**Cours :** Algorithmique Avancée et Structures de Données  
**Formation :** CyberSécurité 3A - ESIN - UIR  
**Année :** 2025-2026

---

## Auteur

HATHOUTI Mohammed Taha - CyberSécurité 3A ESIN

Enseignant : M. BAKHOUYA  
Cours : Algorithmique Avancée et Structures de Données

---

## Description

Ce projet implémente l'algorithme de compression de Huffman, une méthode de compression sans perte basée sur l'encodage à longueur variable. L'algorithme attribue des codes binaires plus courts aux caractères les plus fréquents, permettant ainsi de réduire significativement la taille des fichiers texte.

Principe :
- Les caractères fréquents --> codes courts (ex: '0', '10')
- Les caractères rares --> codes longs (ex: '11110', '11111')
- Aucune perte d'information lors de la compression/décompression

---

## Fonctionnalités

- Compression : Encodage de fichiers texte selon l'algorithme de Huffman
- Décompression : Décodage complet et vérification d'intégrité
- Mode interactif : Compression en temps réel de texte saisi au clavier
- Mode fichier : Traitement automatique de fichiers avec génération de statistiques
- Statistiques détaillées : Taux de compression, gain en bits, tailles avant/après

---

## Architecture

### Structure du Projet
```
HATHOUTI-Mohammed-Taha-ProjetI/
│
├── src/
│   ├── types.h              # Structures de données
│   ├── tas_min.h/c          # Tas minimum (file de priorité)
│   ├── frequences.h/c       # Calcul des fréquences
│   ├── huffman.h/c          # Construction arbre + génération codes
│   ├── compression.h/c      # Encodage
│   ├── decodage.h/c         # Décodage
│   ├── modes.h/c            # Modes interactif et fichier
│   ├── main.c               # Point d'entrée
│   ├── test_tas.c           # Tests du tas minimum
│   ├── test_huffman.c       # Tests arbre + codes
│   ├── test_compression.c   # Tests compression
│   ├── test_decodage.c      # Tests décompression
│   └── Makefile             # Compilation
│
└── tests/
    ├── exemples_simples/    # Tests basiques (4 fichiers)
    ├── exemples_textes/     # Textes réalistes (6 fichiers)
    └── cas_limites/         # Cas extrêmes (9 fichiers)
```
    
### Modules

|     Module      |      Fichiers     |                              Description                                |
|-----------------|-------------------|-------------------------------------------------------------------------|
| Types           | `types.h`         | Définitions des structures (NoeudHuffman, TasMin, Frequence, TableCode) |
| Tas-Min         | `tas_min.h/c`     | File de priorité pour construction de l'arbre (O(log n))                |
| Fréquences      | `frequences.h/c`  | Calcul des occurrences de chaque caractère                              |
| Huffman         | `huffman.h/c`     | Construction de l'arbre et génération des codes                         |
| Compression     | `compression.h/c` | Encodage du fichier source                                              |
| Décodage        | `decodage.h/c`    | Décodage et reconstruction de l'arbre                                   |
| Modes           | `modes.h/c`       | Interface utilisateur (interactif + fichier)                            |

---

## Compilation
```bash
# 1. Se placer dans le dossier source
cd src/

# 2. Compiler tous les exécutables
make

# 3. Vérifier la compilation
ls -l huffman test_*
```

**Exécutables générés :**
- `huffman` - Programme principal (compression/décompression)
- `test_tas` - Tests du tas minimum
- `test_huffman` - Tests de l'arbre de Huffman
- `test_compression` - Tests de compression
- `test_decodage` - Tests de décompression

---

## Utilisation

### Mode 1 : Interactif

Compression en temps réel de texte saisi au clavier.
```bash
./huffman
```

**Exemple d'utilisation :**
```
=== Mode Interactif - Compression de Huffman ===
Tapez votre texte et appuyez sur Entrée.
Tapez 'quit' pour quitter.

> Bonjour le monde

Codes Huffman générés :
  'B' : 0000
  'o' : 001
  'n' : 010
  ...

Texte compressé (en bits) :
000000100100011010001...

Taux de compression : 52.50%
(144 bits -> 68 bits)

> quit

Au revoir !
```

### Mode 2 : Fichier

Compression complète d'un fichier avec vérification automatique.
```bash
./huffman 
```

**Exemple :**
```bash
./huffman ../tests/exemples_textes/simple.txt
```

**Sortie :**
```
=== Compression de Fichier ===
Fichier source : ../tests/exemples_textes/simple.txt

Étape 1/5 : Calcul des fréquences...
  -> 12 caractères distincts

Étape 2/5 : Construction de l'arbre de Huffman...
  -> Arbre construit

Étape 3/5 : Génération des codes...
  -> 12 codes générés

Étape 4/5 : Compression...
  -> Fichier compressé

Étape 5/5 : Décompression (vérification)...
  -> Fichier décompressé

Vérification de l'intégrité...
  ✅ Vérification réussie : fichiers identiques

=== Statistiques de Compression ===
Fichier source:        ../tests/exemples_textes/simple.txt
Nombre de caractères:  17
Taille originale:      136 bits (17 octets)

Fichier compressé:     ../tests/exemples_textes/simple_compresse.txt
Taille compressée:     62 bits (7 octets)

Taux de compression:   54.41%
Gain:                  74 bits

=== Fichiers Créés ===
  - ../tests/exemples_textes/simple_codes.txt
  - ../tests/exemples_textes/simple_compresse.txt
  - ../tests/exemples_textes/simple_decompresse.txt
```

### Fichiers Générés

Pour chaque fichier compressé, 3 fichiers sont créés :

|       Fichier       |               Description               |
|---------------------|-----------------------------------------|
| `*_codes.txt`       | Table des codes Huffman avec fréquences |
| `*_compresse.txt`   | Fichier compressé (séquence de bits)    |
| `*_decompresse.txt` | Fichier décompressé (vérification)      |

---

## Tests

### Tests Automatiques par Module
```bash
# Test 1 : Tas minimum
./test_tas

# Test 2 : Arbre de Huffman et génération de codes
./test_huffman ../tests/exemples_simples/court.txt

# Test 3 : Compression
./test_compression ../tests/exemples_textes/simple.txt

# Test 4 : Décompression
./test_decodage ../tests/compresse.txt ../tests/codes.txt
```

---

**Pour plus de détails sur les algorithmes et structures de données, consulter le compte-rendu LaTeX.**

---

**Date :** Novembre 2025 

















