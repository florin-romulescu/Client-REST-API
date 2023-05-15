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

std::shared_ptr<std::string> utils::receive(int socket_fd) {
    char* response = receive_from_server(socket_fd);
    std::shared_ptr<std::string> responsep(new std::string(response));
    delete response;
    return responsep;
}

// Path: src/lib/HTTPParser.cpp