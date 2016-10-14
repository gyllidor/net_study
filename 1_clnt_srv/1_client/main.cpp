#include <iostream>

#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    argc = 2;
    argv [1] = "192.168.0.103";
    if (argc != 2)
    {
        std::cerr << "not enough args" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "socket failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    sockaddr_in srvaddr;
    bzero(&srvaddr, sizeof(srvaddr));

    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(13);

    if (inet_pton(AF_INET, argv[1], &srvaddr.sin_addr) < 0)
    {
        std::cerr << "inet_pton failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&srvaddr), sizeof(srvaddr)) < 0)
    {
    std::cerr << "connect failed" << std::endl;
    std::exit(EXIT_FAILURE);
    }

    const uint16_t max_length = 1024;
    char line[max_length + 1] = { 0 };
    ssize_t readnbyte = 0;
    while( (readnbyte = read(sockfd, &line, max_length)) > 0)
    {
        line[readnbyte] = 0;
        std::cout << line;
        return 0;
    }

    std::cout << std::endl;

    return 0;
}
