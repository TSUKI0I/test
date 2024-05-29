CC = gcc
EXECUTABLE = maze
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o $(EXECUTABLE)