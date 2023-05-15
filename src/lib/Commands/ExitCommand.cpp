#include "../../include/Command.hpp"

void ExitCommand::execute(std::shared_ptr<Input> input) {
    std::cout << "Exit command executed" << std::endl;
}