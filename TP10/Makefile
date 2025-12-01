# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Cibles
TARGET_DIJKSTRA = test_dijkstra
TARGET_BELLMAN = test_bellman_ford
TARGET_FLOYD = test_floyd_warshall
TARGET_MAIN = main

# Règle par défaut
all: $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD) $(TARGET_MAIN)

# === DIJKSTRA ===
$(TARGET_DIJKSTRA): test_dijkstra.o dijkstra.o affichage.o
	$(CC) test_dijkstra.o dijkstra.o affichage.o -o $(TARGET_DIJKSTRA)

test_dijkstra.o: test_dijkstra.c dijkstra.h affichage.h
	$(CC) $(CFLAGS) -c test_dijkstra.c

dijkstra.o: dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c

# === BELLMAN-FORD ===
$(TARGET_BELLMAN): test_bellman_ford.o bellman_ford.o affichage_bf.o
	$(CC) test_bellman_ford.o bellman_ford.o affichage_bf.o -o $(TARGET_BELLMAN)

test_bellman_ford.o: test_bellman_ford.c bellman_ford.h affichage_bf.h
	$(CC) $(CFLAGS) -c test_bellman_ford.c

bellman_ford.o: bellman_ford.c bellman_ford.h
	$(CC) $(CFLAGS) -c bellman_ford.c

affichage_bf.o: affichage_bf.c affichage_bf.h
	$(CC) $(CFLAGS) -c affichage_bf.c

# === FLOYD-WARSHALL ===
$(TARGET_FLOYD): test_floyd_warshall.o floyd_warshall.o affichage_fw.o
	$(CC) test_floyd_warshall.o floyd_warshall.o affichage_fw.o -o $(TARGET_FLOYD)

test_floyd_warshall.o: test_floyd_warshall.c floyd_warshall.h affichage_fw.h
	$(CC) $(CFLAGS) -c test_floyd_warshall.c

floyd_warshall.o: floyd_warshall.c floyd_warshall.h
	$(CC) $(CFLAGS) -c floyd_warshall.c

affichage_fw.o: affichage_fw.c affichage_fw.h
	$(CC) $(CFLAGS) -c affichage_fw.c

# === MAIN (TP10) - STANDALONE, pas de dépendances ===
$(TARGET_MAIN): main.o
	$(CC) main.o -o $(TARGET_MAIN)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# === RÈGLES GÉNÉRALES ===
clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET_DIJKSTRA) $(TARGET_BELLMAN) $(TARGET_FLOYD) $(TARGET_MAIN)
	rm -f resultats_*.csv *.png

re: fclean all

run-dijkstra: $(TARGET_DIJKSTRA)
	./$(TARGET_DIJKSTRA)

run-bellman: $(TARGET_BELLMAN)
	./$(TARGET_BELLMAN)

run-floyd: $(TARGET_FLOYD)
	./$(TARGET_FLOYD)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

run-all: all
	@echo "\n=== Dijkstra ===\n"
	./$(TARGET_DIJKSTRA)
	@echo "\n=== Bellman-Ford ===\n"
	./$(TARGET_BELLMAN)
	@echo "\n=== Floyd-Warshall ===\n"
	./$(TARGET_FLOYD)
	@echo "\n=== Main (TP10) ===\n"
	./$(TARGET_MAIN)

graph:
	python3 generer_graphiques.py

full: re run graph

.PHONY: all clean fclean re run-dijkstra run-bellman run-floyd run run-all graph full
