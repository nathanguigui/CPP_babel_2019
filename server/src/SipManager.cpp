#include "SipManager.hpp"

SipManager::SipManager(std::string db_path)
{
    sqlite3_open(db_path.c_str(), &_database);
    tag_server = "tag=823f843c";
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
int parse_friends(void *data, int argc, char **argv, char **azColName)
{
    SipManager *my_manager = static_cast<SipManager*>(data);
    std::string buff;
    if (argc > 1) {
        buff = convertToString(argv[argc - 1]);
        boost::split(my_manager->my_friends, buff, boost::is_any_of(" "));
    }
    return 0;
}

void SipManager::get_friends(std::string _username)
{
    char *data; 
    char *zErrMsg = 0;
    std::string sql_request = "SELECT friend FROM user_db\nWHERE username == \"";
    sql_request = sql_request + _username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), parse_friends, this,&zErrMsg);
}

int handler_add_friends(void *data, int argc, char **argv, char **azColName)
{}

int SipManager::add_friends(std::string friend_username)
{
    char *data; 
    char *zErrMsg = 0;

    get_friends(username);
    my_friends.push_back(friend_username);
    std::string sql_request = "UPDATE user_db SET friend=\"";
    for (int i = 0; i < my_friends.size(); i++) {
        sql_request = sql_request + my_friends[i];
        sql_request = sql_request + " ";
    }
    sql_request = sql_request + "\"";
    sql_request = sql_request + "WHERE username==\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), handler_add_friends, this,&zErrMsg);
    my_friends.clear();
    get_friends(friend_username);
    my_friends.push_back(username);
    sql_request = "UPDATE user_db SET friend=\"";
    for (int i = 0; i < my_friends.size(); i++) {
        sql_request = sql_request + my_friends[i];
        sql_request = sql_request + " ";
    }
    sql_request = sql_request + "\"";
    sql_request = sql_request + "WHERE username==\"";
    sql_request = sql_request + friend_username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), handler_add_friends, this,&zErrMsg);
    get_friends(friend_username);
}


