/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>
#include <limits>       // std::numeric_limits
#include "serverUDP.hpp"
#include <thread>

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>

    #pragma comment (lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */

typedef int SOCKET;
#endif
/////////////////////////////////////////////////
// Cross-platform socket initialize
int ServerUDP::sockInit()
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}
/////////////////////////////////////////////////
// Cross-platform socket quit
int ServerUDP::sockQuit()
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}
/////////////////////////////////////////////////
// Cross-platform socket close
int ServerUDP::sockClose(SOCKET sock)
{

    int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0)
    {
        status = closesocket(sock);
    }
#else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0)
    {
        status = close(sock);
    }
#endif

    return status;

}
/////////////////////////////////////////////////
// Output error message and exit
void ServerUDP::error(const char *msg)
{
    perror(msg);
    // Make sure any open sockets are closed before calling exit
    exit(1);
}
/////////////////////////////////////////////////

void ServerUDP::handleMessages()
{
    struct sockaddr_in from;
    socklen_t fromlen;
    int newsockfd;
    int n;

    udpMessage buffer{};

    fromlen = sizeof(struct sockaddr_in);
    while (true)
    {
        n = recvfrom(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
        {
            error("recvfrom");
        }
        printf("Received a datagram: %s, seq: %d, version: %d, type: %d\n", buffer.chMsg, buffer.lSeqNum, buffer.nVersion, buffer.nType);
//        n = sendto(sockfd, "Got your message\n", 17, 0, (struct sockaddr *)&from, fromlen);
        if (n < 0)
            error("sendto");
    }

    sockClose(newsockfd);
    sockClose(sockfd);

    sockQuit();

#ifdef _WIN32
    std::cin.get();
#endif
}

void ServerUDP::startServer(int portno)
{
    struct sockaddr_in serv_addr;

    sockInit();
    // Create the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Make sure the socket was created
    if (sockfd < 0)
        error("ERROR opening socket");
    // Zero out the variable serv_addr
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    // Convert the port number string to an int

    // Initialize the serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert port number from host to network
    serv_addr.sin_port = htons(portno);
    // Bind the socket to the port number
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    initialized = true;
    printf("Waiting on messages...\n");
}

void ServerUDP::promptForCommand()
{
    int command;

    // Keep prompting for a command until the sever is being shutdown
    while(!shutDown)
    {
        std::cin.clear();

        // Prompt the user for a command
        std::cout << "Please enter a command: " << std::endl;
        std::cin >> command;

        // Validate std::cin
        // If the input is valid then parse the command
        if(std::cin.good())
        {
            parseCommand(command);
        }
        // If the input is not valid then ignore everything else in the cin buffer
        //  and clear the cin error state
        else
        {
            std::cout << "Invalid input. Input should be a number" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
}

void ServerUDP::parseCommand(int command)
{
    switch(command)
    {
        case 0:
            std::cout << "DO zero!" << std::endl;
            break;
        case 1:
            std::cout << "DO One!" << std::endl;
            break;
        case 2:
            std::cout << "DO Two!" << std::endl;
            break;
        default:
            std::cout << "Command invalid" << std::endl;
            break;
    }
}

void ServerUDP::spawnWorkers()
{
    // Spawn necessary worker threads
    std::thread receiveMessagesThread(&ServerUDP::handleMessages, this);
    std::thread promptUser(&ServerUDP::promptForCommand, this);

    // When the threads quit due to a shutdown then wait for them to finish
    receiveMessagesThread.join();
    promptUser.join();

    // Close the socket
    sockQuit();
}