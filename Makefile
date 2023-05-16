CC=g++
FLAGS=-std=c++20 -Wall -Wextra -pedantic -g

SOURCE=src/main.cpp
LIB=src/lib/*.cpp src/lib/Commands/*.cpp src/lib/*.c
OUTPUT=main

all:
	$(CC) $(FLAGS) $(SOURCE) $(LIB) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

run:
	./$(OUTPUT)