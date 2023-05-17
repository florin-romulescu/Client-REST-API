#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <memory>
#include "utils.hpp"
#include "json.hpp"

namespace http {
    #include "input.hpp"
    #include <string>

    using json = nlohmann::json;

    /*
    * This class is used for parsing HTTP requests
    * It will parse the request and store the data in the class fields
    * The class fields can be accessed using the getters
    * The class fields can be set using the setters
    */
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
            /*
            * This method will return a proper http request string
            * that can be sent to the server.
            * @return std::shared_ptr<std::string> - the http request string
            */
            std::shared_ptr<std::string> toString();
            /*
            * This method will append \r\n to the end of the string.
            * @param str - the string to append to
            */
            static void append_newline(std::shared_ptr<std::string> str);
    };

} // namespace http

#endif // HTTP_PARSER_HPP