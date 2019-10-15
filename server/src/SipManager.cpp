#include "../includes/SipManager.hpp"

SipManager::SipManager(std::string db_path)
{
    sqlite3_open(db_path.c_str(), &_database);
    tag_server = "tag=823f843c";
    port_server = "25565";
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
    //std::cout << argc << std::endl;
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

    sql_request = "INSERT into user_db(username, ip, state, friend)\n";
    sql_request = sql_request + "VALUES (\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\", \"";
    sql_request = sql_request + ip;
    sql_request = sql_request + "\", 1 ,\" \")";
    std::cout << sql_request << std::endl;
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
        return 1;
    } else {
        create_account();
        return 0;
    }
    return (0);
}

int parse_all_data(void *data, int argc, char **argv, char **azColName)
{
    int i = 0; 
    SipManager *my_manager = static_cast<SipManager*>(data);
    std::string buff;
  
    while (i < argc) {
        if (my_manager->get_username().compare(convertToString(argv[i])) != 0) {
            buff = convertToString(argv[i]) + ";";
            buff = buff + convertToString(argv[i + 1]) + ";";
            buff = buff + convertToString(argv[i + 2]);
            my_manager->my_friends.push_back(buff);
        }
        i = i + 3;
    }
    return 0; 
}

void SipManager::get_all_data_from_db()
{
    char *data;
    char *zErrMsg = 0;
    std::string sql_request = "SELECT username, ip, state from user_db\n";
    sqlite3_exec(_database, sql_request.c_str(), parse_all_data, this,&zErrMsg);
}

int parse_friends(void *data, int argc, char **argv, char **azColName)
{
    SipManager *my_manager = static_cast<SipManager*>(data);
    std::string buff;
    if (argc >= 1) {
        buff = convertToString(argv[argc - 1]);
        //std::cout << buff << "<- Buffer\n";
        boost::split(my_manager->my_friends, buff, boost::is_any_of(";"));
    }
    return 0;
}

int set_states(void *data, int argc, char **argv, char **azColName)
{
    return 0;
}

void SipManager::change_state()
{
    char *data;
    char *zErrMsg = 0;
    std::string sql_request = "UPDATE user_db SET state=0 WHERE username==\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), set_states, this,&zErrMsg);

}

void SipManager::get_friends(std::string _username)
{
    char *data; 
    char *zErrMsg = 0;
    std::string sql_request = "SELECT friend FROM user_db\nWHERE username == \"";
    sql_request = sql_request + _username;
    sql_request = sql_request + "\"";
    //std::cout << sql_request << "Request Send to add my_friend\n";
    sqlite3_exec(_database, sql_request.c_str(), parse_friends, this,&zErrMsg);
}

int handler_add_friends(void *data, int argc, char **argv, char **azColName)
{}

int return_data_friends(void *data, int argc, char **argv, char **azColName)
{
    SipManager *my_manager = static_cast<SipManager*>(data);
    if (argc >= 1) {
        my_manager->friend_str = convertToString(argv[argc - 1]);
    }
    return 0;
}
void SipManager::get_friends_data()
{
    int i = 0;
    char *data;
    char *zErrMsg = 0;
    my_friends.clear();
    get_friends(username);
    if (my_friends.size() > 1) {
        std::string sql_request = "SELECT username, ip, state FROM user_db\nWHERE ";
        std::cout << sql_request << std::endl;
        std::cout << my_friends.size() << std::endl;
        for (i = 0; i < my_friends.size() - 1; i++) {
            sql_request = sql_request + "username == \"";
            sql_request = sql_request + my_friends[i];
            sql_request = sql_request + "\" or ";
        }
        sql_request = sql_request + "username == \"";
        sql_request = sql_request + my_friends[i];
        sql_request = sql_request + "\"";
        my_friends.clear();
        sqlite3_exec(_database, sql_request.c_str(), parse_all_data, this,&zErrMsg);
    }
}



void SipManager::get_friends_in_str(std::string _username)
{
    char *data; 
    char *zErrMsg = 0;
    std::string sql_request = "SELECT friend FROM user_db\nWHERE username == \"";
    sql_request = sql_request + _username;
    sql_request = sql_request + "\"";
    //std::cout << sql_request << "Request Send to add my_friend\n";
    sqlite3_exec(_database, sql_request.c_str(), return_data_friends, this,&zErrMsg);
}

