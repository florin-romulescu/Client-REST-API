#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void GetBookCommand::execute(std::shared_ptr<Input> input) {
    this->id = std::to_string(input->getBookId());
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/library/books/" + this->id);
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    {PRINT("GetBookCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif

    Session::session->requests->push(parser->toString());}

void GetBookCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::cout << jsonBody.dump(4) << std::endl;
        Session::session->setLastCommandSuccess(true);
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
        Session::session->setLastCommandSuccess(false);
    }

    #ifdef DEBUG
    {PRINT("GetBookCommand::response");}
    {PRINT(response.c_str());}
    #endif
}