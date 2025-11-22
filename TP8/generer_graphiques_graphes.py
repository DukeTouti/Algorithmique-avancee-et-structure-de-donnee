#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison BFS vs DFS
TP Graphes - Algorithmes Avancés
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_comparaison_graphes.csv'):
	"""Charge les données depuis le fichier CSV"""
	if not os.path.exists(nom_fichier):
		print(f"❌ Erreur : Le fichier {nom_fichier} n'existe pas.")
		print(f"   Exécutez d'abord : ./main")
		sys.exit(1)
	
	try:
		df = pd.read_csv(nom_fichier)
		df.columns = df.columns.str.strip()
		print(f"✓ Données chargées : {len(df)} points de mesure")
		return df
	except Exception as e:
		print(f"❌ Erreur lors de la lecture du fichier : {e}")
		sys.exit(1)

def creer_graphique_par_densite(df):
	"""Crée un graphique BFS vs DFS pour chaque densité"""
	densites = df['Type'].unique()
	
	for densite_type in densites:
		plt.figure(figsize=(14, 8))
		
		# Filtrer les données pour cette densité
		df_densite = df[df['Type'] == densite_type]
		
		# Tracer BFS
		plt.plot(df_densite['Sommets'], df_densite['Temps_BFS'],
				'o-', label='BFS (Breadth-First Search)',
				color='blue', linewidth=2, markersize=8)
		
		# Tracer DFS
		plt.plot(df_densite['Sommets'], df_densite['Temps_DFS'],
				's-', label='DFS (Depth-First Search)',
				color='red', linewidth=2, markersize=8)
		
		# Ajouter valeurs sur les points
		for i in range(len(df_densite)):
			plt.text(df_densite['Sommets'].iloc[i], df_densite['Temps_BFS'].iloc[i],
					f'{df_densite["Temps_BFS"].iloc[i]:.2f}',
					fontsize=9, color='blue', ha='center', va='bottom')
			
			plt.text(df_densite['Sommets'].iloc[i], df_densite['Temps_DFS'].iloc[i],
					f'{df_densite["Temps_DFS"].iloc[i]:.2f}',
					fontsize=9, color='red', ha='center', va='top')
		
		densite_val = df_densite['Densite'].iloc[0]
		plt.xlabel('Nombre de sommets', fontsize=12)
		plt.ylabel('Temps (ms)', fontsize=12)
		plt.title(f'Comparaison BFS vs DFS\nGraphe {densite_type} (densité {densite_val*100:.0f}%)',
				fontsize=14, fontweight='bold')
		plt.legend(fontsize=11, loc='upper left')
		plt.grid(True, alpha=0.3)
		
		plt.xlim(0, df_densite['Sommets'].max() * 1.05)
		max_temps = max(df_densite['Temps_BFS'].max(), df_densite['Temps_DFS'].max())
		plt.ylim(0, max_temps * 1.2)
		
		plt.tight_layout()
		nom_fichier = f'graphique_bfs_dfs_{densite_type.lower()}.png'
		plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
		print(f"✓ Graphique {densite_type} sauvegardé : {nom_fichier}")

def creer_graphique_global(df):
	"""Crée un graphique global avec toutes les densités"""
	plt.figure(figsize=(16, 10))
	
	densites = df['Type'].unique()
	couleurs = {'Sparse': 'green', 'Medium': 'orange', 'Dense': 'red'}
	marqueurs_bfs = {'Sparse': 'o', 'Medium': 's', 'Dense': '^'}
	marqueurs_dfs = {'Sparse': 'o', 'Medium': 's', 'Dense': '^'}
	
	for densite_type in densites:
		df_densite = df[df['Type'] == densite_type]
		couleur = couleurs.get(densite_type, 'blue')
		
		# BFS pour cette densité
		plt.plot(df_densite['Sommets'], df_densite['Temps_BFS'],
				marker=marqueurs_bfs[densite_type], linestyle='-',
				label=f'BFS - {densite_type}',
				color=couleur, linewidth=2, markersize=7, alpha=0.8)
		
		# DFS pour cette densité
		plt.plot(df_densite['Sommets'], df_densite['Temps_DFS'],
				marker=marqueurs_dfs[densite_type], linestyle='--',
				label=f'DFS - {densite_type}',
				color=couleur, linewidth=2, markersize=7, alpha=0.6)
	
	plt.xlabel('Nombre de sommets', fontsize=12)
	plt.ylabel('Temps (ms)', fontsize=12)
	plt.title('Comparaison GLOBALE : BFS vs DFS\n(Toutes densités)',
			fontsize=14, fontweight='bold')
	plt.legend(fontsize=10, loc='upper left', ncol=2)
	plt.grid(True, alpha=0.3)
	
	plt.xlim(0, df['Sommets'].max() * 1.05)
	plt.ylim(0, df[['Temps_BFS', 'Temps_DFS']].max().max() * 1.1)
	
	plt.tight_layout()
	plt.savefig('graphique_global.png', dpi=300, bbox_inches='tight')
	print("✓ Graphique global sauvegardé : graphique_global.png")