int SipManager::add_friends(std::string friend_username)
{
    int i = 0;
    char *data; 
    char *zErrMsg = 0;

    get_friends_in_str(username);
    std::cout << friend_str << std::endl;
    std::string sql_request = "UPDATE user_db SET friend=\"";
    sql_request = sql_request + friend_str;
    sql_request = sql_request + friend_username;
    sql_request = sql_request + ";\"";
    sql_request = sql_request + "WHERE username==\"";
    sql_request = sql_request + username;
    sql_request = sql_request + "\"";
    std::cout << sql_request << std::endl;
    sqlite3_exec(_database, sql_request.c_str(), handler_add_friends, this,&zErrMsg);
    sql_request.erase(0, std::string::npos);
    get_friends_in_str(friend_username);
    sql_request = "UPDATE user_db SET friend=\"";
    sql_request = sql_request + friend_str;
    sql_request = sql_request + username;
    sql_request = sql_request + ";\"";
    sql_request = sql_request + "WHERE username==\"";
    sql_request = sql_request + friend_username;
    sql_request = sql_request + "\"";
    sqlite3_exec(_database, sql_request.c_str(), handler_add_friends, this,&zErrMsg);
    get_friends(username);
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

void SipManager::parsePacket(std::string request)
{
    types.push_back(get_request_types_request(request));
    if (types[types.size() -1] != request_types::ADD_FRIEND) {
        ip = get_IP_in_request(request);
        username = get_username_request(request);
        hostname = get_hostname_request(request);
        port = get_port_request(request);
        tag_cli = get_tag_client_request(request);
        call_id = get_callID(request);
        Cseq = get_cseq(request);
        server_ip = get_IP_from_iface();
    }
}

void SipManager::parse_header(const std::string request)
{
    std::vector<std::string> lines;
    std::vector<std::string> tmp;
    boost::split(lines, request, boost::is_any_of("\t"));
    for (const auto& elem : lines)
        !elem.empty() ? this->parsePacket(elem) : void();
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
std::string SipManager::get_cseq(std::string request)
{
    request.erase(0, request.find("CSeq:") + 6);
    return (request.substr(0, request.find("\n")));
}

request_types SipManager::get_request_types_request(std::string request)
{
    std::string rtypes;
    try{
        std::stoi(request.substr(0, request.find(" ")));
        rtypes = request.substr(request.find(" "), request.find("\r\n"));
    } catch (std::invalid_argument) {  
        rtypes = request.substr(0, request.find(" "));
    }
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
        case str2int("ADD_FRIEND"):
            return request_types::ADD_FRIEND;
    }
}

std::string SipManager::get_IP_in_request(std::string request)
{
    request.erase(0, request.find("SIP/2.0/TCP") + 12);
    return (request.substr(0, request.find(":")));
}

std::string SipManager::get_username_request(std::string request)
{
    request.erase(0, request.find("From: \"") + 7);
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
    request.erase(0, request.find(ip));
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
    return(request.erase(request.find("CSeq") - 2, std::string::npos));
}



void SipManager::trying_connection()
{
    auto hdr = std::stringstream();
    hdr << "100 Trying\nVia: " << ip << ":" << port;
    hdr << "\r\nFrom: \"" << username << "\"<" << hostname << "@" << server_ip << ">;tag=" << tag_cli;
    hdr << "\r\nTo: \"" << username << "\"<" << hostname << "@" << server_ip << ">";
    hdr << "\r\nCall-ID: " << call_id << " \r\n" << Cseq << "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, SUBSCRIBE, NOTIFY";
    hdr << "\r\nContact: <" << hostname << "@" << server_ip << ">";
    hdr << "\r\nContent-Length: 0\r\n\r\n\t";
    response_header = hdr.str();
}

void SipManager::OK_header()
{
    auto hdr = std::stringstream();
    hdr << "200 OK\r\nVia: " << ip << ":" << port;
    hdr << "\r\nFrom: \"" << username << "\"<" << hostname << "@" << server_ip <<">;tag="<< tag_cli;
    hdr << "\r\nTo: \"" << username << "\"<" << hostname << "@" << server_ip << ">;tag=" << tag_server;
    hdr << "\r\nCall-ID: " << call_id << "\r\n" << "CSeq: " << Cseq << "Contact: <" << hostname << "@" << ip << ":" << port << ">\r\n" <<"Content-Length: 0\r\n\r\n\t"; 
    response_header = hdr.str();
}

void SipManager::notify_header(std::string message)
{
    auto hdr = std::stringstream();
    hdr << "NOTIFY " << hostname << "@" << ip << ":" << port;
    hdr << "\r\nVia: " << server_ip << ":" << port_server;
    hdr << "\r\nFrom: \"" << username << "\" <sip:" << username << "@" << ip << ">;tag=" << tag_cli;
    hdr <<  "\r\nTo: <" << hostname << "@" << server_ip << ">";
    hdr << "\r\nContact: <sip:" << username <<"@" << server_ip; ">";
    hdr << "\r\nCSeq: 102 NOTIFY";
    hdr << "\r\nMessage_Waiting: " << message << "\r\n\r\n\t";
    response_header = hdr.str();
}

void SipManager::update_header()
{
    auto hdr = std::stringstream();
    int i = 0;
    get_all_data_from_db();
    hdr << "242 UPDATE\r\n" << hostname << "@" << ip << ":" << port;
    hdr << "\r\nVia: " << server_ip << ":" << port_server;
    hdr << "\r\nFrom: \"" << username << "\" <sip:" << username << "@" << ip << ">;tag=" << tag_cli;
    hdr <<  "\r\nTo: <" << hostname << "@" << server_ip << ">";
    hdr << "\r\nContact: <sip:" << username <<"@" << server_ip; ">";
    hdr << "\r\nCSeq: 242 UPDATE";
    hdr << "\r\nMessage_Waiting: ";
    for (i = 0; i < my_friends.size() - 1; i++) {
        hdr << my_friends[i] << ","; 
    }
    hdr << my_friends[i] ; 
    hdr << "\r\n";
    my_friends.clear();
    response_header = hdr.str();
}
std::string SipManager::get_friend_username(std::string header_recv)
{
    header_recv.erase(0, header_recv.find("Waiting: ") + 9);
    header_recv.erase(header_recv.find("\n") - 1, std::string::npos);
    return(header_recv);
}

void SipManager::add_friend_header(std::string header_recv)
{
    auto hdr = std::stringstream();
    std::string friend_username = get_friend_username(header_recv);
    add_friends(friend_username);
    hdr << "243 ADD_FRIEND\r\n" << hostname << "@" << ip << ":" << port;
    hdr << "\r\nVia: " << server_ip << ":" << port_server;
    hdr << "\r\nFrom: \"" << username << "\" <sip:" << username << "@" << ip << ">;tag=" << tag_cli;
    hdr <<  "\r\nTo: <" << hostname << "@" << server_ip << ">";
    hdr << "\r\nContact: <sip:" << username <<"@" << server_ip; ">";
    hdr << "\r\nCSeq: 243 ADD_FRIEND";
    response_header = hdr.str();
}

void SipManager::info_header()
{
    int i = 0;
    auto hdr = std::stringstream();
    get_friends_data();
    hdr << "420 INFO\r\n" << hostname << "@" << ip << ":" << port;
    hdr << "\r\nVia: " << server_ip << ":" << port_server;
    hdr << "\r\nFrom: \"" << username << "\" <sip:" << username << "@" << ip << ">;tag=" << tag_cli;
    hdr <<  "\r\nTo: <" << hostname << "@" << server_ip << ">";
    hdr << "\r\nContact: <sip:" << username <<"@" << server_ip; ">";
    hdr << "\r\nCSeq: 420 INFO";
    hdr << "\r\nMessage_Waiting: ";
    for (i = 0; i < my_friends.size() - 1; i++) {
        hdr << my_friends[i] << ","; 
    }
    hdr << my_friends[i]; 
    hdr << "\r\n";
    my_friends.clear();
    response_header = hdr.str();
}




void SipManager::invite_header(std::string packet)
{
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



std::stringstream SipManager::notify_header(char *old_request)
{
    auto ss = std::stringstream();
    std::string request = convertToString(old_request);
 
    //std::cout << ss.str() << std::endl;
    return (ss);
}
*/