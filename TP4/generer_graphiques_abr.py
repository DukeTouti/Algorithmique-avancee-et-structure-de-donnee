#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison des méthodes d'insertion dans les ABR
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_abr.csv'):
    """Charge les données depuis le fichier CSV"""
    if not os.path.exists(nom_fichier):
        print(f"✗ Erreur : Le fichier {nom_fichier} n'existe pas.")
        print(f"   Exécutez d'abord : ./abr")
        sys.exit(1)
    
    try:
        df = pd.read_csv(nom_fichier)
        # Nettoyer les noms de colonnes (enlever les espaces)
        df.columns = df.columns.str.strip()
        # Nettoyer les valeurs de la colonne Type
        df['Type'] = df['Type'].str.strip()
        print(f"✓ Données chargées : {len(df)} points de mesure")
        return df
    except Exception as e:
        print(f"✗ Erreur lors de la lecture du fichier : {e}")
        sys.exit(1)

def creer_graphique_hauteur(df, type_donnees):
    """Crée un graphique comparant les hauteurs des arbres"""
    df_type = df[df['Type'] == type_donnees]
    
    if len(df_type) == 0:
        print(f"⚠️  Aucune donnée pour le type : {type_donnees}")
        return
    
    plt.figure(figsize=(14, 8))
    
    # Tracer les hauteurs
    plt.plot(df_type['Taille'], df_type['Hauteur_Equilibre'], 
             'o-', label='Arbre équilibré', 
             color='green', linewidth=2, markersize=8)
    
    plt.plot(df_type['Taille'], df_type['Hauteur_Sequentiel'], 
             's-', label='Arbre séquentiel (déséquilibré)', 
             color='red', linewidth=2, markersize=8)
    
    # Courbes théoriques
    n = np.array(df_type['Taille'])
    plt.plot(n, np.log2(n + 1), 
             ':', label='O(log n) théorique', 
             color='lightgreen', linewidth=2.5, alpha=0.7)
    
    plt.plot(n, n, 
             ':', label='O(n) théorique (pire cas)', 
             color='lightcoral', linewidth=2.5, alpha=0.7)
    
    plt.xlabel('Nombre d\'éléments (n)', fontsize=12)
    plt.ylabel('Hauteur de l\'arbre', fontsize=12)
    plt.title(f'Comparaison des hauteurs : Arbre équilibré vs déséquilibré\n(Données {type_donnees})', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df_type['Taille'].max() * 1.05)
    plt.ylim(0, df_type['Hauteur_Sequentiel'].max() * 1.1)
    
    plt.tight_layout()
    nom_fichier = f'graphique_hauteur_{type_donnees}.png'
    plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
    print(f"✓ Graphique sauvegardé : {nom_fichier}")

