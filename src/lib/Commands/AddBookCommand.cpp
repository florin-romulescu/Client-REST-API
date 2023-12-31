#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void AddBookCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("POST");
    parser->setAccessRoute("/api/v1/tema/library/books");
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());
    nlohmann::json payload;
    payload["title"] = input->getBook().title;
    payload["author"] = input->getBook().author;
    payload["genre"] = input->getBook().genre;
    payload["publisher"] = input->getBook().publisher;
    payload["page_count"] = input->getBook().page_count;
    parser->setPayload(payload);

    #ifdef DEBUG
    {PRINT("AddBookCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif

    Session::session->requests->push(parser->toString());
}

void AddBookCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        // Nothing to do here
    } else if (statusCode == 201) {
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
    {PRINT("AddBookCommand::response");}
    {PRINT(response.c_str());}
    #endif
}