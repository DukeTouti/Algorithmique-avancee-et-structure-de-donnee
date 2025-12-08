# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = graphe_exam
SOURCES = main.c graphe.c bfs.c dfs.c topo.c scc.c kruskal.c prim.c dijkstra.c bellman.c floyd.c coloration.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = graphe.h bfs.h dfs.h topo.h scc.h kruskal.h prim.h dijkstra.h bellman.h floyd.h coloration.h

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
	rm -f *.csv
	rm -f *.png

# Recompilation complète
re: fclean all

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Aide pour les commandes disponibles
help:
	@echo "Commandes disponibles:"
	@echo "  make          - Compiler le projet"
	@echo "  make run      - Compiler et exécuter"
	@echo "  make clean    - Supprimer les fichiers objets"
	@echo "  make fclean   - Nettoyage complet"
	@echo "  make re       - Recompiler depuis zéro"
	@echo "  make help     - Afficher cette aide"

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run help
