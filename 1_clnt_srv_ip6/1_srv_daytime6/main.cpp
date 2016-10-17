#include <iostream>

#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <ctime>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    const int listenfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sockaddr_in6 srvaddr;
    bzero(&srvaddr, sizeof(srvaddr));

    srvaddr.sin6_family = AF_INET6;
    srvaddr.sin6_port = htons(13);
    srvaddr.sin6_addr = in6addr_any;

    int err = bind(listenfd, reinterpret_cast<sockaddr*>(&srvaddr), sizeof(srvaddr));
    if (err < 0)
    {
        perror(nullptr);
        std::cerr << "bind failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 5) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while(true)
    {
        std::cout << "waiting..." << std::endl;

        const int clientfd = accept(listenfd, nullptr, nullptr);
        if (clientfd < 0)
        {
            std::cerr << "accept failed" << std::endl;
            continue;
        }

        const time_t ticks = time(nullptr);
        const std::string time_readable = ctime(&ticks);

        std::cout << time_readable << std::endl;

        if (write(clientfd, time_readable.c_str(), time_readable.size()) < 0)
            std::cerr << "write failed" << std::endl;

        if (close(clientfd) < 0)
            std::cerr << "close failed" << std::endl;
    }

    return 0;
}
