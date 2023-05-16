#include "../include/HTTPParser.hpp"
using namespace http;

HTTPParser::HTTPParser() {
    this->method = "";
    this->access_route = "";
    this->payload_type = "";
    this->payload = json();
    this->cookie = "";
    this->session_token = "";
}

HTTPParser::~HTTPParser() {}

HTTPParser* HTTPParser::setMethod(std::string method) {
    this->method = method;
    return this;
}

HTTPParser* HTTPParser::setAccessRoute(std::string access_route) {
    this->access_route = access_route;
    return this;
}

HTTPParser* HTTPParser::setPayloadType(std::string payload_type) {
    this->payload_type = payload_type;
    return this;
}

HTTPParser* HTTPParser::setPayload(json payload) {
    this->payload = payload;
    return this;
}

HTTPParser* HTTPParser::setCookie(std::string cookie) {
    this->cookie = cookie;
    return this;
}

HTTPParser* HTTPParser::setSessionToken(std::string session_token) {
    this->session_token = session_token;
    return this;
}

HTTPParser* HTTPParser::setQueryParams(std::string query_params) {
    this->query_params = query_params;
    return this;
}

std::string HTTPParser::getMethod() {
    return this->method;
}

std::string HTTPParser::getAccessRoute() {
    return this->access_route;
}

std::string HTTPParser::getPayloadType() {
    return this->payload_type;
}

json HTTPParser::getPayload() {
    return this->payload;
}

std::string HTTPParser::getCookie() {
    return this->cookie;
}

std::string HTTPParser::getSessionToken() {
    return this->session_token;
}

std::string HTTPParser::getQueryParams() {
    return this->query_params;
}

void HTTPParser::append_newline(std::shared_ptr<std::string> str) {
    str->append("\r\n");
}

std::shared_ptr<std::string> HTTPParser::toString() {
    std::shared_ptr<std::string> output(new std::string());
    output->append(this->method);
    if (query_params != "") {
        output->append("?");
        output->append(query_params);
    } else {
        output->append(" ");
    }
    output->append(this->access_route);
    output->append(" HTTP/1.1");
    
    HTTPParser::append_newline(output);
    output->append("Host: ");
    output->append(SERVER_IP);
    output->append(":");
    output->append(std::to_string(SERVER_PORT));
    HTTPParser::append_newline(output);

    if (this->payload_type != "") {
        output->append("Content-Type: ");
        output->append(this->payload_type);
        HTTPParser::append_newline(output);
    }

    output->append("Connection: keep-alive");
    HTTPParser::append_newline(output);

    if (this->cookie != "") {
        output->append("Cookie: ");
        output->append(this->cookie);
        HTTPParser::append_newline(output);
    }

    if (this->getSessionToken() != "") {
        output->append("Authorization: Bearer ");
        output->append(this->getSessionToken());
        HTTPParser::append_newline(output);
    }

    if (method == "POST") {
        output->append("Content-Length: ");
        output->append(std::to_string(this->payload.dump().length()));
        HTTPParser::append_newline(output);
        HTTPParser::append_newline(output);
        output->append(this->payload.dump());
    } else if (method == "GET") {
        // output->append("Content-Length: 0");
        HTTPParser::append_newline(output);
    }

    HTTPParser::append_newline(output);
    return output;
}
