#include "../../include/Command.hpp"

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
    PRINT("RegisterCommand::executed");
    #endif
}

std::string RegisterCommand::getUsername() {
    return this->username;
}

std::string RegisterCommand::getPassword() {
    return this->password;
}
