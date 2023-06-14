OBJS	= obj/main.o obj/lib/utils.o obj/lib/Session.o obj/lib/Input.o obj/lib/HTTPParser.o obj/lib/buffer.o obj/lib/helpers.o obj/lib/Commands/AddBookCommand.o obj/lib/Commands/DeleteBookCommand.o obj/lib/Commands/EnterLibaryCommand.o obj/lib/Commands/ExitCommand.o obj/lib/Commands/GetBookCommand.o obj/lib/Commands/GetBooksCommand.o obj/lib/Commands/HelpCommand.o obj/lib/Commands/InvalidCommand.o obj/lib/Commands/LoginCommand.o obj/lib/Commands/LogoutCommand.o obj/lib/Commands/RegisterCommand.o
SOURCE	= src/main.cpp src/lib/utils.cpp src/lib/Session.cpp src/lib/Input.cpp src/lib/HTTPParser.cpp src/lib/buffer.c src/lib/helpers.c src/lib/Commands/AddBookCommand.cpp src/lib/Commands/DeleteBookCommand.cpp src/lib/Commands/EnterLibaryCommand.cpp src/lib/Commands/ExitCommand.cpp src/lib/Commands/GetBookCommand.cpp src/lib/Commands/GetBooksCommand.cpp src/lib/Commands/HelpCommand.cpp src/lib/Commands/InvalidCommand.cpp src/lib/Commands/LoginCommand.cpp src/lib/Commands/LogoutCommand.cpp src/lib/Commands/RegisterCommand.cpp
HEADER	= src/include/utils.hpp src/include/Session.hpp src/include/json.hpp src/include/input.hpp src/include/HTTPParser.hpp src/include/Command.hpp src/include/helpers/buffer.h src/include/helpers/helpers.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall -Wextra
LFLAGS	 = 

all: obj $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

obj:
	mkdir -p obj/lib/Commands

obj/main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp -std=c++17 -o obj/main.o

obj/lib/utils.o: src/lib/utils.cpp
	$(CC) $(FLAGS) src/lib/utils.cpp -std=c++17 -o obj/lib/utils.o

obj/lib/Session.o: src/lib/Session.cpp
	$(CC) $(FLAGS) src/lib/Session.cpp -std=c++17 -o obj/lib/Session.o

obj/lib/Input.o: src/lib/Input.cpp
	$(CC) $(FLAGS) src/lib/Input.cpp -std=c++17 -o obj/lib/Input.o

obj/lib/HTTPParser.o: src/lib/HTTPParser.cpp
	$(CC) $(FLAGS) src/lib/HTTPParser.cpp -std=c++17 -o obj/lib/HTTPParser.o

obj/lib/buffer.o: src/lib/buffer.c
	$(CC) $(FLAGS) src/lib/buffer.c -std=c++17 -o obj/lib/buffer.o

obj/lib/helpers.o: src/lib/helpers.c
	$(CC) $(FLAGS) src/lib/helpers.c -std=c++17 -o obj/lib/helpers.o

obj/lib/Commands/AddBookCommand.o: src/lib/Commands/AddBookCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/AddBookCommand.cpp -std=c++17 -o obj/lib/Commands/AddBookCommand.o

obj/lib/Commands/DeleteBookCommand.o: src/lib/Commands/DeleteBookCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/DeleteBookCommand.cpp -std=c++17 -o obj/lib/Commands/DeleteBookCommand.o

obj/lib/Commands/EnterLibaryCommand.o: src/lib/Commands/EnterLibaryCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/EnterLibaryCommand.cpp -std=c++17 -o obj/lib/Commands/EnterLibaryCommand.o

obj/lib/Commands/ExitCommand.o: src/lib/Commands/ExitCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/ExitCommand.cpp -std=c++17 -o obj/lib/Commands/ExitCommand.o

obj/lib/Commands/GetBookCommand.o: src/lib/Commands/GetBookCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/GetBookCommand.cpp -std=c++17 -o obj/lib/Commands/GetBookCommand.o

obj/lib/Commands/GetBooksCommand.o: src/lib/Commands/GetBooksCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/GetBooksCommand.cpp -std=c++17 -o obj/lib/Commands/GetBooksCommand.o

obj/lib/Commands/HelpCommand.o: src/lib/Commands/HelpCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/HelpCommand.cpp -std=c++17 -o obj/lib/Commands/HelpCommand.o

obj/lib/Commands/InvalidCommand.o: src/lib/Commands/InvalidCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/InvalidCommand.cpp -std=c++17 -o obj/lib/Commands/InvalidCommand.o

obj/lib/Commands/LoginCommand.o: src/lib/Commands/LoginCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/LoginCommand.cpp -std=c++17 -o obj/lib/Commands/LoginCommand.o

obj/lib/Commands/LogoutCommand.o: src/lib/Commands/LogoutCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/LogoutCommand.cpp -std=c++17 -o obj/lib/Commands/LogoutCommand.o

obj/lib/Commands/RegisterCommand.o: src/lib/Commands/RegisterCommand.cpp
	$(CC) $(FLAGS) src/lib/Commands/RegisterCommand.cpp -std=c++17 -o obj/lib/Commands/RegisterCommand.o


clean:
	rm -rf obj
	rm -f $(OUT)

run: $(OUT)
	./$(OUT)