#include <sqlite3.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
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
    private:
        states is_connected;
        sqlite3 *_database;
        std::string ip;
        std::string username;
};