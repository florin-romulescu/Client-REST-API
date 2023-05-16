#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void DeleteBookCommand::execute(std::shared_ptr<Input> input) {
    this->id = input->getBookId();
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("DELETE");
    parser->setAccessRoute("/api/v1/tema/library/books/:" + this->id);
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    PRINT("DeleteBookCommand::executed");
    #endif
}