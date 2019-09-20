#include "Server.hpp"

std::string make_daytime_string(char *recv_buffer_, SipManager sip)
{
    if (strncmp(recv_buffer_, "REGISTER", 8) == 0) {
        sip.trying_connection(recv_buffer_);
    }
    return ("Salut\n");
}