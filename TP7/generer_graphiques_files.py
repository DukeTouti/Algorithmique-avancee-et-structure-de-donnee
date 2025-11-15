#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison FILES DE PRIORITÉ vs TABLEAU
TP7 - Algorithmes Avancés
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_comparaison_files.csv'):
    """Charge les données depuis le fichier CSV"""
    if not os.path.exists(nom_fichier):
        print(f"❌ Erreur : Le fichier {nom_fichier} n'existe pas.")
        print(f"   Exécutez d'abord : ./main")
        sys.exit(1)
    
    try:
        df = pd.read_csv(nom_fichier)
        # Nettoyer les noms de colonnes (enlever les espaces)
        df.columns = df.columns.str.strip()
        print(f"✓ Données chargées : {len(df)} points de mesure")
        return df
    except Exception as e:
        print(f"❌ Erreur lors de la lecture du fichier : {e}")
        sys.exit(1)

def calculer_courbes_theoriques(tailles):
    """Calcule les courbes théoriques O(1), O(log n), et O(n)"""
    n = np.array(tailles)
    
    # Constantes pour ajuster les courbes (valeurs arbitraires pour visualisation)
    c_constant = 0.0001  # O(1)
    c_log = 0.001        # O(log n)
    c_lineaire = 0.005   # O(n)
    
    courbe_constant = c_constant * np.ones_like(n)  # O(1)
    courbe_log = c_log * n * np.log2(n)             # O(n log n) pour insertion TAS
    courbe_lineaire = c_lineaire * n * n / n        # O(n) pour extraction TABLEAU
    
    return courbe_constant, courbe_log, courbe_lineaire

