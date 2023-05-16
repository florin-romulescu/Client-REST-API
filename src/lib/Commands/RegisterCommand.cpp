#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void RegisterCommand::execute(std::shared_ptr<Input> input) {
    this->username = input->getUsername();
    this->password = input->getPassword();
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("POST");
    parser->setAccessRoute("/api/v1/tema/auth/register");
    parser->setPayloadType("application/json");
    parser->setPayload(nlohmann::json::parse(R"(
        {
            "username": ")" + this->username + R"(",
            "password": ")" + this->password + R"("
        }
    )"));
    #ifdef DEBUG
    {PRINT("RegisterCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif

    std::cout << "TEST" << std::endl;
    utils::send(Session::session->getSocketFd(), parser->toString());
    std::cout << "TEST" << std::endl;
    std::string response = utils::receive(Session::session->getSocketFd());
    std::cout << "TEST" << std::endl;
    #ifdef DEBUG
    {PRINT("RegisterCommand::response");}
    {PRINT(response.c_str());}
    #endif
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        return;
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
    }
}

std::string RegisterCommand::getUsername() {
    return this->username;
}

std::string RegisterCommand::getPassword() {
    return this->password;
}
