# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Cibles
TARGET_DIJKSTRA = test_dijkstra
TARGET_BELLMAN = test_bellman_ford
TARGET_FLOYD = test_floyd_warshall

# Sources Dijkstra
SOURCES_DIJKSTRA = test_dijkstra.c dijkstra.c affichage.c
OBJECTS_DIJKSTRA = $(SOURCES_DIJKSTRA:.c=.o)
HEADERS_DIJKSTRA = dijkstra.h affichage.h

# Sources Bellman-Ford
SOURCES_BELLMAN = test_bellman_ford.c bellman_ford.c affichage_bf.c
OBJECTS_BELLMAN = $(SOURCES_BELLMAN:.c=.o)
HEADERS_BELLMAN = bellman_ford.h affichage_bf.h

# Sources Floyd-Warshall
SOURCES_FLOYD = test_floyd_warshall.c floyd_warshall.c affichage_fw.c
OBJECTS_FLOYD = $(SOURCES_FLOYD:.c=.o)
HEADERS_FLOYD = floyd_warshall.h affichage_fw.h

# Règle par défaut: compiler les trois
all: $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD)

# === DIJKSTRA ===

# Création de l'exécutable Dijkstra
$(TARGET_DIJKSTRA): $(OBJECTS_DIJKSTRA)
	$(CC) $(OBJECTS_DIJKSTRA) -o $(TARGET_DIJKSTRA)
	rm -f $(OBJECTS_DIJKSTRA)

# Compilation des fichiers objets Dijkstra
test_dijkstra.o: test_dijkstra.c $(HEADERS_DIJKSTRA)
	$(CC) $(CFLAGS) -c test_dijkstra.c -o test_dijkstra.o

dijkstra.o: dijkstra.c $(HEADERS_DIJKSTRA)
	$(CC) $(CFLAGS) -c dijkstra.c -o dijkstra.o

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c -o affichage.o

# === BELLMAN-FORD ===

# Création de l'exécutable Bellman-Ford
$(TARGET_BELLMAN): $(OBJECTS_BELLMAN)
	$(CC) $(OBJECTS_BELLMAN) -o $(TARGET_BELLMAN)
	rm -f $(OBJECTS_BELLMAN)

# Compilation des fichiers objets Bellman-Ford
test_bellman_ford.o: test_bellman_ford.c $(HEADERS_BELLMAN)
	$(CC) $(CFLAGS) -c test_bellman_ford.c -o test_bellman_ford.o

bellman_ford.o: bellman_ford.c $(HEADERS_BELLMAN)
	$(CC) $(CFLAGS) -c bellman_ford.c -o bellman_ford.o

affichage_bf.o: affichage_bf.c $(HEADERS_BELLMAN)
	$(CC) $(CFLAGS) -c affichage_bf.c -o affichage_bf.o

# === FLOYD-WARSHALL ===

# Création de l'exécutable Floyd-Warshall
$(TARGET_FLOYD): $(OBJECTS_FLOYD)
	$(CC) $(OBJECTS_FLOYD) -o $(TARGET_FLOYD)
	rm -f $(OBJECTS_FLOYD)

# Compilation des fichiers objets Floyd-Warshall
test_floyd_warshall.o: test_floyd_warshall.c $(HEADERS_FLOYD)
	$(CC) $(CFLAGS) -c test_floyd_warshall.c -o test_floyd_warshall.o

floyd_warshall.o: floyd_warshall.c $(HEADERS_FLOYD)
	$(CC) $(CFLAGS) -c floyd_warshall.c -o floyd_warshall.o

affichage_fw.o: affichage_fw.c $(HEADERS_FLOYD)
	$(CC) $(CFLAGS) -c affichage_fw.c -o affichage_fw.o

# === RÈGLES GÉNÉRALES ===

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJECTS_DIJKSTRA) $(OBJECTS_BELLMAN) $(OBJECTS_FLOYD)
	rm -f *.o

# Nettoyage complet (objets + exécutables + résultats)
fclean: clean
	rm -f $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD)
	rm -f resultats_*.csv
	rm -f *.png

# Recompilation complète
re: fclean all

# Exécution Dijkstra
run-dijkstra: $(TARGET_DIJKSTRA)
	./$(TARGET_DIJKSTRA)

# Exécution Bellman-Ford
run-bellman: $(TARGET_BELLMAN)
	./$(TARGET_BELLMAN)

# Exécution Floyd-Warshall
run-floyd: $(TARGET_FLOYD)
	./$(TARGET_FLOYD)

# Exécution des trois
run-all: $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD)
	@echo "\n=== Exécution de Dijkstra ===\n"
	./$(TARGET_DIJKSTRA)
	@echo "\n\n=== Exécution de Bellman-Ford ===\n"
	./$(TARGET_BELLMAN)
	@echo "\n\n=== Exécution de Floyd-Warshall ===\n"
	./$(TARGET_FLOYD)

# Génération des graphiques (si tu en ajoutes plus tard)
graph:
	python3 generer_graphiques.py

# Exécution complète (compilation + run + graphiques)
full: re run-all graph

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run-dijkstra run-bellman run-floyd run-all graph full
