#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void AddBookCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("POST");
    parser->setAccessRoute("/api/v1/tema/library/books");
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());
    parser->setPayload(nlohmann::json::parse(R"(
        {
            "title": ")" + input->getBook().title + R"(",
            "author": ")" + input->getBook().author + R"(",
            "genre": ")" + input->getBook().genre + R"(",
            "page_count": )" + std::to_string(input->getBook().page_count) + R"(,
            "publisher": ")" + input->getBook().publisher + R"(",
        }
    )"));

    #ifdef DEBUG
    {PRINT("AddBookCommand::executed");}
    #endif

    utils::send(Session::session->getSocketFd(), parser->toString());
}

void AddBookCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 201) {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::cout << jsonBody.dump(4) << std::endl;
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
    }

    #ifdef DEBUG
    {PRINT("AddBookCommand::response");}
    {PRINT(response.c_str());}
    #endif
}