#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison des algorithmes de tri
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_tri.csv'):
    """Charge les données depuis le fichier CSV"""
    if not os.path.exists(nom_fichier):
        print(f"❌ Erreur : Le fichier {nom_fichier} n'existe pas.")
        print(f"   Exécutez d'abord : ./test_tri")
        sys.exit(1)
    
    try:
        df = pd.read_csv(nom_fichier)
        print(f"✓ Données chargées : {len(df)} points de mesure")
        return df
    except Exception as e:
        print(f"❌ Erreur lors de la lecture du fichier : {e}")
        sys.exit(1)

def calculer_courbes_theoriques(tailles):
    """Calcule les courbes théoriques O(n²) et O(n log n)"""
    n = np.array(tailles)
    
    # Normalisation pour que les courbes soient visibles
    c1 = 1e-8  # Constante pour O(n²)
    c2 = 1e-7  # Constante pour O(n log n)
    
    courbe_n2 = c1 * n * n
    courbe_nlogn = c2 * n * np.log2(n)
    
    return courbe_n2, courbe_nlogn

def creer_graphique_loglog(df):
    """Crée un graphique en échelle log-log"""
    plt.figure(figsize=(12, 8))
    
    # Données expérimentales
    plt.loglog(df['Taille'], df['Temps_Insertion'], 
               'o-', label='Tri par insertion (expérimental)', 
               color='#e74c3c', linewidth=2, markersize=8)
    plt.loglog(df['Taille'], df['Temps_Fusion'], 
               's-', label='Tri par fusion (expérimental)', 
               color='#3498db', linewidth=2, markersize=8)
    
    # Courbes théoriques
    courbe_n2, courbe_nlogn = calculer_courbes_theoriques(df['Taille'])
    plt.loglog(df['Taille'], courbe_n2, 
               '--', label='O(n²) théorique', 
               color='#e74c3c', alpha=0.5, linewidth=2)
    plt.loglog(df['Taille'], courbe_nlogn, 
               '--', label='O(n log n) théorique', 
               color='#3498db', alpha=0.5, linewidth=2)
    
    plt.xlabel('Taille du tableau (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Temps d\'exécution (secondes)', fontsize=12, fontweight='bold')
    plt.title('Comparaison des algorithmes de tri\n(échelle logarithmique)', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3, which='both')
    
    plt.tight_layout()
    plt.savefig('graphique_tri_loglog.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique log-log sauvegardé : graphique_tri_loglog.png")

def creer_graphique_lineaire(df):
    """Crée un graphique en échelle linéaire (zoom sur petites tailles)"""
    # Filtrer pour n <= 10000 pour mieux voir les petites tailles
    df_zoom = df[df['Taille'] <= 10000]
    
    if len(df_zoom) == 0:
        print("⚠ Pas assez de données pour le graphique linéaire")
        return
    
    plt.figure(figsize=(12, 8))
    
    plt.plot(df_zoom['Taille'], df_zoom['Temps_Insertion'], 
             'o-', label='Tri par insertion', 
             color='#e74c3c', linewidth=2, markersize=8)
    plt.plot(df_zoom['Taille'], df_zoom['Temps_Fusion'], 
             's-', label='Tri par fusion', 
             color='#3498db', linewidth=2, markersize=8)
    
    plt.xlabel('Taille du tableau (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Temps d\'exécution (secondes)', fontsize=12, fontweight='bold')
    plt.title('Comparaison des algorithmes de tri\n(échelle linéaire - petites tailles)', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('graphique_tri_lineaire.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique linéaire sauvegardé : graphique_tri_lineaire.png")

def creer_graphique_ratio(df):
    """Crée un graphique du ratio insertion/fusion"""
    plt.figure(figsize=(12, 6))
    
    plt.semilogx(df['Taille'], df['Ratio'], 
                 'o-', color='#9b59b6', linewidth=2, markersize=8)
    plt.axhline(y=1, color='gray', linestyle='--', alpha=0.7, 
                label='Performances égales')
    
    plt.xlabel('Taille du tableau (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Ratio (Temps Insertion / Temps Fusion)', fontsize=12, fontweight='bold')
    plt.title('Ratio de performance : Tri par insertion / Tri par fusion', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    
    # Annotation du point de croisement approximatif
    point_croisement = df[df['Ratio'] >= 1].iloc[0] if any(df['Ratio'] >= 1) else None
    if point_croisement is not None:
        plt.annotate(f'Point de croisement\n≈ n = {int(point_croisement["Taille"])}',
                    xy=(point_croisement['Taille'], point_croisement['Ratio']),
                    xytext=(point_croisement['Taille']*2, point_croisement['Ratio']*2),
                    arrowprops=dict(arrowstyle='->', color='red', lw=1.5),
                    fontsize=10, color='red')
    
    plt.tight_layout()
    plt.savefig('graphique_ratio.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique du ratio sauvegardé : graphique_ratio.png")

def afficher_statistiques(df):
    """Affiche des statistiques sur les performances"""
    print("\n" + "="*60)
    print("STATISTIQUES DE PERFORMANCE")
    print("="*60)
    
    # Ratio moyen
    ratio_moyen = df['Ratio'].mean()
    print(f"Ratio moyen insertion/fusion : {ratio_moyen:.2f}×")
    
    # Performance pour la plus grande taille
    derniere_ligne = df.iloc[-1]
    print(f"\nPour n = {int(derniere_ligne['Taille'])} :")
    print(f"  - Tri par insertion : {derniere_ligne['Temps_Insertion']:.6f} s")
    print(f"  - Tri par fusion    : {derniere_ligne['Temps_Fusion']:.6f} s")
    print(f"  - Le tri par fusion est {derniere_ligne['Ratio']:.1f}× plus rapide")
    
    # Point de croisement
    point_croisement = df[df['Ratio'] >= 1]
    if len(point_croisement) > 0:
        n_croisement = point_croisement.iloc[0]['Taille']
        print(f"\nPoint de croisement : n ≈ {int(n_croisement)}")
        print(f"  → Pour n < {int(n_croisement)}, le tri par insertion peut être compétitif")
        print(f"  → Pour n > {int(n_croisement)}, le tri par fusion devient nettement plus rapide")
    
    print("="*60 + "\n")

def main():
    print("\n" + "="*60)
    print("GÉNÉRATION DES GRAPHIQUES DE COMPARAISON")
    print("="*60 + "\n")
    
    # Charger les données
    df = charger_donnees()
    
    # Afficher statistiques
    afficher_statistiques(df)
    
    # Créer les graphiques
    print("Génération des graphiques...")
    creer_graphique_loglog(df)
    creer_graphique_lineaire(df)
    creer_graphique_ratio(df)
    
    print("\n✓ Tous les graphiques ont été générés avec succès !")
    print("\nFichiers créés :")
    print("  - graphique_tri_loglog.png    : Comparaison en échelle log-log")
    print("  - graphique_tri_lineaire.png  : Zoom sur les petites tailles")
    print("  - graphique_ratio.png         : Évolution du ratio de performance")
    print()

if __name__ == "__main__":
    main()
