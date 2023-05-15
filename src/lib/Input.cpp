#include "../include/input.hpp"
#include "../include/Command.hpp"
#include <iostream>

Input::Input() {
    command = "";
    username = "";
    password = "";
    sessionToken = "";
    bookId = -1;
    book.title = "";
    book.author = "";
    book.genre = "";
    book.publisher = "";
    book.year = "";
}

Input::~Input() {
    // Destructor
}

Input* Input::setCommand(std::string command) {
    this->command = command;
    return this;
}

Input* Input::setUsername(std::string username) {
    this->username = username;
    return this;
}

Input* Input::setPassword(std::string password) {
    this->password = password;
    return this;
}

Input* Input::setSessionToken(std::string sessionToken) {
    this->sessionToken = sessionToken;
    return this;
}

Input* Input::setBook(struct Book book) {
    this->book = book;
    return this;
}

Input* Input::setBookId(int bookId) {
    this->bookId = bookId;
    return this;
}

std::string Input::getCommand() {
    return this->command;
}

std::string Input::getUsername() {
    return this->username;
}

std::string Input::getPassword() {
    return this->password;
}

std::string Input::getSessionToken() {
    return this->sessionToken;
}

struct Book Input::getBook() {
    return this->book;
}

int Input::getBookId() {
    return this->bookId;
}

void Input::mainLoop() {
    while (true) {    
        std::string command;
        std::cin >> command;
        std::shared_ptr<Input> input(new Input());
        std::unique_ptr<CommandFactory> cmdFactory(new CommandFactory());
        Command *cmd;

        input->setCommand(command);
        if (command == "login") {
            std::string username;
            std::string password;
            std::cout << "username="; std::cin >> username;
            std::cout << "password="; std::cin >> password;
            input->setUsername(username)
                 ->setPassword(password);
            cmd = cmdFactory->build(COMMAND_TYPE::LOGIN);
        } else if (command == "register") {
            std::string username;
            std::string password;
            std::cout << "username="; std::cin >> username;
            std::cout << "password="; std::cin >> password;
            input->setUsername(username)
                 ->setPassword(password);
            cmd = cmdFactory->build(COMMAND_TYPE::REGISTER);
        } else if (command == "enter_library") {
            cmd = cmdFactory->build(COMMAND_TYPE::ENTER_LIBRARY);
        } else if (command == "get_books") {
            cmd = cmdFactory->build(COMMAND_TYPE::GET_BOOKS);
        } else if (command == "get_book") {
            int id;
            std::cout << "id=";
            std::cin >> id;
            input->setBookId(id);
            cmd = cmdFactory->build(COMMAND_TYPE::GET_BOOK);
        } else if (command == "add_book") {
            std::string title;
            std::string author;
            std::string genre;
            std::string publisher;
            std::string year;
            std::cout << "title="; std::cin >> title;
            std::cout << "author="; std::cin >> author;
            std::cout << "genre="; std::cin >> genre;
            std::cout << "publisher="; std::cin >> publisher;
            std::cout << "year="; std::cin >> year;
            struct Book book;
            book.title = title;
            book.author = author;
            book.genre = genre;
            book.publisher = publisher;
            book.year = year;
            input->setBook(book);
            cmd = cmdFactory->build(COMMAND_TYPE::ADD_BOOK);
        } else if (command == "delete_book") {
            int id;
            std::cout << "id="; std::cin >> id;
            input->setBookId(id);
            cmd = cmdFactory->build(COMMAND_TYPE::DELETE_BOOK);
        } else if (command == "logout") {
            cmd = cmdFactory->build(COMMAND_TYPE::LOGOUT);
        } else if (command == "help") {
            cmd = cmdFactory->build(COMMAND_TYPE::HELP);
        } else if (command == "exit") {
            break;
        } else {
            cmd = cmdFactory->build(COMMAND_TYPE::INVALID);
        }
        cmd->execute(input);
        delete cmd;
    }
}
