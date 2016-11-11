#include "SocketFunctions.h"

#include "BrrLogger.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Net::Exception::Socket::Socket(const std::string &i_exception_msg)
    : m_exception_msg(i_exception_msg)
{
}

//-------------------------------------------------------------------------------------------------
const char *Net::Exception::Socket::what() const
{
    return m_exception_msg.c_str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int Net::Socket(int i_domain, int i_type, int i_protocol)
{
    const int socketfd = socket(i_domain, i_type, i_protocol);
    if (socketfd < 0)
    {
        BRR_LOGE("%s", brr::StrErrno().c_str());
        throw Exception::Socket(brr::StrErrno());
    }

    return socketfd;
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

