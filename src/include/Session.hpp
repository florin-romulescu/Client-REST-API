#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <memory>

/*
* Session class
* This class is used for storing session information
* like the session token, username, password and
* whether the user is logged in or not.
* This class is a singleton.
* Use the start() method to create a new session.
* Use the end() method to end a session.
*/
class Session {
    private:
        std::string sessionCookie;
        std::string sessionToken;
        std::string username;
        std::string password;
        Session();
    public:
        ~Session();
        static Session* session;
        static Session* start();
        static void end();
        std::string getSessionToken();
        std::string getCookie();
        std::string getUsername();
        std::string getPassword();
        void setSessionToken(std::string sessionToken);
        void setUsername(std::string username);
        void setPassword(std::string password);
        void setCookie(std::string cookie);
};

#endif // SESSION_HPP