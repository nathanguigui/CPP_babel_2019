#include <sqlite3.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>


enum states {
    new_account = 1,
    existing = 2,
    connected = 3,
};
class SipManager {
    public:
        SipManager(std::string db_path = "../user.db");
        ~SipManager();
        void trying_connection(char *request);
        int check_account_existing();
        int create_account();
        int update_account();
        std::stringstream options_header(char *);
        std::stringstream SipManager::OK_header(char *old_request)

    private:
        states is_connected;
        sqlite3 *_database;
        std::string ip;
        std::string username;
};