#include <iostream>

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    const int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sockaddr_in srvaddr;
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(13);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, reinterpret_cast<sockaddr*>(&srvaddr), sizeof(srvaddr)) < 0)
    {
        std::cerr << "bind failed " << errno << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 5) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while(true)
    {
        std::string buff;
        buff.resize(56);

        if (inet_ntop(AF_INET, &srvaddr.sin_addr.s_addr, &buff[0], 56) == nullptr)
        {
            std::cerr << "inet_ntop failed" << std::endl;
        }


        std::cout << "listen " << buff << std::endl;
        const int clientfd = accept(listenfd, reinterpret_cast<sockaddr*>(NULL), nullptr);
        if (clientfd < 0)
        {
            std::cerr << "accept failed" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        const time_t ticks = time(nullptr);
        const std::string readable_time = ctime(&ticks);
        std::cout << readable_time << std::endl;

        size_t index = 0;
        ssize_t writenbyte = 0;
        while ((writenbyte = write(clientfd, &readable_time[index], readable_time.size() - index)) > 0)
        {
            if (writenbyte < 0)
            {
                std::cerr << "write failed" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            index = writenbyte;
            std::cout << "write bytes" << writenbyte << std::endl;
        }

        return 0;
    }

    return 0;
}
