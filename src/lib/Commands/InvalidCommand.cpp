#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void InvalidCommand::execute(std::shared_ptr<Input> input) {
    input=nullptr;
    std::cout << "Invalid command! Execute help to get a list of commands" << std::endl;
    Session::session->setLastCommandSuccess(false);
}

void InvalidCommand::respond(std::string response) {
    (void) response;
}