#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <memory>
#include "input.hpp"
#include "HTTPParser.hpp"
#include "utils.hpp"

enum COMMAND_TYPE {
            LOGIN = 0,
            REGISTER = 1,
            ENTER_LIBRARY = 2,
            GET_BOOKS = 3,
            GET_BOOK = 4,
            ADD_BOOK = 5,
            DELETE_BOOK = 6,
            LOGOUT = 7,
            EXIT = 8,
            HELP = 9,
            INVALID = 10
        };

class Command {
    public:
    virtual void execute(std::shared_ptr<Input> input) = 0;
    virtual ~Command() = default;
    std::shared_ptr<http::HTTPParser> parser;
};

class LoginCommand : public Command {
    private:
    std::string username;
    std::string password;
    public:
    void execute(std::shared_ptr<Input> input) override;
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
    RegisterCommand() = default;
    std::string getUsername();
    std::string getPassword();
};

class EnterLibraryCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class GetBooksCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class GetBookCommand : public Command {
    public:
    std::string id;
    void execute(std::shared_ptr<Input> input) override;
};

class AddBookCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class DeleteBookCommand : public Command {
    public:
    std::string id;
    void execute(std::shared_ptr<Input> input) override;
};

class LogoutCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class ExitCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class HelpCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class InvalidCommand : public Command {
    public:
    void execute(std::shared_ptr<Input> input) override;
};

class CommandFactory {
    public:
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