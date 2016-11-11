#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include <sys/socket.h>
#include <sys/types.h>

#include <exception>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace Net
{
namespace Exception
{
class Socket : public std::exception
{
public:
    Socket(const std::string& i_exception_msg);
    ~Socket() throw{};

    const char* what() const throw;

private:
    const std::string m_exception_msg;
};
} // namespace Exception
} // namespace Net

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace Net
{
int Socket(int i_domain, int i_type, int i_protocol);

int Bind(int i_socketfd, const sockaddr* ip_addr, socklen_t i_addr_length);

int Listen(int i_socketfd, int i_backlog);

int Accept(int i_socketfd, sockaddr* ip_addr, socklen_t& i_addrlen);

int Connect(int i_socketfd, const sockaddr* ip_addr, socklen_t i_addrlen);

} // namespace Net

#endif // SOCKET_FUNCTIONS_H
