#include "../../include/Command.hpp"

void RegisterCommand::execute(std::shared_ptr<Input> input) {
    std::cout << "Register command executed" << std::endl;
}

std::string RegisterCommand::getUsername() {
    return this->username;
}

std::string RegisterCommand::getPassword() {
    return this->password;
}
