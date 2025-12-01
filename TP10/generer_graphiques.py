#!/usr/bin/env python3
"""
Script de génération de graphiques pour la comparaison Dijkstra vs Bellman-Ford vs Floyd-Warshall
TP10 - Algorithmes de Plus Courts Chemins
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def charger_donnees(nom_fichier='resultats_comparaison_chemins.csv'):
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
	"""Crée un graphique Dijkstra vs Bellman-Ford vs Floyd-Warshall pour chaque densité"""
	densites = df['Type'].unique()
	
	for densite_type in densites:
		plt.figure(figsize=(14, 8))
		
		# Filtrer les données pour cette densité
		df_densite = df[df['Type'] == densite_type]
		
		# Tracer Dijkstra
		plt.plot(df_densite['Sommets'], df_densite['Temps_Dijkstra_us'],
				'o-', label='Dijkstra',
				color='blue', linewidth=2, markersize=8)
		
		# Tracer Bellman-Ford
		plt.plot(df_densite['Sommets'], df_densite['Temps_BellmanFord_us'],
				's-', label='Bellman-Ford',
				color='red', linewidth=2, markersize=8)
		
		# Tracer Floyd-Warshall
		plt.plot(df_densite['Sommets'], df_densite['Temps_FloydWarshall_us'],
				'^-', label='Floyd-Warshall',
				color='green', linewidth=2, markersize=8)
		
		# Ajouter valeurs sur les points
		for i in range(len(df_densite)):
			plt.text(df_densite['Sommets'].iloc[i], df_densite['Temps_Dijkstra_us'].iloc[i],
					f'{df_densite["Temps_Dijkstra_us"].iloc[i]:.0f}',
					fontsize=8, color='blue', ha='center', va='bottom')
			
			plt.text(df_densite['Sommets'].iloc[i], df_densite['Temps_BellmanFord_us'].iloc[i],
					f'{df_densite["Temps_BellmanFord_us"].iloc[i]:.0f}',
					fontsize=8, color='red', ha='center', va='top')
			
			plt.text(df_densite['Sommets'].iloc[i], df_densite['Temps_FloydWarshall_us'].iloc[i],
					f'{df_densite["Temps_FloydWarshall_us"].iloc[i]:.0f}',
					fontsize=8, color='green', ha='left', va='center')
		
		densite_val = df_densite['Densite'].iloc[0]
		plt.xlabel('Nombre de sommets', fontsize=12)
		plt.ylabel('Temps (µs)', fontsize=12)
		plt.title(f'Comparaison Dijkstra vs Bellman-Ford vs Floyd-Warshall\nGraphe {densite_type} (densité {densite_val*100:.0f}%)',
				fontsize=14, fontweight='bold')
		plt.legend(fontsize=11, loc='upper left')
		plt.grid(True, alpha=0.3)
		
		plt.xlim(0, df_densite['Sommets'].max() * 1.05)
		max_temps = max(df_densite['Temps_Dijkstra_us'].max(), 
		                df_densite['Temps_BellmanFord_us'].max(),
		                df_densite['Temps_FloydWarshall_us'].max())
		plt.ylim(0, max_temps * 1.2)
		
		plt.tight_layout()
		nom_fichier = f'graphique_chemins_{densite_type.lower()}.png'
		plt.savefig(nom_fichier, dpi=300, bbox_inches='tight')
		print(f"✓ Graphique {densite_type} sauvegardé : {nom_fichier}")

def creer_graphique_global(df):
	"""Crée un graphique global avec toutes les densités"""
	plt.figure(figsize=(16, 10))
	
	densites = df['Type'].unique()
	couleurs = {'Sparse': 'green', 'Medium': 'orange', 'Dense': 'red'}
	marqueurs = {'Dijkstra': 'o', 'BellmanFord': 's', 'FloydWarshall': '^'}
	
	for densite_type in densites:
		df_densite = df[df['Type'] == densite_type]
		couleur = couleurs.get(densite_type, 'blue')
		
		# Dijkstra
		plt.plot(df_densite['Sommets'], df_densite['Temps_Dijkstra_us'],
				marker=marqueurs['Dijkstra'], linestyle='-',
				label=f'Dijkstra - {densite_type}',
				color=couleur, linewidth=2, markersize=7, alpha=0.8)
		
		# Bellman-Ford
		plt.plot(df_densite['Sommets'], df_densite['Temps_BellmanFord_us'],
				marker=marqueurs['BellmanFord'], linestyle='--',
				label=f'Bellman-Ford - {densite_type}',
				color=couleur, linewidth=2, markersize=7, alpha=0.6)
		
		# Floyd-Warshall
		plt.plot(df_densite['Sommets'], df_densite['Temps_FloydWarshall_us'],
				marker=marqueurs['FloydWarshall'], linestyle=':',
				label=f'Floyd-Warshall - {densite_type}',
				color=couleur, linewidth=2, markersize=7, alpha=0.5)
	
	plt.xlabel('Nombre de sommets', fontsize=12)
	plt.ylabel('Temps (µs)', fontsize=12)
	plt.title('Comparaison GLOBALE : Dijkstra vs Bellman-Ford vs Floyd-Warshall\n(Toutes densités)',
			fontsize=14, fontweight='bold')
	plt.legend(fontsize=9, loc='upper left', ncol=3)
	plt.grid(True, alpha=0.3)
	
	plt.xlim(0, df['Sommets'].max() * 1.05)
	plt.ylim(0, df[['Temps_Dijkstra_us', 'Temps_BellmanFord_us', 'Temps_FloydWarshall_us']].max().max() * 1.1)
	
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
	largeur = 0.25
	
	plt.bar(x - largeur, df_taille['Temps_Dijkstra_us'], largeur,
			label='Dijkstra', color='blue', alpha=0.8)
	plt.bar(x, df_taille['Temps_BellmanFord_us'], largeur,
			label='Bellman-Ford', color='red', alpha=0.8)
	plt.bar(x + largeur, df_taille['Temps_FloydWarshall_us'], largeur,
			label='Floyd-Warshall', color='green', alpha=0.8)
	
	plt.xlabel('Densité du graphe', fontsize=12)
	plt.ylabel('Temps (µs)', fontsize=12)
	plt.title(f'Impact de la DENSITÉ sur les performances\n(Graphe à {taille_ref} sommets)',
			fontsize=14, fontweight='bold')
	plt.xticks(x, df_taille['Type'])
	plt.legend(fontsize=11)
	plt.grid(True, alpha=0.3, axis='y')
	
	# Ajouter les valeurs sur les barres
	for i, (dijkstra, bellman, floyd) in enumerate(zip(df_taille['Temps_Dijkstra_us'], 
	                                                     df_taille['Temps_BellmanFord_us'],
	                                                     df_taille['Temps_FloydWarshall_us'])):
		plt.text(i - largeur, dijkstra, f'{dijkstra:.0f}',
				ha='center', va='bottom', fontsize=9)
		plt.text(i, bellman, f'{bellman:.0f}',
				ha='center', va='bottom', fontsize=9)
		plt.text(i + largeur, floyd, f'{floyd:.0f}',
				ha='center', va='bottom', fontsize=9)
	
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
		
		plt.loglog(df_densite['Sommets'], df_densite['Temps_Dijkstra_us'],
				'o-', label=f'Dijkstra - {densite_type}',
				color=couleur, linewidth=2, markersize=8, alpha=0.8)
		
		plt.loglog(df_densite['Sommets'], df_densite['Temps_BellmanFord_us'],
				's--', label=f'Bellman-Ford - {densite_type}',
				color=couleur, linewidth=2, markersize=8, alpha=0.6)
		
		plt.loglog(df_densite['Sommets'], df_densite['Temps_FloydWarshall_us'],
				'^:', label=f'Floyd-Warshall - {densite_type}',
				color=couleur, linewidth=2, markersize=8, alpha=0.5)
	
	plt.xlabel('Nombre de sommets (log)', fontsize=12, fontweight='bold')
	plt.ylabel('Temps (µs, log)', fontsize=12, fontweight='bold')
	plt.title('Comparaison Dijkstra vs Bellman-Ford vs Floyd-Warshall\n(Échelle log-log)',
			fontsize=14, fontweight='bold')
	plt.legend(fontsize=9, loc='upper left', ncol=2)
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
		print(f"  • Dijkstra      : {derniere_ligne['Temps_Dijkstra_us']:.2f} µs")
		print(f"  • Bellman-Ford  : {derniere_ligne['Temps_BellmanFord_us']:.2f} µs")
		print(f"  • Floyd-Warshall: {derniere_ligne['Temps_FloydWarshall_us']:.2f} µs")
		
		# Trouver le plus rapide
		temps = {
			'Dijkstra': derniere_ligne['Temps_Dijkstra_us'],
			'Bellman-Ford': derniere_ligne['Temps_BellmanFord_us'],
			'Floyd-Warshall': derniere_ligne['Temps_FloydWarshall_us']
		}
		plus_rapide = min(temps, key=temps.get)
		
		print(f"\n  → {plus_rapide} est le PLUS RAPIDE ✓")
		
		# Analyse de croissance
		facteur_taille = derniere_ligne['Sommets'] / premiere_ligne['Sommets']
		facteur_dijkstra = derniere_ligne['Temps_Dijkstra_us'] / premiere_ligne['Temps_Dijkstra_us'] if premiere_ligne['Temps_Dijkstra_us'] > 0 else 0
		facteur_bellman = derniere_ligne['Temps_BellmanFord_us'] / premiere_ligne['Temps_BellmanFord_us'] if premiere_ligne['Temps_BellmanFord_us'] > 0 else 0
		facteur_floyd = derniere_ligne['Temps_FloydWarshall_us'] / premiere_ligne['Temps_FloydWarshall_us'] if premiere_ligne['Temps_FloydWarshall_us'] > 0 else 0
		
		print(f"\n  CROISSANCE (taille ×{facteur_taille:.1f}) :")
		print(f"  • Dijkstra      : temps ×{facteur_dijkstra:.1f}")
		print(f"  • Bellman-Ford  : temps ×{facteur_bellman:.1f}")
		print(f"  • Floyd-Warshall: temps ×{facteur_floyd:.1f}")
	
	print("\n" + "="*80 + "\n")

def afficher_tableau_resultats(df):
	"""Affiche un tableau des résultats"""
	print("\n" + "="*110)
	print("TABLEAU DES RÉSULTATS")
	print("="*110)
	print(f"{'Sommets':>10} | {'Densité':>10} | {'Type':>10} | {'Dijkstra (µs)':>15} | {'Bellman-Ford (µs)':>18} | {'Floyd-Warshall (µs)':>20}")
	print("-" * 110)
	
	for i in range(len(df)):
		print(f"{int(df['Sommets'].iloc[i]):>10} | "
			f"{df['Densite'].iloc[i]:>10.1f} | "
			f"{df['Type'].iloc[i]:>10} | "
			f"{df['Temps_Dijkstra_us'].iloc[i]:>15.2f} | "
			f"{df['Temps_BellmanFord_us'].iloc[i]:>18.2f} | "
			f"{df['Temps_FloydWarshall_us'].iloc[i]:>20.2f}")
	
	print("="*110 + "\n")

def main():
	print("\n" + "="*80)
	print("GÉNÉRATION DES GRAPHIQUES - ALGORITHMES DE PLUS COURTS CHEMINS")
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
	print("  - graphique_chemins_sparse.png : Graphes peu denses")
	print("  - graphique_chemins_medium.png : Graphes moyennement denses")
	print("  - graphique_chemins_dense.png : Graphes très denses")
	print("  - graphique_global.png : Toutes configurations")
	print("  - graphique_impact_densite.png : Impact de la densité")
	print("  - graphique_loglog.png : Échelle log-log")
	
	print("\n" + "="*80)
	print("ANALYSE THÉORIQUE")
	print("="*80)
	print("Dijkstra (tous sommets) :")
	print("  • Complexité : O(V³) avec implémentation simple")
	print("  • Complexité : O(V × (V + E) log V) avec min-heap")
	print("  • Ne fonctionne PAS avec poids négatifs")
	print("  • Sélectionne toujours le sommet de distance minimale")
	print("\nBellman-Ford (tous sommets) :")
	print("  • Complexité : O(V² × E)")
	print("  • Fonctionne avec poids négatifs")
	print("  • Détecte les cycles négatifs")
	print("  • Relaxation V-1 fois pour chaque source")
	print("\nFloyd-Warshall :")
	print("  • Complexité : O(V³)")
	print("  • Calcule TOUS les plus courts chemins (une seule exécution)")
	print("  • Fonctionne avec poids négatifs")
	print("  • Programmation dynamique")
	print("\nCONCLUSION :")
	print("  • Dijkstra : RAPIDE sur graphes sans poids négatifs")
	print("  • Bellman-Ford : FLEXIBLE (poids négatifs) mais LENT (O(V²E))")
	print("  • Floyd-Warshall : OPTIMAL pour tous-vers-tous (O(V³))")
	print("  • Pour tous-vers-tous : Floyd-Warshall vs V × Dijkstra")
	print("="*80 + "\n")

if __name__ == "__main__":
	main()