def creer_graphique_temps_insertion(df, type_donnees):
    """Crée un graphique des temps d'insertion"""
    df_type = df[df['Type'] == type_donnees]
    
    if len(df_type) == 0:
        return
    
    plt.figure(figsize=(14, 8))
    
    plt.plot(df_type['Taille'], df_type['Temps_Insertion_Equilibre'], 
             'o-', label='Insertion équilibrée', 
             color='green', linewidth=2, markersize=8)
    
    plt.plot(df_type['Taille'], df_type['Temps_Insertion_Sequentiel'], 
             's-', label='Insertion séquentielle', 
             color='red', linewidth=2, markersize=8)
    
    # Ajouter les valeurs sur quelques points clés
    step = max(1, len(df_type) // 5)
    for i in range(0, len(df_type), step):
        plt.text(df_type['Taille'].iloc[i], df_type['Temps_Insertion_Equilibre'].iloc[i], 
                f'{int(df_type["Temps_Insertion_Equilibre"].iloc[i])}',
                fontsize=9, color='green', ha='center', va='bottom')
        
        plt.text(df_type['Taille'].iloc[i], df_type['Temps_Insertion_Sequentiel'].iloc[i], 
                f'{int(df_type["Temps_Insertion_Sequentiel"].iloc[i])}',
                fontsize=9, color='red', ha='center', va='top')
    
    plt.xlabel('Nombre d\'éléments (n)', fontsize=12)
    plt.ylabel('Temps d\'insertion (microsecondes)', fontsize=12)
    plt.title(f'Temps d\'insertion : Arbre équilibré vs déséquilibré\n(Données {type_donnees})', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df_type['Taille'].max() * 1.05)
    plt.ylim(0, df_type['Temps_Insertion_Sequentiel'].max() * 1.1)
    
    plt.tight_layout()
    nom_fichier = f'graphique_insertion_{type_donnees}.png'
    plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
    print(f"✓ Graphique sauvegardé : {nom_fichier}")

def creer_graphique_temps_recherche(df, type_donnees):
    """Crée un graphique des temps de recherche"""
    df_type = df[df['Type'] == type_donnees]
    
    if len(df_type) == 0:
        return
    
    plt.figure(figsize=(14, 8))
    
    plt.plot(df_type['Taille'], df_type['Temps_Recherche_Equilibre'], 
             'o-', label='Recherche (arbre équilibré)', 
             color='blue', linewidth=2, markersize=8)
    
    plt.plot(df_type['Taille'], df_type['Temps_Recherche_Sequentiel'], 
             's-', label='Recherche (arbre déséquilibré)', 
             color='orange', linewidth=2, markersize=8)
    
    plt.xlabel('Nombre d\'éléments (n)', fontsize=12)
    plt.ylabel('Temps de recherche (microsecondes)', fontsize=12)
    plt.title(f'Temps de recherche : Arbre équilibré vs déséquilibré\n(Données {type_donnees})', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df_type['Taille'].max() * 1.05)
    plt.ylim(0, df_type['Temps_Recherche_Sequentiel'].max() * 1.1)
    
    plt.tight_layout()
    nom_fichier = f'graphique_recherche_{type_donnees}.png'
    plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
    print(f"✓ Graphique sauvegardé : {nom_fichier}")

def creer_graphique_comparaison_complete(df):
    """Crée un graphique comparant tous les types"""
    plt.figure(figsize=(16, 10))
    
    types = df['Type'].unique()
    colors_eq = {'aleatoire': 'green', 'croissant': 'darkgreen', 'decroissant': 'lime'}
    colors_seq = {'aleatoire': 'red', 'croissant': 'darkred', 'decroissant': 'orange'}
    markers = {'aleatoire': 'o', 'croissant': 's', 'decroissant': '^'}
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        # Insertion équilibrée
        plt.plot(df_type['Taille'], df_type['Temps_Insertion_Equilibre'], 
                 marker=markers[type_donnees], linestyle='-',
                 label=f'Équilibré - {type_donnees}', 
                 color=colors_eq[type_donnees], linewidth=2, markersize=7)
        
        # Insertion séquentielle
        plt.plot(df_type['Taille'], df_type['Temps_Insertion_Sequentiel'], 
                 marker=markers[type_donnees], linestyle='--',
                 label=f'Séquentiel - {type_donnees}', 
                 color=colors_seq[type_donnees], linewidth=2, markersize=7)
    
    plt.xlabel('Nombre d\'éléments (n)', fontsize=12)
    plt.ylabel('Temps d\'insertion (microsecondes)', fontsize=12)
    plt.title('Comparaison des temps d\'insertion pour tous types de données', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=9, loc='upper left', ncol=2)
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df['Taille'].max() * 1.05)
    
    plt.tight_layout()
    plt.savefig('graphique_comparaison_complete.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique de comparaison complète sauvegardé : graphique_comparaison_complete.png")

def creer_graphique_loglog(df):
    """Crée des graphiques en échelle log-log"""
    types = df['Type'].unique()
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        if len(df_type) == 0:
            continue
        
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
        
        # Hauteur en log-log
        ax1.loglog(df_type['Taille'], df_type['Hauteur_Equilibre'], 
                   'o-', label='Équilibré', color='green', linewidth=2, markersize=8)
        ax1.loglog(df_type['Taille'], df_type['Hauteur_Sequentiel'], 
                   's-', label='Séquentiel', color='red', linewidth=2, markersize=8)
        ax1.set_xlabel('Taille (n)', fontsize=11, fontweight='bold')
        ax1.set_ylabel('Hauteur', fontsize=11, fontweight='bold')
        ax1.set_title(f'Hauteur (échelle log-log)', fontsize=12, fontweight='bold')
        ax1.legend(fontsize=10)
        ax1.grid(True, alpha=0.3, which='both')
        
        # Temps recherche en log-log
        ax2.loglog(df_type['Taille'], df_type['Temps_Recherche_Equilibre'], 
                   'o-', label='Équilibré', color='blue', linewidth=2, markersize=8)
        ax2.loglog(df_type['Taille'], df_type['Temps_Recherche_Sequentiel'], 
                   's-', label='Séquentiel', color='orange', linewidth=2, markersize=8)
        ax2.set_xlabel('Taille (n)', fontsize=11, fontweight='bold')
        ax2.set_ylabel('Temps recherche (µs)', fontsize=11, fontweight='bold')
        ax2.set_title(f'Temps de recherche (échelle log-log)', fontsize=12, fontweight='bold')
        ax2.legend(fontsize=10)
        ax2.grid(True, alpha=0.3, which='both')
        
        plt.suptitle(f'Analyse log-log - Données {type_donnees}', fontsize=14, fontweight='bold')
        plt.tight_layout()
        
        nom_fichier = f'graphique_loglog_{type_donnees}.png'
        plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
        print(f"✓ Graphique log-log sauvegardé : {nom_fichier}")

def afficher_statistiques(df):
    """Affiche des statistiques sur les performances"""
    print("\n" + "="*90)
    print("STATISTIQUES DE PERFORMANCE")
    print("="*90)
    
    types = df['Type'].unique()
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        if len(df_type) == 0:
            continue
        
        print(f"\n--- Type de données : {type_donnees.upper()} ---")
        
        # Performance pour la plus grande taille
        derniere_ligne = df_type.iloc[-1]
        print(f"\nPour n = {int(derniere_ligne['Taille'])} éléments :")
        print(f"  Hauteur équilibré : {int(derniere_ligne['Hauteur_Equilibre'])}")
        print(f"  Hauteur séquentiel : {int(derniere_ligne['Hauteur_Sequentiel'])}")
        print(f"  Ratio hauteur : {derniere_ligne['Hauteur_Sequentiel'] / derniere_ligne['Hauteur_Equilibre']:.1f}×")
        
        print(f"\n  Temps insertion équilibré : {derniere_ligne['Temps_Insertion_Equilibre']:.2f} µs")
        print(f"  Temps insertion séquentiel : {derniere_ligne['Temps_Insertion_Sequentiel']:.2f} µs")
        ratio_insertion = derniere_ligne['Temps_Insertion_Sequentiel'] / derniere_ligne['Temps_Insertion_Equilibre']
        print(f"  → L'arbre équilibré est {ratio_insertion:.1f}× plus rapide en insertion")
        
        print(f"\n  Temps recherche équilibré : {derniere_ligne['Temps_Recherche_Equilibre']:.2f} µs")
        print(f"  Temps recherche séquentiel : {derniere_ligne['Temps_Recherche_Sequentiel']:.2f} µs")
        ratio_recherche = derniere_ligne['Temps_Recherche_Sequentiel'] / derniere_ligne['Temps_Recherche_Equilibre']
        print(f"  → L'arbre équilibré est {ratio_recherche:.1f}× plus rapide en recherche")
        
        # Vérification de la complexité
        premiere_ligne = df_type.iloc[0]
        facteur_n = derniere_ligne['Taille'] / premiere_ligne['Taille']
        facteur_h_eq = derniere_ligne['Hauteur_Equilibre'] / premiere_ligne['Hauteur_Equilibre']
        facteur_h_seq = derniere_ligne['Hauteur_Sequentiel'] / premiere_ligne['Hauteur_Sequentiel']
        
        print(f"\nCroissance observée (n ×{facteur_n:.0f}) :")
        print(f"  Hauteur équilibré : ×{facteur_h_eq:.1f} (attendu ≈ ×{np.log2(derniere_ligne['Taille']) / np.log2(premiere_ligne['Taille']):.1f} pour O(log n))")
        print(f"  Hauteur séquentiel : ×{facteur_h_seq:.1f} (attendu ≈ ×{facteur_n:.0f} pour O(n))")
    
    print("\n" + "="*90 + "\n")

def afficher_tableau_resultats(df):
    """Affiche un tableau des résultats"""
    print("\n" + "="*120)
    print("TABLEAU DES RÉSULTATS")
    print("="*120)
    print(f"{'Taille':>8} | {'Type':>12} | {'H_Eq':>5} | {'H_Seq':>6} | {'T_Ins_Eq':>10} | {'T_Ins_Seq':>11} | {'T_Rech_Eq':>11} | {'T_Rech_Seq':>12}")
    print("-" * 120)
    
    for i in range(len(df)):
        print(f"{int(df['Taille'].iloc[i]):>8} | {df['Type'].iloc[i]:>12} | "
              f"{int(df['Hauteur_Equilibre'].iloc[i]):>5} | {int(df['Hauteur_Sequentiel'].iloc[i]):>6} | "
              f"{df['Temps_Insertion_Equilibre'].iloc[i]:>10.2f} | {df['Temps_Insertion_Sequentiel'].iloc[i]:>11.2f} | "
              f"{df['Temps_Recherche_Equilibre'].iloc[i]:>11.2f} | {df['Temps_Recherche_Sequentiel'].iloc[i]:>12.2f}")
    
    print("="*120 + "\n")

def main():
    print("\n" + "="*90)
    print("GÉNÉRATION DES GRAPHIQUES - ARBRES BINAIRES DE RECHERCHE")
    print("="*90 + "\n")
    
    # Charger les données
    df = charger_donnees()
    
    # Afficher tableau
    afficher_tableau_resultats(df)
    
    # Afficher statistiques
    afficher_statistiques(df)
    
    # Créer les graphiques
    print("Génération des graphiques...")
    
    types = df['Type'].unique()
    for type_donnees in types:
        creer_graphique_hauteur(df, type_donnees)
        creer_graphique_temps_insertion(df, type_donnees)
        creer_graphique_temps_recherche(df, type_donnees)
    
    creer_graphique_comparaison_complete(df)
    creer_graphique_loglog(df)
    
    print("\n✓ Tous les graphiques ont été générés avec succès !")
    print("\nFichiers créés :")
    for type_donnees in types:
        print(f"  - graphique_hauteur_{type_donnees}.png")
        print(f"  - graphique_insertion_{type_donnees}.png")
        print(f"  - graphique_recherche_{type_donnees}.png")
        print(f"  - graphique_loglog_{type_donnees}.png")
    print(f"  - graphique_comparaison_complete.png")
    
    print("\n" + "="*90)
    print("ANALYSE THÉORIQUE")
    print("="*90)
    print("Arbre équilibré :")
    print("  - Hauteur : O(log n)")
    print("  - Insertion : O(log n)")
    print("  - Recherche : O(log n)")
    print("\nArbre déséquilibré (pire cas) :")
    print("  - Hauteur : O(n)")
    print("  - Insertion : O(n)")
    print("  - Recherche : O(n)")
    print("\nL'équilibrage améliore drastiquement les performances !")
    print("="*90 + "\n")

if __name__ == "__main__":
    main()
