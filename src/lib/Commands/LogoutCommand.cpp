#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void LogoutCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/auth/logout");
    parser->setPayloadType("application/json");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    PRINT("LogoutCommand::executed");
    #endif

    Session::session->requests->push(parser->toString());}

void LogoutCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        Session::session->setCookie("");
        Session::session->setUsername("");
        Session::session->setPassword("");
        Session::session->setSessionToken("");
        Session::session->setLastCommandSuccess(true);
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
        Session::session->setLastCommandSuccess(false);
    }

    #ifdef DEBUG
    {PRINT("LogoutCommand::response");}
    {PRINT(response.c_str());}
    #endif
}