def creer_graphique_impact_densite(df):
	"""Crée un graphique montrant l'impact de la densité"""
	# Prendre une taille moyenne pour comparer l'impact de la densité
	tailles = df['Sommets'].unique()
	taille_ref = tailles[len(tailles)//2]  # Taille au milieu
	
	df_taille = df[df['Sommets'] == taille_ref]
	
	if len(df_taille) == 0:
		print("⚠ Pas assez de données pour le graphique d'impact de densité")
		return
	
	plt.figure(figsize=(12, 8))
	
	x = np.arange(len(df_taille))
	largeur = 0.35
	
	plt.bar(x - largeur/2, df_taille['Temps_BFS'], largeur,
			label='BFS', color='blue', alpha=0.8)
	plt.bar(x + largeur/2, df_taille['Temps_DFS'], largeur,
			label='DFS', color='red', alpha=0.8)
	
	plt.xlabel('Densité du graphe', fontsize=12)
	plt.ylabel('Temps (ms)', fontsize=12)
	plt.title(f'Impact de la DENSITÉ sur les performances\n(Graphe à {taille_ref} sommets)',
			fontsize=14, fontweight='bold')
	plt.xticks(x, df_taille['Type'])
	plt.legend(fontsize=11)
	plt.grid(True, alpha=0.3, axis='y')
	
	# Ajouter les valeurs sur les barres
	for i, (bfs, dfs) in enumerate(zip(df_taille['Temps_BFS'], df_taille['Temps_DFS'])):
		plt.text(i - largeur/2, bfs, f'{bfs:.2f}',
				ha='center', va='bottom', fontsize=10)
		plt.text(i + largeur/2, dfs, f'{dfs:.2f}',
				ha='center', va='bottom', fontsize=10)
	
	plt.tight_layout()
	plt.savefig('graphique_impact_densite.png', dpi=300, bbox_inches='tight')
	print("✓ Graphique impact densité sauvegardé : graphique_impact_densite.png")

def creer_graphique_loglog(df):
	"""Crée un graphique en échelle log-log"""
	plt.figure(figsize=(14, 9))
	
	densites = df['Type'].unique()
	couleurs = {'Sparse': 'green', 'Medium': 'orange', 'Dense': 'red'}
	
	for densite_type in densites:
		df_densite = df[df['Type'] == densite_type]
		couleur = couleurs.get(densite_type, 'blue')
		
		plt.loglog(df_densite['Sommets'], df_densite['Temps_BFS'],
				'o-', label=f'BFS - {densite_type}',
				color=couleur, linewidth=2, markersize=8, alpha=0.8)
		
		plt.loglog(df_densite['Sommets'], df_densite['Temps_DFS'],
				's--', label=f'DFS - {densite_type}',
				color=couleur, linewidth=2, markersize=8, alpha=0.6)
	
	plt.xlabel('Nombre de sommets (log)', fontsize=12, fontweight='bold')
	plt.ylabel('Temps (ms, log)', fontsize=12, fontweight='bold')
	plt.title('Comparaison BFS vs DFS\n(Échelle log-log)',
			fontsize=14, fontweight='bold')
	plt.legend(fontsize=10, loc='upper left')
	plt.grid(True, alpha=0.3, which='both')
	
	plt.tight_layout()
	plt.savefig('graphique_loglog.png', dpi=300, bbox_inches='tight')
	print("✓ Graphique log-log sauvegardé : graphique_loglog.png")

def afficher_statistiques(df):
	"""Affiche des statistiques sur les performances"""
	print("\n" + "="*80)
	print("STATISTIQUES DE PERFORMANCE")
	print("="*80)
	
	densites = df['Type'].unique()
	
	for densite_type in densites:
		df_densite = df[df['Type'] == densite_type]
		derniere_ligne = df_densite.iloc[-1]
		premiere_ligne = df_densite.iloc[0]
		
		n = int(derniere_ligne['Sommets'])
		densite_val = derniere_ligne['Densite']
		
		print(f"\n{'='*80}")
		print(f"GRAPHE {densite_type.upper()} (densité {densite_val*100:.0f}%)")
		print(f"{'='*80}")
		
		print(f"\nPour n = {n} sommets :")
		print(f"  • BFS : {derniere_ligne['Temps_BFS']:.2f} ms")
		print(f"  • DFS : {derniere_ligne['Temps_DFS']:.2f} ms")
		
		if derniere_ligne['Temps_BFS'] > derniere_ligne['Temps_DFS']:
			ratio = derniere_ligne['Temps_BFS'] / derniere_ligne['Temps_DFS']
			print(f"  → DFS est {ratio:.2f}× plus RAPIDE ✓")
		else:
			ratio = derniere_ligne['Temps_DFS'] / derniere_ligne['Temps_BFS']
			print(f"  → BFS est {ratio:.2f}× plus RAPIDE ✓")
		
		# Analyse de croissance
		facteur_taille = derniere_ligne['Sommets'] / premiere_ligne['Sommets']
		facteur_bfs = derniere_ligne['Temps_BFS'] / premiere_ligne['Temps_BFS'] if premiere_ligne['Temps_BFS'] > 0 else 0
		facteur_dfs = derniere_ligne['Temps_DFS'] / premiere_ligne['Temps_DFS'] if premiere_ligne['Temps_DFS'] > 0 else 0
		
		print(f"\n  CROISSANCE (taille ×{facteur_taille:.1f}) :")
		print(f"  • BFS : temps ×{facteur_bfs:.1f}")
		print(f"  • DFS : temps ×{facteur_dfs:.1f}")
	
	print("\n" + "="*80 + "\n")

def afficher_tableau_resultats(df):
	"""Affiche un tableau des résultats"""
	print("\n" + "="*100)
	print("TABLEAU DES RÉSULTATS")
	print("="*100)
	print(f"{'Sommets':>10} | {'Densité':>10} | {'Type':>10} | {'BFS (ms)':>12} | {'DFS (ms)':>12}")
	print("-" * 100)
	
	for i in range(len(df)):
		print(f"{int(df['Sommets'].iloc[i]):>10} | "
			f"{df['Densite'].iloc[i]:>10.1f} | "
			f"{df['Type'].iloc[i]:>10} | "
			f"{df['Temps_BFS'].iloc[i]:>12.2f} | "
			f"{df['Temps_DFS'].iloc[i]:>12.2f}")
	
	print("="*100 + "\n")

def main():
	print("\n" + "="*80)
	print("GÉNÉRATION DES GRAPHIQUES - BFS vs DFS")
	print("="*80 + "\n")
	
	# Charger données
	df = charger_donnees()
	
	# Afficher tableau
	afficher_tableau_resultats(df)
	
	# Afficher statistiques
	afficher_statistiques(df)
	
	# Créer graphiques
	print("Génération des graphiques...")
	creer_graphique_par_densite(df)
	creer_graphique_global(df)
	creer_graphique_impact_densite(df)
	creer_graphique_loglog(df)
	
	print("\n✓ Tous les graphiques ont été générés avec succès !")
	print("\nFichiers créés :")
	print("  - graphique_bfs_dfs_sparse.png : Graphes peu denses")
	print("  - graphique_bfs_dfs_medium.png : Graphes moyennement denses")
	print("  - graphique_bfs_dfs_dense.png : Graphes très denses")
	print("  - graphique_global.png : Toutes configurations")
	print("  - graphique_impact_densite.png : Impact de la densité")
	print("  - graphique_loglog.png : Échelle log-log")
	
	print("\n" + "="*80)
	print("ANALYSE THÉORIQUE")
	print("="*80)
	print("BFS (Breadth-First Search) :")
	print("  • Complexité : O(V + E)")
	print("  • Utilise une FIFO (queue)")
	print("  • Parcours en largeur (niveau par niveau)")
	print("\nDFS (Depth-First Search) :")
	print("  • Complexité : O(V + E)")
	print("  • Utilise la récursion (stack implicite)")
	print("  • Parcours en profondeur (explore au maximum)")
	print("\nCONCLUSION :")
	print("  Les deux algorithmes ont la même complexité théorique O(V + E).")
	print("  Les différences de performance dépendent de :")
	print("    - La structure du graphe (densité, forme)")
	print("    - L'implémentation (overhead de la queue vs récursion)")
	print("    - La localité mémoire")
	print("="*80 + "\n")

if __name__ == "__main__":
	main()
