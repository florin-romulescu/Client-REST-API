#include "../../include/Command.hpp"
#include "../../include/Session.hpp"

void EnterLibraryCommand::execute(std::shared_ptr<Input> input) {
    parser = std::make_shared<http::HTTPParser>(http::HTTPParser());
    parser->setMethod("GET");
    parser->setAccessRoute("/api/v1/tema/library/access");
    parser->setCookie(Session::session->getCookie());
    parser->setSessionToken(Session::session->getSessionToken());

    #ifdef DEBUG
    {PRINT("EnterLibraryCommand::executed");}
    {PRINT(parser->toString()->c_str());}
    #endif
    utils::send(Session::session->getSocketFd(), parser->toString());
}

void EnterLibraryCommand::respond(std::string response) {
    int statusCode = utils::getErrorCode(response);
    if (statusCode == 200) {
        std::string jwt = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(jwt);
        jwt = jsonBody["token"];
        Session::session->setSessionToken(jwt);
        #ifdef DEBUG
        {std::cout << "EnterLibraryCommand::respond: " << jwt << std::endl;}
        #endif
    } else {
        std::string body = utils::getBody(response);
        nlohmann::json jsonBody = nlohmann::json::parse(body);
        std::string message = jsonBody["error"];
        std::cerr << message << std::endl;
    }

    #ifdef DEBUG
    {PRINT("EnterLibraryCommand::response");}
    {PRINT(response.c_str());}
    #endif
}
