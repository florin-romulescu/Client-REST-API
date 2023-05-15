#include "../../include/Command.hpp"

void LoginCommand::execute(std::shared_ptr<Input> input) {
    this->username = input->getUsername();
    this->password = input->getPassword();
    std::cout << "Login command executed" << std::endl;
}

std::string LoginCommand::getUsername() {
    return this->username;
}

std::string LoginCommand::getPassword() {
    return this->password;
}