#include "../include/utils.hpp"

int utils::connect(std::string ip, int port, int ip_type, int socket_type, int flag) {
    char *ipc = new char[ip.length() + 1];
    strcpy(ipc, ip.c_str());
    int err = open_connection(ipc, port, ip_type, socket_type, flag);
    delete ipc;

    return err;
}

void utils::disconnect(int socket_fd) {
    close_connection(socket_fd);
}

int utils::send(int socket_fd, std::shared_ptr<std::string> message) {
    char* messagec = new char[message->length() + 1];
    strcpy(messagec, message->c_str());
    send_to_server(socket_fd, messagec);
    delete messagec;
    return 0;
}

std::string utils::receive(int socket_fd) {
    char* response = receive_from_server(socket_fd);
    std::string responsep(response);
    delete response;
    return responsep;
}

int utils::getErrorCode(std::string response) {
    int size = std::string("HTTP/1.1 ").length();
    std::string code = response.substr(size, 3);
    return std::stoi(code);
}

std::string utils::getSetCookie(std::string response) {
    int size = std::string("Set-Cookie: ").length();
    std::string cookie = response.substr(response.find("Set-Cookie: ") + size);
    cookie = cookie.substr(0, cookie.find("\r\n"));
    return cookie;
}

std::string utils::getBody(std::string response) {
    std::string jwt = response.substr(response.find("\r\n\r\n") + 4);
    return jwt;
}

// Path: src/lib/HTTPParser.cpp