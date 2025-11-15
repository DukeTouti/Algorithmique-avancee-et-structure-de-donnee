# README - Codes Sources TPs Algorithmique Avancée

## Note importante

Lors de ma soumission initiale des comptes rendus des **TP5** et **TP6** sur Moodle, j'ai **omis de joindre les codes sources** par manque d'attention.

Je tiens à préciser que :
- **Les travaux ont été réalisés dans les délais impartis**
- **Tous les codes compilent sans erreur**
- **Les résultats des comptes rendus proviennent bien de ces codes**

## Vérification de l'authenticité

Pour prouver que le travail a été effectué à temps, l'historique complet est disponible sur mon repo GitHub :

** Lien GitHub :** `https://github.com/DukeTouti/Algorithmique-avancee-et-structure-de-donnee`

Les commits montrent clairement :
- Les dates de création et modification des fichiers
- L'historique complet du développement
- Les tests et validations effectués

---

## Contenu de cette archive

```
Code/
│
├── README.md                 Ce fichier
│
├── TP5/                      Tas Binaires
│   ├── graphique/
│   │   ├── graphique_tas_aleatoire.png
│   │   ├── graphique_tas_comparaison_complete.png
│   │   ├── graphique_tas_croissant.png
│   │   ├── graphique_tas_decroissant.png
│   │   ├── graphique_tas_loglog_aleatoire.png
│   │   ├── graphique_tas_loglog_croissant.png
│   │   └── graphique_tas_loglog_decroissant.png
│   │
│   ├── generer_graphiques_tas.py
│   ├── main.c
│   ├── Makefile
│   ├── resultats_tas.csv
│   ├── tas_operations.c/h
│   ├── tas_utils.c/h
│   └── type_tas.h
│
├── TP6/                      Comparaison des Algorithmes de Tri
│   ├── Graphes/
│   │   ├── graphique_tas_aleatoire.png
│   │   ├── graphique_tas_comparaison_complete.png
│   │   ├── graphique_tas_croissant.png
│   │   ├── graphique_tas_decroissant.png
│   │   ├── graphique_tas_loglog_aleatoire.png
│   │   ├── graphique_tas_loglog_croissant.png
│   │   └── graphique_tas_loglog_decroissant.png
│   │
│   ├── generer_graphiques_tas.py
│   ├── main.c
│   ├── Makefile
│   ├── resultats_comparaison_tri.csv
|   ├── tas_operations.c/h
│   ├── tas_utils.c/h
│   ├── tri_fusion.c/h
│   ├── tri_insertion.c/h
│   └── type_tas.h
│
└── TP7/                      Files de Priorité vs Tableau
    ├── Graphes/
    │   ├── graphique_comparaison_complete.png
    │   ├── graphique_extraction.png
    │   ├── graphique_insertion.png
    │   └── graphique_loglog.png
    │
    ├── generer_graphiques_files.py
    ├── main.c
    ├── Makefile
    ├── resultats_comparaison_files.csv
    ├── tas_min_max.c/h
    ├── tas_operations.c/h
    ├── tas_utils.c/h
    └── types_tas.h
     
```

---

### TP5 - Tas Binaires

**Objectif :** Approfondir l’étude des Tas Binaires.

```bash
# Compilation
cd TP5/
make

# Exécution
./main
```

**Sortie :** Fichier `resultats_tas.csv` contenant les mesures de performance.

**Génération des graphiques :**
```bash
python3 generer_graphiques_tas.py
```

**Graphiques générés :**
- `graphique_tas_aleatoire.png`
- `graphique_tas_comparaison_complete.png`
- `graphique_tas_croissant.png`
- `graphique_tas_decroissant.png`
- `graphique_tas_loglog_aleatoire.png`
- `graphique_tas_loglog_croissant.png`
- `graphique_tas_loglog_decroissant.png`

### TP6 - Comparaison des Algorithmes de Tri

**Objectif :** Comparer Tri Insertion, Tri Fusion et Tri par Tas sur données aléatoires, croissantes et décroissantes.

```bash
# Compilation
cd TP6/
make

# Exécution
./main
```

**Sortie :** Fichier `resultats_comparaison_tri.csv` contenant les mesures de performance.

**Génération des graphiques :**
```bash
python3 generer_graphiques_tas.py
```

**Graphiques générés :**
- `graphique_tas_aleatoire.png`
- `graphique_tas_comparaison_complete.png`
- `graphique_tas_croissant.png`
- `graphique_tas_decroissant.png`
- `graphique_tas_loglog_aleatoire.png`
- `graphique_tas_loglog_croissant.png`
- `graphique_tas_loglog_decroissant.png`

### TP7 - Files de Priorité vs Tableau

**Objectif :** Comparer une File de Priorité (tas binaire) avec un Tableau simple pour l'insertion et l'extraction.

```bash
# Compilation
cd TP7/
make

# Exécution
./main
```

**Sortie :** Fichier `resultats_comparaison_files.csv` contenant les mesures de performance.

**Génération des graphiques :**
```bash
python3 generer_graphiques_files.py
```

**Graphiques générés :**
- `graphique_comparaison_complete.png`
- `graphique_extraction.png`
- `graphique_insertion.png`
- `graphique_loglog.png`

---

## Environnement de développement

|     Composant     |             Version             |
|-------------------|---------------------------------|
| **OS**            | Ubuntu 24.04 (DualBoot)         |
| **Compilateur**   | GCC 11.4.0                      |
| **Norme C**       | C99/C11                         |
| **Options**       | `-Wall -Wextra` (aucun warning) |
| **Python**        | 3.10+                           |
| **Bibliothèques** | pandas, matplotlib, numpy       |

---

## Tests effectués

Tous les codes ont été :
- Compilés sans erreurs ni warnings
- Validés sur plusieurs tailles de données (1000 à 200000 éléments)
- Vérifiés par rapport aux complexités théoriques
- Exécutés sur différentes configurations de données

---

## Informations

**Étudiant :** HATHOUTI Mohammed Taha  
**Filière :** Cybersécurité - 3ème année  
**École :** ESIN - UIR  
**Email :** [mohammed-taha.hathouti@uir.ac.ma]  
**Année académique :** 2025/2026

---

## Conclusion

Je présente mes excuses pour cet oubli lors de la première soumission sur Moodle. Les codes ont bien été développés dans les temps et sont entièrement fonctionnels.

Le repo GitHub mentionné ci-dessus permet de vérifier l'historique complet du travail et les dates de réalisation.

Tous les résultats présentés dans les comptes rendus sont reproductibles avec ces codes.

Merci de votre compréhension.

---

**Date de soumission des codes :** [samedi 15 novembre 2025]
