CC = gcc
CFLAGS = -Wall -Wextra -I.

SRCS = main.c processus.c
OBJS = $(SRCS:.c=.o)
TARGET = ordonnanceur

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c processus.h scheduler.h
processus.o: processus.c processus.h

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) config.txt

.PHONY: all clean run