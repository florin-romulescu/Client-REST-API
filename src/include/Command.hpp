#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <memory>
#include "input.hpp"
#include "HTTPParser.hpp"
#include "utils.hpp"

class Command {
    public:
    virtual void execute(std::shared_ptr<Input> input) = 0;
    virtual void respond(std::string response) = 0;
    virtual ~Command() = default;
    std::shared_ptr<http::HTTPParser> parser;
};

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