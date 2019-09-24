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
int check_account_in_db(void *data, int argc, char **argv, char **azColName)
{
    if (argc > 0) {
        return argc;
    }
    return 0;
}

int create_account_in_db(void *data, int argc, char **argv, char **azColName)
{
    std::cout << argc << std::endl;
    return 1;
}

int update_db_account(void *data, int argc, char **argv, char **azColName)
{
    return (0);
}

int SipManager::update_account()
{
    std::string sql_request = "UPDATE user_db SET ip=\"";
    char *data; 
    char *zErrMsg = 0;

    sql_request = sql_request + ip;
    sql_request = sql_request + "\", state=1\n WHERE username=\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), update_db_account, data,&zErrMsg);
}
int SipManager::create_account()
{
    std::string sql_request;
    char *data; 
    char *zErrMsg = 0;

    sql_request = "INSERT into user_db(username, ip, state)\n";
    sql_request = sql_request + "VALUES (\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\", \"";
    sql_request = sql_request + ip;
    sql_request = sql_request + "\", 1)";
    sqlite3_exec(_database, sql_request.c_str(), create_account_in_db, data,&zErrMsg);
}
int SipManager::check_account_existing()
{
    std::string sql_request;
    char *data; 
    char *zErrMsg = 0;

    sql_request = "SELECT username FROM user_db\nWHERE username == \"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    if (sqlite3_exec(_database, sql_request.c_str(), check_account_in_db,data, &zErrMsg) != 0) {
        update_account();
    } else {
        create_account();
    }
    return (0);
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

void SipManager::trying_connection(char *request)
{
    std::string test = convertToString(request);
    auto ss = std::stringstream();
    ss << "SIP/2.0 100 Trying\nVia: SIP/2.0/UDP ";
    ip = get_IP_in_request(request);
    username = get_username(test);
    ss << ip << "\nFrom: " << get_user_in_request(test, 1) << "To: " << get_user_in_request(test, 0);
    ss << "\n" << get_callID(test) << "User-Agent: Asterisk PBX\n" << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\nSupported: replaces\nContact: " << get_user_in_request(test, 0).erase(0, username.size() + 2) << "\nContent-Length: 0\n";
    check_account_existing();
    options_header(request);
}
std::string get_IP_from_iface()
{
char hostbuffer[256]; 
    char *IPbuffer; 
    struct hostent *host_entry; 
    int hostname; 
  
    // To retrieve hostname 
    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
  
    // To retrieve host information 
    host_entry = gethostbyname(hostbuffer); 
  
    // To convert an Internet network 
    // address into ASCII string 
    IPbuffer = inet_ntoa(*((struct in_addr*) 
                           host_entry->h_addr_list[0])); 
    return convertToString(IPbuffer); 
}

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

std::stringstream SipManager::options_header(char *old_request)
{
    std::string request = convertToString(old_request);
    auto ss = std::stringstream();
    ss << "OPTIONS sip:1010@" << get_IP_from_iface() << ":25565;SIP/2.0";
    ss << "\nVia: SIP/2.0/UDP " << ip << "\nFrom:" << get_user_in_request(request, 1);
    ss << "To: <sip:1010@" << ip << "\nContact: <sip:"  << username << "@" << ip << ">";
    ss << "Call-ID: \n" << "CSeq: 102 OPTIONS\nUser-Agent:" << username << "\nMax-Forwards: 70\nDate: ";
    ss << make_daytime_string() << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\n";
    ss << "Supported: replaces\nContent-Length: 0";
    std::cout << request << std::endl;
    std::cout << ss.str() << std::endl;
    return ss;
}

std::stringstream SipManager::OK_header(char *old_request)
{
    
}