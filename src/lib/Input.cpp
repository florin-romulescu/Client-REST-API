#include "../include/input.hpp"
#include "../include/Command.hpp"
#include "../include/utils.hpp"
#include "../include/Session.hpp"
#include <iostream>
#include <fstream>

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

COMMAND_TYPE Input::mainLoop() {
    std::string command;
    std::getline(std::cin, command);
    if (command == "") {
        // Why? I have no idea, but it works
        command = "invalid";
    }
    std::shared_ptr<Input> input(new Input());
    std::unique_ptr<CommandFactory> cmdFactory(new CommandFactory());
    Command *cmd;
    COMMAND_TYPE cmdType;

    input->setCommand(command);
    if (command == "login") {
        std::string username;
        std::string password;
        std::cout << "username="; std::cout.flush(); std::getline(std::cin, username);
        std::cout << "password="; std::cout.flush(); std::getline(std::cin, password);
        input->setUsername(username)
                ->setPassword(password);
        cmd = cmdFactory->build(COMMAND_TYPE::LOGIN);
        cmdType = COMMAND_TYPE::LOGIN;
    } else if (command == "register") {
        std::string username;
        std::string password;
        std::cout << "username="; std::cout.flush(); std::getline(std::cin, username);
        std::cout << "password="; std::cout.flush(); std::getline(std::cin, password);
        input->setUsername(username)
                ->setPassword(password);
        cmd = cmdFactory->build(COMMAND_TYPE::REGISTER);
        cmdType = COMMAND_TYPE::REGISTER;
    } else if (command == "enter_library") {
        cmd = cmdFactory->build(COMMAND_TYPE::ENTER_LIBRARY);
        cmdType = COMMAND_TYPE::ENTER_LIBRARY;
    } else if (command == "get_books") {
        cmd = cmdFactory->build(COMMAND_TYPE::GET_BOOKS);
        cmdType = COMMAND_TYPE::GET_BOOKS;
    } else if (command == "get_book") {
        int id;
        std::string str;
        std::cout << "id=";
        std::getline(std::cin, str);
        id = std::stoi(str);
        input->setBookId(id);
        cmd = cmdFactory->build(COMMAND_TYPE::GET_BOOK);
        cmdType = COMMAND_TYPE::GET_BOOK;
    } else if (command == "add_book") {
        std::string title;
        std::string author;
        std::string genre;
        std::string publisher;
        int page_count;
        std::cout << "title="; std::cout.flush(); std::getline(std::cin, title);
        std::cout << "author="; std::cout.flush(); std::getline(std::cin, author);
        std::cout << "genre="; std::cout.flush(); std::getline(std::cin, genre);
        std::cout << "publisher="; std::cout.flush(); std::getline(std::cin, publisher);
        std::cout << "page_count="; std::cout.flush(); std::cin >> page_count;
        struct Book book;
        book.title = title;
        book.author = author;
        book.genre = genre;
        book.publisher = publisher;
        book.page_count = page_count;
        input->setBook(book);
        cmd = cmdFactory->build(COMMAND_TYPE::ADD_BOOK);
        cmdType = COMMAND_TYPE::ADD_BOOK;
    } else if (command == "delete_book") {
        int id;
        std::string str;
        std::cout << "id=";
        std::getline(std::cin, str);
        id = std::stoi(str);
        input->setBookId(id);
        cmd = cmdFactory->build(COMMAND_TYPE::DELETE_BOOK);
        cmdType = COMMAND_TYPE::DELETE_BOOK;
    } else if (command == "logout") {
        cmd = cmdFactory->build(COMMAND_TYPE::LOGOUT);
        cmdType = COMMAND_TYPE::LOGOUT;
    } else if (command == "help") {
        cmd = cmdFactory->build(COMMAND_TYPE::HELP);
        cmdType = COMMAND_TYPE::HELP;
    } else if (command == "exit") {
        return COMMAND_TYPE::EXIT;
    } else {
        cmd = cmdFactory->build(COMMAND_TYPE::INVALID);
        cmdType = COMMAND_TYPE::INVALID;
    }
    cmd->execute(input);
    delete cmd;
    return cmdType;
}
