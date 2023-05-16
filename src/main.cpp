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

    // sockaddr_in server;
    // server.sin_family = AF_INET;
    // server.sin_port = htons(SERVER_PORT);
    // server.sin_addr.s_addr = inet_addr(SERVER_IP);

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

    do {
        poll(pollfds.data(), pollfds.size(), -1);
        for (int i = 0; i < (int)pollfds.size(); i++) {
            if (pollfds[i].revents & POLLIN) {
                if (pollfds[i].fd == 0) {
                    mode = Input::mainLoop();
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
                        continue;
                    }
                    CommandFactory cmdFactory;
                    Command* cmd = cmdFactory.build(mode);
                    cmd->respond(response);
                    delete cmd;
                }
            }
        }
    } while (mode != COMMAND_TYPE::EXIT);

    utils::disconnect(sockdfd);
    Session::end();

    #ifdef DEBUG
    std::cout << "Disconnected from server" << std::endl;
    #endif
    return 0;
}