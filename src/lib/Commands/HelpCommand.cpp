#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void HelpCommand::execute(std::shared_ptr<Input> input) {
    input=nullptr;
    std::cout << "Available commands:" << std::endl;
    std::cout << "1.login" << std::endl;
    std::cout << "2.register" << std::endl;
    std::cout << "3.enter_library" << std::endl;
    std::cout << "4.get_books" << std::endl;
    std::cout << "5.get_book" << std::endl;
    std::cout << "6.add_book" << std::endl;
    std::cout << "7.delete_book" << std::endl;
    std::cout << "8.logout" << std::endl;
    std::cout << "9.help" << std::endl;
    std::cout << "10.exit" << std::endl;
    Session::session->setLastCommandSuccess(true);
}

void HelpCommand::respond(std::string response) {
    (void) response;
}