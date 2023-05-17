#include "include/json.hpp"
#include "include/input.hpp"
#include "include/HTTPParser.hpp"
#include "include/utils.hpp"
#include "include/Session.hpp"
#include "include/Command.hpp"
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>


using json = nlohmann::json;

int main() {
    #ifdef DEBUG
    std::ofstream fout("log.txt");
    fout << std::endl;
    fout.close();
    #endif

    int sockdfd = utils::connect(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);

    std::vector<pollfd> pollfds;
    #ifdef DEBUG
    std::cout << "Connected to server" << std::endl;
    #endif

    pollfds.push_back({
        .fd = 0,
        .events = 0x0001,
        .revents = 0
    });

    pollfds.push_back({
        .fd = sockdfd,
        .events = 0x0001,
        .revents = 0
    });

    COMMAND_TYPE mode = COMMAND_TYPE::LOGIN; // not important

    Session* session = Session::start();
    session->setSocketFd(sockdfd);

    #define TIMEOUT 4000
    bool command_running = true;

    do {
        if (command_running) {
            std::cout << "[";
            if (Session::session->getLastCommandSuccess()) {
                std::cout << "\033[1;32m";
                std::cout << "OK";
            } else {
                std::cout << "\033[1;31m";
                std::cout << "FAIL";
            }
            std::cout << "\033[0m" << "]> ";
            std::cout.flush();
        }
        poll(pollfds.data(), pollfds.size(), -1);
        for (int i = 0; i < (int)pollfds.size(); i++) {
            if (pollfds[i].revents & POLLIN) {
                if (pollfds[i].fd == 0) {
                    mode = Input::mainLoop();
                    command_running = false;
                } else {
                    std::string response = utils::receive(sockdfd);
                    if (response == "") {
                        #ifdef DEBUG
                        std::cout << "Server disconnected" << std::endl;
                        #endif
                        // Reconnect to server
                        utils::disconnect(sockdfd);
                        sockdfd = utils::connect(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
                        pollfds[1].fd = sockdfd;
                        #ifdef DEBUG
                        std::cout << "Reconnected to server" << std::endl;
                        #endif
                        command_running = false;
                        continue;
                    }
                    CommandFactory cmdFactory;
                    Command* cmd = cmdFactory.build(mode);
                    cmd->respond(response);
                    delete cmd;
                    command_running = true;
                }
            }
        }
        while (!Session::session->requests->empty()) {
            std::shared_ptr<std::string> request = Session::session->requests->front();
            Session::session->requests->pop();
            utils::send(sockdfd, request);
        }
    } while (mode != COMMAND_TYPE::EXIT);

    utils::disconnect(sockdfd);
    Session::end();

    #ifdef DEBUG
    std::cout << "Disconnected from server" << std::endl;
    #endif
    return 0;
}