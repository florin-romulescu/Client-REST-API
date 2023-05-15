#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <memory>
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
        public:
            HTTPParser();
            ~HTTPParser();
            
    };

} // namespace http

#endif // HTTP_PARSER_HPP