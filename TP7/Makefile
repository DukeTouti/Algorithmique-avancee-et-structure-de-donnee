# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = main
SOURCES = main.c tas_min_max.c tas_operations.c tas_utils.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = types_tas.h tas_utils.h tas_operations.h tas_min_max.h

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
	rm -f resultats_comparaison_files.csv
	rm -f *.png

# Recompilation complète
re: fclean all

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Génération des graphiques
graph:
	python3 generer_graphiques_files.py

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run graph help
