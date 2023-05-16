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

#define DEBUG

#define PRINT(message) \
std::ofstream fout("log.txt", std::ios_base::app); \
fout << message << std::endl; \
fout.close();


#define DIE(condition, message) \
if (condition) { \
    std::cerr << message << std::endl; \
    exit(EXIT_FAILURE); \
}
namespace utils {
    int connect(std::string ip, int port, int ip_type, int socket_type, int flag);
    void disconnect(int socket_fd);
    int send(int socket_fd, std::shared_ptr<std::string> message);
    std::shared_ptr<std::string> receive(int socket_fd);
} // namespace utils

#endif // UTILS_HPP