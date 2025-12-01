# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = test_dijkstra
SOURCES = test_dijkstra.c dijkstra.c affichage.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = dijkstra.h affichage.h

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	rm -f $(OBJECTS)

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJECTS)

# Nettoyage complet (objets + exécutable + résultats)
fclean: clean
	rm -f $(TARGET)
	rm -f resultats_dijkstra.csv
	rm -f *.png

# Recompilation complète
re: fclean all

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Génération des graphiques (si tu en ajoutes plus tard)
graph:
	python3 generer_graphiques_dijkstra.py

# Exécution complète (compilation + run + graphiques)
full: re run graph

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run graph full
