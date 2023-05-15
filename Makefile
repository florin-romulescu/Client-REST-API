CC=g++
FLAGS=-std=c++11 -Wall -Wextra -pedantic -g

SOURCE=src/main.cpp
LIB=src/lib/*.cpp src/lib/Commands/*.cpp
OUTPUT=main

all:
	$(CC) $(FLAGS) $(SOURCE) $(LIB) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

run:
	./$(OUTPUT)