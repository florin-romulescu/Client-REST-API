#include "include/json.hpp"
#include "include/input.hpp"
#include "include/HTTPParser.hpp"
#include "include/utils.hpp"
#include "include/Session.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    #ifdef DEBUG
    std::ofstream fout("log.txt");
    fout << std::endl;
    fout.close();
    #endif

    int sockdfd = utils::connect(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    #ifdef DEBUG
    std::cout << "Connected to server" << std::endl;
    #endif
    Session* session = Session::start();

    Input::mainLoop();

    utils::disconnect(sockdfd);
    Session::end();
    #ifdef DEBUG
    std::cout << "Disconnected from server" << std::endl;
    #endif
    return 0;
}