EXEC=gameoflife
CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -O3
LDFLAGS=-std=c++11
LIBS=-lncursesw
OBJECTS = $(SOURCES:.cpp=.o)
SOURCES = $(wildcard *.cpp)

all: $(EXEC)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJECTS)

