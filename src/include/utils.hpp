#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <memory>
#include <fstream>
#include <string.h>
#include "helpers/buffer.h"
#include "helpers/helpers.h"

#define SERVER_IP "34.254.242.81"
#define SERVER_PORT 8080

// #define DEBUG // Uncomment this line to enable debug mode

#define PRINT(message) \
std::ofstream fout("log.txt", std::ios_base::app); \
fout << message << std::endl; \
fout.close();

#define DIE(condition, message) \
if (condition) { \
    std::cerr << message << std::endl; \
    exit(EXIT_FAILURE); \
}

enum COMMAND_TYPE {
            LOGIN = 0,
            REGISTER = 1,
            ENTER_LIBRARY = 2,
            GET_BOOKS = 3,
            GET_BOOK = 4,
            ADD_BOOK = 5,
            DELETE_BOOK = 6,
            LOGOUT = 7,
            EXIT = 8,
            HELP = 9,
            INVALID = 10
        };

namespace utils {
    enum RUN_MODE {
        CONTINUE,
        STOP
    };
    // The bellow actions are wrappers over the c alternatives from the helpers directory
    int connect(std::string ip, int port, int ip_type, int socket_type, int flag);
    void disconnect(int socket_fd);
    int send(int socket_fd, std::shared_ptr<std::string> message);
    std::string receive(int socket_fd);
    // ---------------------------- //

    /*
    * The function will extract the status code from
    * the response received from the server.
    * @param response The response received from the server
    * @return The status code
    */
    int getErrorCode(std::string response);

    /*
    * The function will extract the cookie from
    * the Set-Cookie header received from the server.
    * @param response The response received from the server
    * @return The cookie
    */
    std::string getSetCookie(std::string response);

    /*
    * The function will extract the body from
    * the response received from the server.
    * @param response The response received from the server
    * @return The body
    */
    std::string getBody(std::string response);
} // namespace utils

#endif // UTILS_HPP