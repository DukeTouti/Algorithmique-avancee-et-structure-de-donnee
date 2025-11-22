# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET_TAS = test_tas
TARGET_HUFFMAN = test_huffman
TARGET_COMPRESSION = test_compression
SOURCES_TAS = test_tas.c tas_min.c
SOURCES_HUFFMAN = test_huffman.c tas_min.c frequences.c huffman.c
SOURCES_COMPRESSION = test_compression.c tas_min.c frequences.c huffman.c compression.c
OBJECTS_TAS = $(SOURCES_TAS:.c=.o)
OBJECTS_HUFFMAN = $(SOURCES_HUFFMAN:.c=.o)
OBJECTS_COMPRESSION = $(SOURCES_COMPRESSION:.c=.o)
HEADERS = types.h tas_min.h frequences.h huffman.h compression.h

# Regle par defaut
all: $(TARGET_TAS) $(TARGET_HUFFMAN) $(TARGET_COMPRESSION)
	rm -f *.o

# Creation de l'executable test_tas
$(TARGET_TAS): $(OBJECTS_TAS)
	$(CC) $(OBJECTS_TAS) -o $(TARGET_TAS)

# Creation de l'executable test_huffman
$(TARGET_HUFFMAN): $(OBJECTS_HUFFMAN)
	$(CC) $(OBJECTS_HUFFMAN) -o $(TARGET_HUFFMAN)

# Creation de l'executable test_compression
$(TARGET_COMPRESSION): $(OBJECTS_COMPRESSION)
	$(CC) $(OBJECTS_COMPRESSION) -o $(TARGET_COMPRESSION)

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f *.o

# Nettoyage complet (objets + executables)
fclean: clean
	rm -f $(TARGET_TAS) $(TARGET_HUFFMAN) $(TARGET_COMPRESSION)

# Recompilation complete
re: fclean all

# Execution du test tas
run_tas: $(TARGET_TAS)
	./$(TARGET_TAS)

# Execution du test huffman
run_huffman: $(TARGET_HUFFMAN)
	./$(TARGET_HUFFMAN)

# Execution du test compression
run_compression: $(TARGET_COMPRESSION)
	./$(TARGET_COMPRESSION)

# Declaration des cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re run_tas run_huffman run_compression
