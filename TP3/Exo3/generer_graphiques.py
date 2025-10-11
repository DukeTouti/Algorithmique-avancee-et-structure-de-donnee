#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison des algorithmes de tri
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_temps.csv'):
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

def calculer_courbes_theoriques(tailles, temps_insertion, temps_fusion):
    """Calcule les courbes théoriques O(n²) et O(n log n)"""
    n = np.array(tailles)
    
    # Ajuster les constantes pour que les courbes théoriques matchent les données expérimentales
    # On utilise les premières valeurs pour calibrer
    n0 = tailles.iloc[2]  # Utiliser la 3ème valeur pour calibrer
    
    # Constante pour O(n²) basée sur le tri par insertion
    c_n2 = temps_insertion.iloc[2] / (n0 * n0)
    courbe_n2 = c_n2 * n * n
    
    # Constante pour O(n log n) basée sur le tri par fusion
    c_nlogn = temps_fusion.iloc[2] / (n0 * np.log2(n0))
    courbe_nlogn = c_nlogn * n * np.log2(n)
    
    return courbe_n2, courbe_nlogn

def creer_graphique_comparaison(df):
    """Crée un graphique de comparaison simple comme dans le CR"""
    plt.figure(figsize=(14, 8))
    
    # Calculer les courbes théoriques
    courbe_n2, courbe_nlogn = calculer_courbes_theoriques(df['Taille'], df['Temps_Insertion'], df['Temps_Fusion'])
    
    # Tracer les courbes théoriques en premier (en arrière-plan)
    plt.plot(df['Taille'], courbe_n2, 
             ':', label='O(n²) théorique', 
             color='lightblue', linewidth=2.5, alpha=0.7)
    
    plt.plot(df['Taille'], courbe_nlogn, 
             ':', label='O(n log n) théorique', 
             color='lightcoral', linewidth=2.5, alpha=0.7)
    
    # Tracer les courbes expérimentales par-dessus
    plt.plot(df['Taille'], df['Temps_Insertion'], 
             'x--', label='Temps_Insertion (expérimental)', 
             color='blue', linewidth=2, markersize=10)
    
    plt.plot(df['Taille'], df['Temps_Fusion'], 
             'x--', label='Temps_Fusion (expérimental)', 
             color='red', linewidth=2, markersize=10)
    
    # Ajouter les valeurs sur les points
    for i in range(len(df)):
        # Valeurs pour insertion (en bleu)
        plt.text(df['Taille'].iloc[i], df['Temps_Insertion'].iloc[i], 
                f'{int(df["Temps_Insertion"].iloc[i])}',
                fontsize=9, color='blue', ha='center', va='bottom')
        
        # Valeurs pour fusion (en rouge)
        plt.text(df['Taille'].iloc[i], df['Temps_Fusion'].iloc[i], 
                f'{int(df["Temps_Fusion"].iloc[i])}',
                fontsize=9, color='red', ha='center', va='top')
    
    plt.xlabel('Taille du Tableau de valeurs (en nombres de valeurs)', fontsize=12)
    plt.ylabel('Temps (en micro secondes)', fontsize=12)
    plt.title('Graphe de comparaison entre Tri par Insertion et Tri par Fusion', fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3)
    
    # Forcer les axes à commencer à (0, 0)
    plt.xlim(0, df['Taille'].max() * 1.05)
    plt.ylim(0, df['Temps_Insertion'].max() * 1.1)
    
    # Format scientifique pour l'axe X si nécessaire
    plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
    
    plt.tight_layout()
    plt.savefig('graphique_comparaison.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique de comparaison sauvegardé : graphique_comparaison.png")

def creer_graphique_loglog(df):
    """Crée un graphique en échelle log-log"""
    plt.figure(figsize=(12, 8))
    
    plt.loglog(df['Taille'], df['Temps_Insertion'], 
               'o-', label='Tri par Insertion', 
               color='blue', linewidth=2, markersize=8)
    
    plt.loglog(df['Taille'], df['Temps_Fusion'], 
               's-', label='Tri par Fusion', 
               color='red', linewidth=2, markersize=8)
    
    plt.xlabel('Taille (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Temps (µs)', fontsize=12, fontweight='bold')
    plt.title('Comparaison des algorithmes de tri (échelle log-log)', fontsize=14, fontweight='bold')
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3, which='both')
    
    plt.tight_layout()
    plt.savefig('graphique_loglog.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique log-log sauvegardé : graphique_loglog.png")

def afficher_statistiques(df):
    """Affiche des statistiques sur les performances"""
    print("\n" + "="*60)
    print("STATISTIQUES DE PERFORMANCE")
    print("="*60)
    
    # Performance pour la plus grande taille
    derniere_ligne = df.iloc[-1]
    print(f"\nPour n = {int(derniere_ligne['Taille'])} :")
    print(f"  - Tri par insertion : {derniere_ligne['Temps_Insertion']:.2f} µs")
    print(f"  - Tri par fusion    : {derniere_ligne['Temps_Fusion']:.2f} µs")
    
    if 'Ratio' in df.columns:
        print(f"  - Le tri par fusion est {derniere_ligne['Ratio']:.1f}× plus rapide")
        
        # Point de croisement
        point_croisement = df[df['Ratio'] >= 1]
        if len(point_croisement) > 0:
            n_croisement = point_croisement.iloc[0]['Taille']
            print(f"\nPoint de croisement : n ≈ {int(n_croisement)}")
    
    print("="*60 + "\n")

def afficher_tableau_resultats(df):
    """Affiche un tableau des résultats"""
    print("\n" + "="*60)
    print("TABLEAU DES RÉSULTATS")
    print("="*60)
    print(f"{'Taille':>10} | {'Temps Insertion (µs)':>20} | {'Temps Fusion (µs)':>18}")
    print("-" * 60)
    for i in range(len(df)):
        print(f"{int(df['Taille'].iloc[i]):>10} | {df['Temps_Insertion'].iloc[i]:>20.2f} | {df['Temps_Fusion'].iloc[i]:>18.2f}")
    print("="*60 + "\n")

def main():
    print("\n" + "="*60)
    print("GÉNÉRATION DES GRAPHIQUES DE COMPARAISON")
    print("="*60 + "\n")
    
    # Charger les données
    df = charger_donnees()
    
    # Afficher tableau
    afficher_tableau_resultats(df)
    
    # Afficher statistiques
    afficher_statistiques(df)
    
    # Créer les graphiques
    print("Génération des graphiques...")
    creer_graphique_comparaison(df)
    creer_graphique_loglog(df)
    
    print("\n✓ Tous les graphiques ont été générés avec succès !")
    print("\nFichiers créés :")
    print("  - graphique_comparaison.png : Graphique style CR (principal)")
    print("  - graphique_loglog.png      : Graphique échelle logarithmique")
    print()

if __name__ == "__main__":
    main()