void SipManager::parse_header(std::string request)
{
    types = get_request_types_request(request);
    ip = get_IP_in_request(request);
    username = get_username_request(request);
    hostname = get_hostname_request(request);
    port = get_port_request(request);
    tag_cli = get_tag_client_request(request);
    call_id = get_callID(request);
    add_friends("ref");
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

request_types SipManager::get_request_types_request(std::string request)
{
    std::string rtypes = request.substr(0, request.find(" "));
    switch (str2int(rtypes.c_str())) {
        case str2int("INVITE"):
            return request_types::INVITE;
        case str2int("ACK"):
            return request_types::ACK;
        case str2int("BYE"):
            return request_types::BYE;
        case str2int("CANCEL"):
            return request_types::CANCEL;
        case str2int("REGISTER"):
            return request_types::REGISTER;
        case str2int("OPTIONS"):
            return request_types::OPTIONS;
        case str2int("SUBSCRIBE"):
            return request_types::SUBSCRIBE;
        case str2int("NOTIFY"):
            return request_types::NOTIFY;
        case str2int("INFO"):
            return request_types::INFO;
        case str2int("MESSAGE"):
            return request_types::MESSAGE;
        case str2int("UPDATE"):
            return request_types::UPDATE;
    }
}

std::string SipManager::get_IP_in_request(std::string request)
{
    request.erase(0, request.find("sip:") + 4);
    return (request.substr(0, request.find("SIP/2.0") - 1));
}

std::string SipManager::get_username_request(std::string request)
{
    request.erase(0, request.find("\"") + 1);
    request.erase(request.find("\""), std::string::npos);
    return (request);
}

std::string SipManager::get_hostname_request(std::string request)
{
    request.erase(0, request.find("\"<") + 2);
    return(request.substr(0, request.find("@")));
}

std::string SipManager::get_port_request(std::string request)
{
    request.erase(0, request.find(hostname));
    request.erase(0, request.find(ip) + ip.size() + 1);
    return (request.substr(0, request.find(">")));
}
std::string SipManager::get_tag_client_request(std::string request)
{
    request.erase(0, request.find(";tag=") + 5);
    return(request.substr(0, request.find("Call-ID") - 1));
}

std::string SipManager::get_callID(std::string request)
{
    request.erase(0, request.find("Call-ID") + 9);
    return(request.erase(request.find("CSeq") - 3, std::string::npos));
}
/*std::string get_user_in_request(std::string request, int tag_id)
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
    request.erase(0, request.find("Call-ID"));
    return(request.erase(request.find("CSeq"), std::string::npos));
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

void SipManager::trying_connection(char *request)
{
    std::string test = convertToString(request);
    auto ss = std::stringstream();
    ss << "SIP/2.0 100 Trying\nVia: SIP/2.0/UDP ";
    ip = get_IP_in_request(request);
    username = get_username(test);
    ss << ip << "\nFrom: " << get_user_in_request(test, 1) << "To: " << get_user_in_request(test, 0);
    ss << "\n" << get_callID(test) << "CSeq: 2 REGISTER\n"<<"User-Agent: Asterisk PBX\n" << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\nSupported: replaces\nContact: " << get_user_in_request(test, 0).erase(0, username.size() + 2) << "\nContent-Length: 0";
    check_account_existing();
    options_header(request);
}

std::stringstream SipManager::options_header(char *old_request)
{
    std::string request = convertToString(old_request);
    auto ss = std::stringstream();
    ss << "OPTIONS sip:1010@" << get_IP_from_iface() << ":25565";
    ss << "\nVia: SIP/2.0/UDP " << ip << "\nFrom: " << get_user_in_request(request, 0) << ";" << tag_server;
    ss << "\nTo: <sip:1010@" << ip << "\nContact: <sip:"  << username << "@" << ip << ">\n";
    ss << get_callID(request) << "CSeq: 102 OPTIONS\nUser-Agent: " << username << "\nMax-Forwards: 70\nDate: ";
    ss << make_daytime_string() << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\n";
    ss << "Supported: replaces\nContent-Length: 0";
    OK_header(old_request);
    return ss;
}

std::stringstream SipManager::OK_header(char *old_request)
{
    auto ss = std::stringstream();
    std::string request = convertToString(old_request);
    ss << "SIP/2.0 200 OK\nVia: SIP/2.0/UDP " << ip << "\n";
    ss << "From:" << get_user_in_request(request, 1) << "To:" << get_user_in_request(request, 0) << ";"<< tag_server;
    ss << "\n"<< get_callID(request) << "CSeq: 2 REGISTER\n" <<"User-Agent:" << username;
    ss << "\nAllow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY\n";
    ss << "Supported: replaces\nExpires: 3600\nContact: " << get_user_in_request(request, 0).erase(0, username.size() + 2) << "\nDate: " << make_daytime_string() << "Content-Length: 0";
    notify_header(old_request);
    return ss;
}

std::stringstream SipManager::notify_header(char *old_request)
{
    auto ss = std::stringstream();
    std::string request = convertToString(old_request);
    ss << "NOTIFY sip:1010@" << ip << "\nVia: SIP/2.0/UDP" << get_IP_from_iface() << ":25565\nFrom: " << get_user_in_request(request, 1);
    ss << "To: sip:sip:1010@" << get_IP_from_iface() << ":25565>;" << tag_server;
    ss << "\nContact: " << get_user_in_request(request, 0).erase(0, username.size() + 2);
    ss << get_callID << "\nCSeq: 102 NOTIFY\nUser-Agent: " << username << "\nMax-Forwards: 70\nEvent: message-summary\n";
    ss << "Content-Type: application/simple-message-summary" << "Subscription-State: active\nContent-Length: <" << 10;
    ss << "Messages-Waiting: no\nMessage-Account: sip:" << username << "@" << get_IP_from_iface();
    std::cout << ss.str() << std::endl;
    return (ss);
}
*/