CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = test_dijkstra
OBJS = main.o dijkstra.o affichage.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c dijkstra.h affichage.h
	$(CC) $(CFLAGS) -c main.c

dijkstra.o: dijkstra.c dijkstra.h affichage.h
	$(CC) $(CFLAGS) -c dijkstra.c

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
