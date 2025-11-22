# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = test_tas
SOURCES = test_tas.c tas_min.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = types.h tas_min.h

# Regle par defaut
all: $(TARGET)

# Creation de l'executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	rm -f $(OBJECTS)

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJECTS)

# Nettoyage complet (objets + executable)
fclean: clean
	rm -f $(TARGET)

# Recompilation complete
re: fclean all

# Execution du programme
run: $(TARGET)
	./$(TARGET)

# Declaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run
