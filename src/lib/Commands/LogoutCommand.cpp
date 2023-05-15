#include "../../include/Command.hpp"

void LogoutCommand::execute(std::shared_ptr<Input> input) {
    std::cout << "Logout command executed" << std::endl;
}