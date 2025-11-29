# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_POSIX_C_SOURCE=200809L
TARGET_TAS = test_tas
TARGET_HUFFMAN = test_huffman
TARGET_COMPRESSION = test_compression
TARGET_DECODAGE = test_decodage
TARGET_MAIN = huffman

SOURCES_TAS = test_tas.c tas_min.c
SOURCES_HUFFMAN = test_huffman.c tas_min.c frequences.c huffman.c
SOURCES_COMPRESSION = test_compression.c tas_min.c frequences.c huffman.c compression.c
SOURCES_DECODAGE = test_decodage.c tas_min.c frequences.c huffman.c decodage.c
SOURCES_MAIN = main.c modes.c tas_min.c frequences.c huffman.c compression.c decodage.c

OBJECTS_TAS = $(SOURCES_TAS:.c=.o)
OBJECTS_HUFFMAN = $(SOURCES_HUFFMAN:.c=.o)
OBJECTS_COMPRESSION = $(SOURCES_COMPRESSION:.c=.o)
OBJECTS_DECODAGE = $(SOURCES_DECODAGE:.c=.o)
OBJECTS_MAIN = $(SOURCES_MAIN:.c=.o)

HEADERS = types.h tas_min.h frequences.h huffman.h compression.h decodage.h modes.h

# Regle par defaut
all: $(TARGET_TAS) $(TARGET_HUFFMAN) $(TARGET_COMPRESSION) $(TARGET_DECODAGE) $(TARGET_MAIN)
	rm -f *.o

# Creation des executables
$(TARGET_TAS): $(OBJECTS_TAS)
	$(CC) $(OBJECTS_TAS) -o $(TARGET_TAS)

$(TARGET_HUFFMAN): $(OBJECTS_HUFFMAN)
	$(CC) $(OBJECTS_HUFFMAN) -o $(TARGET_HUFFMAN)

$(TARGET_COMPRESSION): $(OBJECTS_COMPRESSION)
	$(CC) $(OBJECTS_COMPRESSION) -o $(TARGET_COMPRESSION)

$(TARGET_DECODAGE): $(OBJECTS_DECODAGE)
	$(CC) $(OBJECTS_DECODAGE) -o $(TARGET_DECODAGE)

$(TARGET_MAIN): $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $(TARGET_MAIN)

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET_TAS) $(TARGET_HUFFMAN) $(TARGET_COMPRESSION) $(TARGET_DECODAGE) $(TARGET_MAIN)

re: fclean all

# Execution
run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

.PHONY: all clean fclean re run
