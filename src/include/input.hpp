#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <memory>
#include "utils.hpp"

struct Book {
    std::string title;
    std::string author;
    std::string genre;
    std::string publisher;
    std::string year;
    int page_count;
};

/*
* Input class
* This class is used for handling input from the user
* and parsing it into a proper command.
*/
class Input {
    private:
        std::string command;
        std::string username;
        std::string password;
        std::string sessionToken;
        int bookId;
        struct Book book;

    public:
        Input();
        ~Input();
        /*
        * This method is used for retrieving input from the user
        * and parsing it into a proper command that will be executed.
        * The command is build using the CommandFactory class. 
        */
        static COMMAND_TYPE mainLoop();

        // Setters
        Input* setCommand(std::string command);
        Input* setUsername(std::string username);
        Input* setPassword(std::string password);
        Input* setSessionToken(std::string sessionToken);
        Input* setBook(struct Book book);
        Input* setBookId(int bookId);

        // Getters
        std::string getCommand();
        std::string getUsername();
        std::string getPassword();
        std::string getSessionToken();
        struct Book getBook();
        int getBookId();
};

#endif // INPUT_HPP