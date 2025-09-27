# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = main
SOURCES = main.c recherche_max_incrementale.c recherche_max_divise_pour_regner.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = recherche_max_incrementale.h recherche_max_divise_pour_regner.h

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

# Nettoyage complet (objets + exécutable)
fclean: clean
	rm -f $(TARGET)

# Recompilation complète
re: fclean all

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Déclaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run
