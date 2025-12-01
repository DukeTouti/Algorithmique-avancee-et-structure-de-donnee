CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = test_dijkstra
OBJS = test_dijkstra.o dijkstra.o affichage.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test_dijkstra.o: test_dijkstra.c dijkstra.h affichage.h
	$(CC) $(CFLAGS) -c test_dijkstra.c

dijkstra.o: dijkstra.c dijkstra.h affichage.h
	$(CC) $(CFLAGS) -c dijkstra.c

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
