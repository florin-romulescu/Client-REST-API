#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void GetBooksCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/library/books");
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    PRINT("GetBooksCommand::executed");
    #endif
}