# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Cibles
TARGET_DIJKSTRA = test_dijkstra
TARGET_BELLMAN = test_bellman_ford
TARGET_FLOYD = test_floyd_warshall
TARGET_MAIN = main

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

# Sources Main (TP10)
SOURCES_MAIN = main.c dijkstra.c bellman_ford.c floyd_warshall.c affichage.c affichage_bf.c affichage_fw.c
OBJECTS_MAIN = $(SOURCES_MAIN:.c=.o)
HEADERS_MAIN = dijkstra.h bellman_ford.h floyd_warshall.h affichage.h affichage_bf.h affichage_fw.h

# Règle par défaut: compiler tous les programmes
all: $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD) $(TARGET_MAIN)

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

# === MAIN (TP10) ===

# Création de l'exécutable Main
$(TARGET_MAIN): $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $(TARGET_MAIN)
	rm -f $(OBJECTS_MAIN)

# Compilation des fichiers objets Main
main.o: main.c $(HEADERS_MAIN)
	$(CC) $(CFLAGS) -c main.c -o main.o

# === RÈGLES GÉNÉRALES ===

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJECTS_DIJKSTRA) $(OBJECTS_BELLMAN) $(OBJECTS_FLOYD) $(OBJECTS_MAIN)
	rm -f *.o

# Nettoyage complet (objets + exécutables + résultats)
fclean: clean
	rm -f $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD) $(TARGET_MAIN)
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

# Exécution Main (TP10)
run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

# Exécution des quatre programmes
run-all: $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD) $(TARGET_MAIN)
	@echo "\n=== Exécution de Dijkstra ===\n"
	./$(TARGET_DIJKSTRA)
	@echo "\n\n=== Exécution de Bellman-Ford ===\n"
	./$(TARGET_BELLMAN)
	@echo "\n\n=== Exécution de Floyd-Warshall ===\n"
	./$(TARGET_FLOYD)
	@echo "\n\n=== Exécution du Main (TP10) ===\n"
	./$(TARGET_MAIN)

# Génération des graphiques
graph:
	python3 generer_graphiques.py

# Exécution complète (compilation + run + graphiques)
full: re run graph

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run-dijkstra run-bellman run-floyd run run-all graph full
