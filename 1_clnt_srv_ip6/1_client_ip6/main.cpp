#include <iostream>

#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "not enough argc" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const std::string serv_ip = argv[1];

    sockaddr_in6 servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13);

    if (inet_pton(AF_INET6, serv_ip.c_str(), &servaddr.sin6_addr) <= 0)
    {
        std::cerr << "inet_pton failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) < 0)
    {
        perror(nullptr);
        std::cerr << "connect failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int readnbyte = 0;
    size_t index = 0;
    std::string buff(1025, '\0');
    while((readnbyte = read(sockfd, &buff[index], 1024) > 0))
    {
        index += readnbyte;
        std::cout << buff << std::endl;
    }

    if (readnbyte < 0)
    {
        std::cout << "read failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return 0;
}
