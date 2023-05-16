#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

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
    PRINT("LoginCommand::executed");
    #endif
}

std::string LoginCommand::getUsername() {
    return this->username;
}

std::string LoginCommand::getPassword() {
    return this->password;
}