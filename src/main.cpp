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

void reconnect(int& sockdfd, std::vector<pollfd>& pollfds) {
     // Timeout
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
}

using json = nlohmann::json;

/*
*  This is the main function of the program
*  It will connect to the server and start the main loop
*  The main loop will wait for user input, store it in a buffer
*  and send it to the server when the server is up.
*  The main loop will also wait for server response and respond to it
*  accordingly.
*  @return 0 if the program exits successfully
*/
int main() {
    #ifdef DEBUG
    std::ofstream fout("log.txt");
    fout << std::endl;
    fout.close();
    #endif
    // Connect to server
    int sockdfd = utils::connect(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);

    std::vector<pollfd> pollfds;
    #ifdef DEBUG
    std::cout << "Connected to server" << std::endl;
    #endif
    // Add stdin and socket to pollfd
    pollfds.push_back({
        .fd = 0,
        .events = 0x0001,
        .revents = 0
    });
    // Add socket to pollfd
    pollfds.push_back({
        .fd = sockdfd,
        .events = 0x0001,
        .revents = 0
    });

    COMMAND_TYPE mode = COMMAND_TYPE::LOGIN; // not important

    Session* session = Session::start();
    session->setSocketFd(sockdfd);
    // This variable is used for prompt printing
    bool command_running = true;

    #define TIMEOUT 4000

    do {
        // Print prompt
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
        int ret = poll(pollfds.data(), pollfds.size(), TIMEOUT);
        if (ret == 0) {
            // Timeout
            reconnect(sockdfd, pollfds);
            command_running = false;
            continue;
        } else if (ret == -1) {
            // Error
            #ifdef DEBUG
            std::cout << "Error" << std::endl;
            #endif
            continue;
        }
        for (int i = 0; i < (int)pollfds.size(); i++) {
            if (pollfds[i].revents & POLLIN) {
                if (pollfds[i].fd == 0) {
                    mode = Input::mainLoop();
                    if (mode == COMMAND_TYPE::HELP || mode == COMMAND_TYPE::INVALID) {
                        command_running = true;
                    } else {
                        command_running = false;
                    }
                } else {
                    std::string response = utils::receive(sockdfd);
                    if (response == "") {
                        reconnect(sockdfd, pollfds);
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
        // Reconnect to server
        reconnect(sockdfd, pollfds);
        // Send requests
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