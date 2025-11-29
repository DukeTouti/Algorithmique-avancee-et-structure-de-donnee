# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = main
SOURCES = main.c graphe.c prim.c kruskal.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = graphe.h prim.h kruskal.h

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
	rm -f resultats_comparaison_mst.csv
	rm -f *.png

# Recompilation complète
re: fclean all

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Génération des graphiques
graph:
	python3 generer_graphiques_mst.py

# Exécution complète (compilation + run + graphiques)
full: re run graph

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run graph full
