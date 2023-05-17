#include "../include/Session.hpp"

Session* Session::session = nullptr;

Session::Session() {
    this->sessionToken = "";
    this->username = "";
    this->password = "";
    this->lastCommandSuccess = true;
    this->requests = std::make_shared<std::queue<std::shared_ptr<std::string>>>();
}

Session::~Session() {}

Session* Session::start() {
    if (Session::session == nullptr) {
        Session::session = new Session();
    }
    return Session::session;
}

void Session::end() {
    if (session != nullptr) {
        delete session;
        session = nullptr;
    }
}

std::string Session::getSessionToken() {
    return this->sessionToken;
}

std::string Session::getUsername() {
    return this->username;
}

std::string Session::getPassword() {
    return this->password;
}

void Session::setSessionToken(std::string sessionToken) {
    this->sessionToken = sessionToken;
}

void Session::setUsername(std::string username) {
    this->username = username;
}

void Session::setPassword(std::string password) {
    this->password = password;
}

std::string Session::getCookie() {
    return this->sessionCookie;
}

void Session::setCookie(std::string cookie) {
    this->sessionCookie = cookie;
}

void Session::setSocketFd(int sockdfd) {
    this->sockdfd = sockdfd;
}

int Session::getSocketFd() {
    return this->sockdfd;
}

void Session::setLastCommandSuccess(bool success) {
    this->lastCommandSuccess = success;
}

bool Session::getLastCommandSuccess() {
    return this->lastCommandSuccess;
}

// Path: src/lib/CommandFactory.cpp
