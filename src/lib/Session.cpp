#include "../include/Session.hpp"

Session* Session::session = nullptr;

Session::Session() {
    this->sessionToken = "";
    this->username = "";
    this->password = "";
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

// Path: src/lib/CommandFactory.cpp
