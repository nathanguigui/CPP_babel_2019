#include <sqlite3.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp> 


enum states {
    new_account = 1,
    existing = 2,
    connected = 3,
};

enum request_types {
    INVITE = 1,
    ACK = 2,
    BYE = 3,
    CANCEL = 4,
    REGISTER = 5,
    OPTIONS = 6,
    SUBSCRIBE = 7,
    NOTIFY = 8,
    INFO = 9,
    MESSAGE = 10,
    UPDATE = 11,
};

class SipManager {
    public:
        SipManager(std::string db_path = "../user.db");
        ~SipManager();
        void parse_header(std::string);
        void trying_connection(char *request);
        int check_account_existing();
        int create_account();
        int update_account();
        int add_friends(std::string friend_username);
        void get_friends(std::string _username);
        request_types get_request_types_request(std::string request);
        std::string get_IP_in_request(std::string request);
        std::string get_username_request(std::string request);
        std::string get_hostname_request(std::string request);
        std::string get_port_request(std::string request);
        std::string get_tag_client_request(std::string request);
        std::string get_callID(std::string request);
        std::stringstream options_header(char *);
        std::stringstream OK_header(char *old_request);
        std::stringstream notify_header(char *old_request);
        std::vector<std::string> my_friends;
    private:
        request_types types;
        std::string ip;
        std::string username;
        std::string hostname;
        std::string port;
        std::string tag_cli;
        std::string tag_server;
        std::string call_id;
        std::stringstream response_header;
        states is_connected;
        sqlite3 *_database;
};