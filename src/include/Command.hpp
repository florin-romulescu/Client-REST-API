#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <memory>
#include "input.hpp"
#include "HTTPParser.hpp"
#include "utils.hpp"

/*
* Abstract class for all client commands.
* Each command has an execute method that takes an input and a respond method
* for interacting with the server.
*/
class Command {
    public:
    virtual void execute(std::shared_ptr<Input> input) = 0;
    virtual void respond(std::string response) = 0;
    virtual ~Command() = default;
    std::shared_ptr<http::HTTPParser> parser;
};

// ------------------ Commands ------------------
/*
* All the below classes are implementations of the Command class.
* They will have additional fields for storing the data that is needed.
*/

class LoginCommand : public Command {
    private:
    std::string username;
    std::string password;
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
    LoginCommand() = default;
    std::string getUsername();
    std::string getPassword();
};

class RegisterCommand : public Command {
    private:
    std::string username;
    std::string password;
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
    RegisterCommand() = default;
    std::string getUsername();
    std::string getPassword();
};

class EnterLibraryCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class GetBooksCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class GetBookCommand : public Command {
    public:
    std::string id;
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class AddBookCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class DeleteBookCommand : public Command {
    public:
    std::string id;
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class LogoutCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class ExitCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class HelpCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

class InvalidCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
    void respond(std::string response) override;
};

// ------------------ Command Factory ------------------
/*
* The CommandFactory class is used to build commands.
* It has a build method that takes a COMMAND_TYPE and returns a pointer to a
* Command object.
* It uses the Factory design pattern.
*/
class CommandFactory {
    public:
    /*
    * The build method takes a COMMAND_TYPE and returns a pointer to a Command
    * object.
    * @param COMMAND_TYPE type - the type of the command to be built
    * @return Command* - pointer to a Command object
    */
    Command* build(COMMAND_TYPE type) {
        switch (type) {
            case COMMAND_TYPE::LOGIN:
                return new LoginCommand();
            case COMMAND_TYPE::REGISTER:
                return new RegisterCommand();
            case COMMAND_TYPE::ENTER_LIBRARY:
                return new EnterLibraryCommand();
            case COMMAND_TYPE::GET_BOOKS:
                return new GetBooksCommand();
            case COMMAND_TYPE::GET_BOOK:
                return new GetBookCommand();
            case COMMAND_TYPE::ADD_BOOK:
                return new AddBookCommand();
            case COMMAND_TYPE::DELETE_BOOK:
                return new DeleteBookCommand();
            case COMMAND_TYPE::LOGOUT:
                return new LogoutCommand();
            case COMMAND_TYPE::EXIT:
                return new ExitCommand();
            case COMMAND_TYPE::HELP:
                return new HelpCommand();
            default:
                return new InvalidCommand();
        }
    }
};

#endif // COMMAND_HPP