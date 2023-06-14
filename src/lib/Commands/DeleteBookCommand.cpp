#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void DeleteBookCommand::execute(std::shared_ptr<Input> input) {
    this->id = std::to_string(input->getBookId());
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("DELETE");
    parser->setAccessRoute("/api/v1/tema/library/books/" + this->id);
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    {PRINT("DeleteBookCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif
    Session::session->requests->push(parser->toString());
}

void DeleteBookCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        // Nothing to do here
        Session::session->setLastCommandSuccess(true);
    } else if (statusCode == 201) {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::cout << jsonBody.dump(4) << std::endl;
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
        Session::session->setLastCommandSuccess(false);
    }

    #ifdef DEBUG
    {PRINT("DeleteBookCommand::response");}
    {PRINT(response.c_str());}
    #endif
}
