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
    PRINT("AddBookCommand::executed");
    #endif
}