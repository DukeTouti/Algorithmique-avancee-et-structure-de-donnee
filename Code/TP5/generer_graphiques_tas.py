#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison des méthodes de construction de tas
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_tas.csv'):
    """Charge les données depuis le fichier CSV"""
    if not os.path.exists(nom_fichier):
        print(f"❌ Erreur : Le fichier {nom_fichier} n'existe pas.")
        print(f"   Exécutez d'abord : ./main")
        sys.exit(1)
    
    try:
        df = pd.read_csv(nom_fichier)
        # Nettoyer les noms de colonnes (enlever les espaces)
        df.columns = df.columns.str.strip()
        # Nettoyer les valeurs de la colonne Type (enlever les espaces)
        df['Type'] = df['Type'].str.strip()
        print(f"✓ Données chargées : {len(df)} points de mesure")
        return df
    except Exception as e:
        print(f"❌ Erreur lors de la lecture du fichier : {e}")
        sys.exit(1)

def calculer_courbes_theoriques(tailles, temps_direct, temps_insertion):
    """Calcule les courbes théoriques O(n) et O(n log n)"""
    n = np.array(tailles)
    
    # Ajuster les constantes pour que les courbes théoriques matchent les données expérimentales
    # On utilise les premières valeurs pour calibrer
    n0 = tailles.iloc[2] if len(tailles) > 2 else tailles.iloc[0]
    
    # Constante pour O(n) basée sur la construction directe
    c_n = temps_direct.iloc[2] / n0 if len(temps_direct) > 2 else temps_direct.iloc[0] / n0
    courbe_n = c_n * n
    
    # Constante pour O(n log n) basée sur la construction par insertion
    c_nlogn = temps_insertion.iloc[2] / (n0 * np.log2(n0)) if len(temps_insertion) > 2 else temps_insertion.iloc[0] / (n0 * np.log2(n0))
    courbe_nlogn = c_nlogn * n * np.log2(n)
    
    return courbe_n, courbe_nlogn

