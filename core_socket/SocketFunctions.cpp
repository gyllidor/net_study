#include "SocketFunctions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
int Net::Socket(int i_domain, int i_type, int i_protocol)
{
    return 0;
}

//-------------------------------------------------------------------------------------------------
int Net::Bind(int i_socketfd, const sockaddr* ip_addr, socklen_t i_addr_length)
{
    return 0;
}

//-------------------------------------------------------------------------------------------------
int Net::Listen(int i_socketfd, int i_backlog)
{
    return 0;
}

//-------------------------------------------------------------------------------------------------
int Net::Accept(int i_socketfd, sockaddr* ip_addr, socklen_t& i_addrlen)
{
    return 0;
}

//-------------------------------------------------------------------------------------------------
int Net::Connect(int i_socketfd, const sockaddr* ip_addr, socklen_t i_addrlen)
{
    return 0;
}
