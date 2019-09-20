#include "SipManager.hpp"

SipManager::SipManager(std::string db_path)
{
    sqlite3_open(db_path.c_str(), &_database);
}

SipManager::~SipManager()
{

}

std::string convertToString(char* a) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; a[i]; i++) { 
        s = s + a[i]; 
    } 
    return s; 
}
std::string get_IP_in_request(std::string request)
{
    request.erase(0, request.find("UDP") + 4);
    return (request.erase(request.find("To:") -2, std::string::npos));
}

std::string get_user_in_request(std::string request, int tag_id)
{
    request.erase(0, request.find("From:") + 6);
    if (tag_id == 1) {
        return (request.erase(request.find("Call-ID"), std::string::npos));
    } else {
        return (request.erase(request.find(";tag"), std::string::npos));
    }
}

std::string get_callID(std::string request)
{
    return(request.erase(0, request.find("Call-ID")));
}

std::string get_username(std::string request)
{
    request.erase(0, request.find("\"") + 1);
    request.erase(request.find("\""), std::string::npos);
    return (request);
}
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int SipManager::check_account_existing()
{
    std::string sql_request;
    char *data = "Callback function called"; 
    char *zErrMsg = 0;

    sql_request = "SELECT username FROM user_db\nWHERE username == \"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    std::cout << sql_request << std::endl;
    sqlite3_exec(_database, sql_request.c_str(), callback,data, &zErrMsg);
    return (0);
}

void SipManager::trying_connection(char *request)
{
    std::string test = convertToString(request);
    auto ss = std::stringstream();
    ss << "SIP/2.0 100 Trying\nVia: SIP/2.0/UDP ";
    ip = get_IP_in_request(request);
    username = get_username(test);
    ss << ip << "\nFrom: " << get_user_in_request(test, 1) << "To: " << get_user_in_request(test, 0);
    ss << "\n" << get_callID(test) << "User-Agent: Asterisk PBX\n" << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\nSupported: replaces\nContact: " << get_user_in_request(test, 0).erase(0, username.size() + 2) << "\nContent-Length: 0\n";
    std::cout << ss.str();
    check_account_existing();
}