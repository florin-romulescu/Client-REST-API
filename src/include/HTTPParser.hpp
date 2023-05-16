#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <memory>
#include "utils.hpp"
#include "json.hpp"

namespace http {
    #include "input.hpp"
    #include <string>

    using json = nlohmann::json;

    enum OUTPUT_TYPE {
        ERROR,
        BOOK,
        BOOKS,
        JWT,
        COOKIE
    };

    class HTTPOutput {
        private:
            OUTPUT_TYPE type;
        public:
            virtual void display() = 0;
    };

    class HTTPParser {
        private:
            std::string method;
            std::string access_route;
            std::string payload_type;
            json payload;
            std::string cookie;
            std::string session_token;
            std::string query_params;
        public:
            HTTPParser();
            ~HTTPParser();
            HTTPParser* setMethod(std::string method);
            HTTPParser* setAccessRoute(std::string access_route);
            HTTPParser* setPayloadType(std::string payload_type);
            HTTPParser* setPayload(json payload);
            HTTPParser* setCookie(std::string cookie);
            HTTPParser* setSessionToken(std::string session_token);
            HTTPParser* setQueryParams(std::string query_params);
            std::string getMethod();
            std::string getAccessRoute();
            std::string getPayloadType();
            json getPayload();
            std::string getCookie();
            std::string getSessionToken();
            std::string getQueryParams();
            std::shared_ptr<std::string> toString();
            static void append_newline(std::shared_ptr<std::string> str);
    };

} // namespace http

#endif // HTTP_PARSER_HPP