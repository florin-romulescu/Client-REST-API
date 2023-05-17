#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void GetBooksCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/library/books");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    {PRINT("GetBooksCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif

    // utils::send(Session::session->getSocketFd(), parser->toString());
    Session::session->requests->push(parser->toString());}

void GetBooksCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    std::cout << statusCode << std::endl;
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
    {PRINT("GetBooksCommand::response");}
    {PRINT(response.c_str());}
    #endif
}