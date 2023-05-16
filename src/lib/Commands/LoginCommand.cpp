#include "../../include/Command.hpp"
#include "../../include/Session.hpp"
#include "../../include/utils.hpp"

void LoginCommand::execute(std::shared_ptr<Input> input) {

    this->username = input->getUsername();
    this->password = input->getPassword();
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("POST");
    parser->setAccessRoute("/api/v1/tema/auth/login");
    parser->setPayloadType("application/json");
    parser->setPayload(nlohmann::json::parse(R"(
        {
            "username": ")" + this->username + R"(",
            "password": ")" + this->password + R"("
        }
    )"));

    #ifdef DEBUG
    {PRINT("LoginCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif

    utils::send(Session::session->getSocketFd(), parser->toString());
}

void respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        std::string cookie = utils::getSetCookie(response);
        Session::session->setCookie(cookie);
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
    }

    #ifdef DEBUG
    {PRINT("LoginCommand::response");}
    {PRINT(response.c_str());}
    #endif
}

std::string LoginCommand::getUsername() {
    return this->username;
}

std::string LoginCommand::getPassword() {
    return this->password;
}