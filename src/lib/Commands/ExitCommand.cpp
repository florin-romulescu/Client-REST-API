#include "../../include/Command.hpp"

void ExitCommand::execute(std::shared_ptr<Input> input) {
    std::cout << "Exit command executed" << std::endl;
}

void ExitCommand::respond(std::string response) {
    (void) response;
}