def creer_graphique_par_type(df, type_donnees):
    """Crée un graphique de comparaison pour un type de données spécifique"""
    df_type = df[df['Type'] == type_donnees]
    
    if len(df_type) == 0:
        print(f"⚠️  Aucune donnée pour le type : {type_donnees}")
        return
    
    plt.figure(figsize=(14, 8))
    
    # Calculer les courbes théoriques
    courbe_n, courbe_nlogn = calculer_courbes_theoriques(
        df_type['Taille'], 
        df_type['Temps_Direct'], 
        df_type['Temps_Insertion']
    )
    
    # Tracer les courbes théoriques en premier (en arrière-plan)
    plt.plot(df_type['Taille'], courbe_n, 
             ':', label='O(n) théorique', 
             color='lightcoral', linewidth=2.5, alpha=0.7)
    
    plt.plot(df_type['Taille'], courbe_nlogn, 
             ':', label='O(n log n) théorique', 
             color='lightblue', linewidth=2.5, alpha=0.7)
    
    # Tracer les courbes expérimentales par-dessus
    plt.plot(df_type['Taille'], df_type['Temps_Direct'], 
             'o-', label='Construction Directe - O(n)', 
             color='red', linewidth=2, markersize=8)
    
    plt.plot(df_type['Taille'], df_type['Temps_Insertion'], 
             's-', label='Construction Insertion - O(n log n)', 
             color='blue', linewidth=2, markersize=8)
    
    # Ajouter les valeurs sur quelques points clés
    step = max(1, len(df_type) // 5)  # Afficher environ 5 valeurs
    for i in range(0, len(df_type), step):
        # Valeurs pour direct (en rouge)
        plt.text(df_type['Taille'].iloc[i], df_type['Temps_Direct'].iloc[i], 
                f'{int(df_type["Temps_Direct"].iloc[i])}',
                fontsize=9, color='red', ha='center', va='bottom')
        
        # Valeurs pour insertion (en bleu)
        plt.text(df_type['Taille'].iloc[i], df_type['Temps_Insertion'].iloc[i], 
                f'{int(df_type["Temps_Insertion"].iloc[i])}',
                fontsize=9, color='blue', ha='center', va='top')
    
    plt.xlabel('Taille du tas (nombre d\'éléments)', fontsize=12)
    plt.ylabel('Temps (en microsecondes)', fontsize=12)
    plt.title(f'Comparaison des méthodes de construction de Tas Max\n(Données {type_donnees})', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=10, loc='upper left')
    plt.grid(True, alpha=0.3)
    
    # Forcer les axes à commencer à (0, 0)
    plt.xlim(0, df_type['Taille'].max() * 1.05)
    plt.ylim(0, df_type['Temps_Insertion'].max() * 1.1)
    
    # Format scientifique pour l'axe X si nécessaire
    plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
    
    plt.tight_layout()
    nom_fichier = f'graphique_tas_{type_donnees}.png'
    plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
    print(f"✓ Graphique sauvegardé : {nom_fichier}")

def creer_graphique_comparaison_tous_types(df):
    """Crée un graphique comparant tous les types de données sur le même graphe"""
    plt.figure(figsize=(16, 10))
    
    types = df['Type'].unique()
    colors_direct = {'aleatoire': 'red', 'croissant': 'darkred', 'decroissant': 'orange'}
    colors_insertion = {'aleatoire': 'blue', 'croissant': 'darkblue', 'decroissant': 'cyan'}
    markers_direct = {'aleatoire': 'o', 'croissant': 's', 'decroissant': '^'}
    markers_insertion = {'aleatoire': 'x', 'croissant': '+', 'decroissant': '*'}
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        # Construction directe
        plt.plot(df_type['Taille'], df_type['Temps_Direct'], 
                 marker=markers_direct[type_donnees], linestyle='-',
                 label=f'Direct - {type_donnees}', 
                 color=colors_direct[type_donnees], linewidth=2, markersize=7)
        
        # Construction insertion
        plt.plot(df_type['Taille'], df_type['Temps_Insertion'], 
                 marker=markers_insertion[type_donnees], linestyle='--',
                 label=f'Insertion - {type_donnees}', 
                 color=colors_insertion[type_donnees], linewidth=2, markersize=7)
    
    plt.xlabel('Taille du tas (nombre d\'éléments)', fontsize=12)
    plt.ylabel('Temps (en microsecondes)', fontsize=12)
    plt.title('Comparaison des méthodes de construction de Tas Max\n(Tous types de données)', 
              fontsize=14, fontweight='bold')
    plt.legend(fontsize=9, loc='upper left', ncol=2)
    plt.grid(True, alpha=0.3)
    
    plt.xlim(0, df['Taille'].max() * 1.05)
    plt.ylim(0, df['Temps_Insertion'].max() * 1.1)
    
    plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
    
    plt.tight_layout()
    plt.savefig('graphique_tas_comparaison_complete.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique de comparaison complète sauvegardé : graphique_tas_comparaison_complete.png")

def creer_graphique_loglog(df):
    """Crée un graphique en échelle log-log pour chaque type"""
    types = df['Type'].unique()
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        if len(df_type) == 0:
            continue
        
        plt.figure(figsize=(12, 8))
        
        plt.loglog(df_type['Taille'], df_type['Temps_Direct'], 
                   'o-', label='Construction Directe', 
                   color='red', linewidth=2, markersize=8)
        
        plt.loglog(df_type['Taille'], df_type['Temps_Insertion'], 
                   's-', label='Construction Insertion', 
                   color='blue', linewidth=2, markersize=8)
        
        plt.xlabel('Taille (n)', fontsize=12, fontweight='bold')
        plt.ylabel('Temps (µs)', fontsize=12, fontweight='bold')
        plt.title(f'Comparaison des méthodes de construction (échelle log-log)\n(Données {type_donnees})', 
                  fontsize=14, fontweight='bold')
        plt.legend(fontsize=11)
        plt.grid(True, alpha=0.3, which='both')
        
        plt.tight_layout()
        nom_fichier = f'graphique_tas_loglog_{type_donnees}.png'
        plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
        print(f"✓ Graphique log-log sauvegardé : {nom_fichier}")

def afficher_statistiques(df):
    """Affiche des statistiques sur les performances"""
    print("\n" + "="*80)
    print("STATISTIQUES DE PERFORMANCE")
    print("="*80)
    
    types = df['Type'].unique()
    
    for type_donnees in types:
        df_type = df[df['Type'] == type_donnees]
        
        if len(df_type) == 0:
            continue
        
        print(f"\n--- Type de données : {type_donnees.upper()} ---")
        
        # Performance pour la plus grande taille
        derniere_ligne = df_type.iloc[-1]
        print(f"\nPour n = {int(derniere_ligne['Taille'])} :")
        print(f"  - Construction directe : {derniere_ligne['Temps_Direct']:.2f} µs")
        print(f"  - Construction insertion : {derniere_ligne['Temps_Insertion']:.2f} µs")
        
        ratio = derniere_ligne['Temps_Insertion'] / derniere_ligne['Temps_Direct']
        print(f"  - La méthode directe est {ratio:.2f}× plus rapide")
        
        # Vérifier la croissance
        premiere_ligne = df_type.iloc[0]
        facteur_taille = derniere_ligne['Taille'] / premiere_ligne['Taille']
        facteur_temps_direct = derniere_ligne['Temps_Direct'] / premiere_ligne['Temps_Direct']
        facteur_temps_insertion = derniere_ligne['Temps_Insertion'] / premiere_ligne['Temps_Insertion']
        
        print(f"\nCroissance observée (taille ×{facteur_taille:.0f}) :")
        print(f"  - Direct : temps ×{facteur_temps_direct:.1f} (attendu ≈ ×{facteur_taille:.0f} pour O(n))")
        print(f"  - Insertion : temps ×{facteur_temps_insertion:.1f} (attendu ≈ ×{facteur_taille * np.log2(derniere_ligne['Taille']) / np.log2(premiere_ligne['Taille']):.1f} pour O(n log n))")
    
    print("\n" + "="*80 + "\n")

def afficher_tableau_resultats(df):
    """Affiche un tableau des résultats"""
    print("\n" + "="*90)
    print("TABLEAU DES RÉSULTATS")
    print("="*90)
    print(f"{'Taille':>10} | {'Type':>12} | {'Direct (µs)':>15} | {'Insertion (µs)':>15} | {'Ratio':>8}")
    print("-" * 90)
    
    for i in range(len(df)):
        ratio = df['Temps_Insertion'].iloc[i] / df['Temps_Direct'].iloc[i]
        print(f"{int(df['Taille'].iloc[i]):>10} | {df['Type'].iloc[i]:>12} | "
              f"{df['Temps_Direct'].iloc[i]:>15.2f} | {df['Temps_Insertion'].iloc[i]:>15.2f} | "
              f"{ratio:>8.2f}×")
    
    print("="*90 + "\n")

def main():
    print("\n" + "="*80)
    print("GÉNÉRATION DES GRAPHIQUES DE COMPARAISON - TAS BINAIRES")
    print("="*80 + "\n")
    
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
        creer_graphique_par_type(df, type_donnees)
    
    creer_graphique_comparaison_tous_types(df)
    creer_graphique_loglog(df)
    
    print("\n✓ Tous les graphiques ont été générés avec succès !")
    print("\nFichiers créés :")
    for type_donnees in types:
        print(f"  - graphique_tas_{type_donnees}.png : Graphique pour données {type_donnees}")
        print(f"  - graphique_tas_loglog_{type_donnees}.png : Échelle log-log pour données {type_donnees}")
    print(f"  - graphique_tas_comparaison_complete.png : Tous types sur le même graphe")
    print("\n" + "="*80)
    print("ANALYSE THÉORIQUE")
    print("="*80)
    print("Construction directe : O(n) - Linéaire")
    print("Construction insertion : O(n log n) - Quasi-linéaire")
    print("La méthode directe devrait être significativement plus rapide,")
    print("surtout pour les grandes tailles de données.")
    print("="*80 + "\n")

if __name__ == "__main__":
    main()
