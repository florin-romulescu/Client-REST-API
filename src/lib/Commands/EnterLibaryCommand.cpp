#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void EnterLibraryCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/library/access");
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    PRINT("EnterLibraryCommand::executed");
    #endif
}