def creer_graphique_insertion(df):
    """Crée un graphique comparant les insertions"""
    plt.figure(figsize=(14, 8))
    
    # Calculer courbes théoriques
    n = np.array(df['Taille'])
    
    # Ajuster les constantes pour matcher les données
    if len(df) > 2:
        n0 = df['Taille'].iloc[2]
        # O(log n) pour TAS
        c_tas = df['Temps_Insertion_Tas'].iloc[2] / (n0 * np.log2(n0))
        # O(1) pour TABLEAU
        c_tab = df['Temps_Insertion_Tableau'].iloc[2]
    else:
        c_tas = 0.001
        c_tab = 0.001
    
    courbe_tas_theorique = c_tas * n * np.log2(n)
    courbe_tab_theorique = np.full_like(n, c_tab, dtype=float)
    
    # Tracer courbes théoriques (en pointillés)
    plt.plot(df['Taille'], courbe_tas_theorique, 
             ':', label='TAS O(log n) théorique', 
             color='lightgreen', linewidth=2.5, alpha=0.7)
    
    plt.plot(df['Taille'], courbe_tab_theorique, 
             ':', label='TABLEAU O(1) théorique', 
             color='lightcoral', linewidth=2.5, alpha=0.7)
    
    # Tracer courbes expérimentales
    plt.plot(df['Taille'], df['Temps_Insertion_Tas'], 
             'o-', label='TAS (File de priorité) - O(log n)', 
             color='green', linewidth=2, markersize=8)
    
    plt.plot(df['Taille'], df['Temps_Insertion_Tableau'], 
             's-', label='TABLEAU (non trié) - O(1)', 
             color='red', linewidth=2, markersize=8)
    
    # Ajouter valeurs sur quelques points
    step = max(1, len(df) // 5)
    for i in range(0, len(df), step):
        plt.text(df['Taille'].iloc[i], df['Temps_Insertion_Tas'].iloc[i], 
                f'{df["Temps_Insertion_Tas"].iloc[i]:.2f}',
                fontsize=9, color='green', ha='center', va='bottom')
        
        plt.text(df['Taille'].iloc[i], df['Temps_Insertion_Tableau'].iloc[i], 
                f'{df["Temps_Insertion_Tableau"].iloc[i]:.2f}',
                fontsize=9, color='red', ha='center', va='top')
    
    plt.xlabel('Taille (nombre d\'éléments)', fontsize=12)
    plt.ylabel('Temps (ms)', fontsize=12)
    plt.title('Comparaison des INSERTIONS\nFile de Priorité (TAS) vs Tableau Simple', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df['Taille'].max() * 1.05)
    max_temps = max(df['Temps_Insertion_Tas'].max(), df['Temps_Insertion_Tableau'].max())
    plt.ylim(0, max_temps * 1.2)
    
    plt.tight_layout()
    plt.savefig('graphique_insertion.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique insertion sauvegardé : graphique_insertion.png")

def creer_graphique_extraction(df):
    """Crée un graphique comparant les extractions"""
    plt.figure(figsize=(14, 8))
    
    # Calculer courbes théoriques
    n = np.array(df['Taille'])
    
    # Ajuster les constantes
    if len(df) > 2:
        n0 = df['Taille'].iloc[2]
        # O(log n) pour TAS
        c_tas = df['Temps_Extraction_Tas'].iloc[2] / (n0 * np.log2(n0))
        # O(n) pour TABLEAU
        c_tab = df['Temps_Extraction_Tableau'].iloc[2] / n0
    else:
        c_tas = 0.001
        c_tab = 0.001
    
    courbe_tas_theorique = c_tas * n * np.log2(n)
    courbe_tab_theorique = c_tab * n
    
    # Tracer courbes théoriques
    plt.plot(df['Taille'], courbe_tas_theorique, 
             ':', label='TAS O(log n) théorique', 
             color='lightgreen', linewidth=2.5, alpha=0.7)
    
    plt.plot(df['Taille'], courbe_tab_theorique, 
             ':', label='TABLEAU O(n) théorique', 
             color='lightcoral', linewidth=2.5, alpha=0.7)
    
    # Tracer courbes expérimentales
    plt.plot(df['Taille'], df['Temps_Extraction_Tas'], 
             'o-', label='TAS (File de priorité) - O(log n)', 
             color='green', linewidth=2, markersize=8)
    
    plt.plot(df['Taille'], df['Temps_Extraction_Tableau'], 
             's-', label='TABLEAU (non trié) - O(n)', 
             color='red', linewidth=2, markersize=8)
    
    # Ajouter valeurs sur quelques points
    step = max(1, len(df) // 5)
    for i in range(0, len(df), step):
        plt.text(df['Taille'].iloc[i], df['Temps_Extraction_Tas'].iloc[i], 
                f'{df["Temps_Extraction_Tas"].iloc[i]:.2f}',
                fontsize=9, color='green', ha='center', va='bottom')
        
        plt.text(df['Taille'].iloc[i], df['Temps_Extraction_Tableau'].iloc[i], 
                f'{df["Temps_Extraction_Tableau"].iloc[i]:.2f}',
                fontsize=9, color='red', ha='center', va='top')
    
    plt.xlabel('Taille (nombre d\'éléments)', fontsize=12)
    plt.ylabel('Temps (ms)', fontsize=12)
    plt.title('Comparaison des EXTRACTIONS\nFile de Priorité (TAS) vs Tableau Simple', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df['Taille'].max() * 1.05)
    max_temps = max(df['Temps_Extraction_Tas'].max(), df['Temps_Extraction_Tableau'].max())
    plt.ylim(0, max_temps * 1.1)
    
    plt.tight_layout()
    plt.savefig('graphique_extraction.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique extraction sauvegardé : graphique_extraction.png")

def creer_graphique_comparaison_complete(df):
    """Crée un graphique avec toutes les opérations"""
    plt.figure(figsize=(16, 10))
    
    # Insertion TAS
    plt.plot(df['Taille'], df['Temps_Insertion_Tas'], 
             'o-', label='TAS - Insertion O(log n)', 
             color='darkgreen', linewidth=2, markersize=7)
    
    # Extraction TAS
    plt.plot(df['Taille'], df['Temps_Extraction_Tas'], 
             's-', label='TAS - Extraction O(log n)', 
             color='green', linewidth=2, markersize=7)
    
    # Insertion TABLEAU
    plt.plot(df['Taille'], df['Temps_Insertion_Tableau'], 
             '^-', label='TABLEAU - Insertion O(1)', 
             color='darkred', linewidth=2, markersize=7)
    
    # Extraction TABLEAU
    plt.plot(df['Taille'], df['Temps_Extraction_Tableau'], 
             'v-', label='TABLEAU - Extraction O(n)', 
             color='red', linewidth=2, markersize=7)
    
    plt.xlabel('Taille (nombre d\'éléments)', fontsize=12)
    plt.ylabel('Temps (ms)', fontsize=12)
    plt.title('Comparaison COMPLÈTE : File de Priorité vs Tableau\n(Toutes opérations)', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df['Taille'].max() * 1.05)
    plt.ylim(0, df['Temps_Extraction_Tableau'].max() * 1.1)
    
    plt.tight_layout()
    plt.savefig('graphique_comparaison_complete.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique comparaison complète sauvegardé : graphique_comparaison_complete.png")

def creer_graphique_loglog(df):
    """Crée un graphique en échelle log-log"""
    plt.figure(figsize=(12, 8))
    
    plt.loglog(df['Taille'], df['Temps_Insertion_Tas'], 
               'o-', label='TAS - Insertion', 
               color='darkgreen', linewidth=2, markersize=8)
    
    plt.loglog(df['Taille'], df['Temps_Extraction_Tas'], 
               's-', label='TAS - Extraction', 
               color='green', linewidth=2, markersize=8)
    
    plt.loglog(df['Taille'], df['Temps_Insertion_Tableau'], 
               '^-', label='TABLEAU - Insertion', 
               color='darkred', linewidth=2, markersize=8)
    
    plt.loglog(df['Taille'], df['Temps_Extraction_Tableau'], 
               'v-', label='TABLEAU - Extraction', 
               color='red', linewidth=2, markersize=8)
    
    plt.xlabel('Taille (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Temps (ms)', fontsize=12, fontweight='bold')
    plt.title('Comparaison File de Priorité vs Tableau\n(Échelle log-log)', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3, which='both')
    
    plt.tight_layout()
    plt.savefig('graphique_loglog.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique log-log sauvegardé : graphique_loglog.png")

def afficher_statistiques(df):
    """Affiche des statistiques sur les performances"""
    print("\n" + "="*80)
    print("STATISTIQUES DE PERFORMANCE")
    print("="*80)
    
    derniere_ligne = df.iloc[-1]
    n = int(derniere_ligne['Taille'])
    
    print(f"\nPour n = {n} éléments :")
    print(f"\n  FILE DE PRIORITÉ (TAS) :")
    print(f"    • Insertion  : {derniere_ligne['Temps_Insertion_Tas']:.2f} ms")
    print(f"    • Extraction : {derniere_ligne['Temps_Extraction_Tas']:.2f} ms")
    print(f"    • Total      : {derniere_ligne['Temps_Insertion_Tas'] + derniere_ligne['Temps_Extraction_Tas']:.2f} ms")
    
    print(f"\n  TABLEAU SIMPLE :")
    print(f"    • Insertion  : {derniere_ligne['Temps_Insertion_Tableau']:.2f} ms")
    print(f"    • Extraction : {derniere_ligne['Temps_Extraction_Tableau']:.2f} ms")
    print(f"    • Total      : {derniere_ligne['Temps_Insertion_Tableau'] + derniere_ligne['Temps_Extraction_Tableau']:.2f} ms")
    
    # Comparaison
    ratio_insertion = derniere_ligne['Temps_Insertion_Tableau'] / derniere_ligne['Temps_Insertion_Tas'] if derniere_ligne['Temps_Insertion_Tas'] > 0 else 0
    ratio_extraction = derniere_ligne['Temps_Extraction_Tas'] / derniere_ligne['Temps_Extraction_Tableau'] if derniere_ligne['Temps_Extraction_Tableau'] > 0 else 0
    
    print(f"\n  COMPARAISON :")
    if ratio_insertion < 1:
        print(f"    • Insertion  : TABLEAU est {1/ratio_insertion:.1f}× plus RAPIDE")
    else:
        print(f"    • Insertion  : TAS est {ratio_insertion:.1f}× plus LENT")
    
    if ratio_extraction < 1:
        print(f"    • Extraction : TAS est {1/ratio_extraction:.1f}× plus RAPIDE ✓")
    else:
        print(f"    • Extraction : TABLEAU est {ratio_extraction:.1f}× plus LENT")
    
    # Vérifier croissance
    premiere_ligne = df.iloc[0]
    facteur_taille = derniere_ligne['Taille'] / premiere_ligne['Taille']
    
    facteur_ins_tas = derniere_ligne['Temps_Insertion_Tas'] / premiere_ligne['Temps_Insertion_Tas'] if premiere_ligne['Temps_Insertion_Tas'] > 0 else 0
    facteur_ext_tas = derniere_ligne['Temps_Extraction_Tas'] / premiere_ligne['Temps_Extraction_Tas'] if premiere_ligne['Temps_Extraction_Tas'] > 0 else 0
    facteur_ext_tab = derniere_ligne['Temps_Extraction_Tableau'] / premiere_ligne['Temps_Extraction_Tableau'] if premiere_ligne['Temps_Extraction_Tableau'] > 0 else 0
    
    print(f"\n  CROISSANCE (taille ×{facteur_taille:.0f}) :")
    print(f"    • TAS Insertion  : temps ×{facteur_ins_tas:.1f} (attendu O(log n))")
    print(f"    • TAS Extraction : temps ×{facteur_ext_tas:.1f} (attendu O(log n))")
    print(f"    • TAB Extraction : temps ×{facteur_ext_tab:.1f} (attendu ×{facteur_taille:.0f} pour O(n))")
    
    print("\n" + "="*80 + "\n")

def afficher_tableau_resultats(df):
    """Affiche un tableau des résultats"""
    print("\n" + "="*100)
    print("TABLEAU DES RÉSULTATS")
    print("="*100)
    print(f"{'Taille':>10} | {'TAS Ins (ms)':>15} | {'TAS Ext (ms)':>15} | {'TAB Ins (ms)':>15} | {'TAB Ext (ms)':>15}")
    print("-" * 100)
    
    for i in range(len(df)):
        print(f"{int(df['Taille'].iloc[i]):>10} | "
              f"{df['Temps_Insertion_Tas'].iloc[i]:>15.2f} | "
              f"{df['Temps_Extraction_Tas'].iloc[i]:>15.2f} | "
              f"{df['Temps_Insertion_Tableau'].iloc[i]:>15.2f} | "
              f"{df['Temps_Extraction_Tableau'].iloc[i]:>15.2f}")
    
    print("="*100 + "\n")

def main():
    print("\n" + "="*80)
    print("GÉNÉRATION DES GRAPHIQUES - FILES DE PRIORITÉ vs TABLEAU")
    print("="*80 + "\n")
    
    # Charger données
    df = charger_donnees()
    
    # Afficher tableau
    afficher_tableau_resultats(df)
    
    # Afficher statistiques
    afficher_statistiques(df)
    
    # Créer graphiques
    print("Génération des graphiques...")
    creer_graphique_insertion(df)
    creer_graphique_extraction(df)
    creer_graphique_comparaison_complete(df)
    creer_graphique_loglog(df)
    
    print("\n✓ Tous les graphiques ont été générés avec succès !")
    print("\nFichiers créés :")
    print("  - graphique_insertion.png : Comparaison des insertions")
    print("  - graphique_extraction.png : Comparaison des extractions")
    print("  - graphique_comparaison_complete.png : Toutes opérations sur un graphe")
    print("  - graphique_loglog.png : Échelle log-log")
    
    print("\n" + "="*80)
    print("ANALYSE THÉORIQUE")
    print("="*80)
    print("FILE DE PRIORITÉ (TAS) :")
    print("  • Insertion  : O(log n)")
    print("  • Extraction : O(log n)")
    print("\nTABLEAU SIMPLE (non trié) :")
    print("  • Insertion  : O(1) - Rapide !")
    print("  • Extraction : O(n) - Lent (recherche linéaire)")
    print("\nCONCLUSION :")
    print("  Le TAS est optimal pour les extractions répétées du maximum.")
    print("  Le TABLEAU est très rapide pour l'insertion mais inefficace pour l'extraction.")
    print("="*80 + "\n")

if __name__ == "__main__":
    main()
