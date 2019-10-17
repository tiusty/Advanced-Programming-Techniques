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

void ServerUDP::receiveMessages()
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
        handleMessage(buffer);
    }

    sockClose(newsockfd);
    sockClose(sockfd);

    sockQuit();

#ifdef _WIN32
    std::cin.get();
#endif
}

void ServerUDP::handleMessage(udpMessage message)
{
    // If the message is not version 1 then ignore
    if (message.nVersion != 1) {
        return;
    }

    switch(message.nType)
    {
        // Just clears composite message and ignores content
        case 0:
            std::cout << "Just clearing" << std::endl;
            clearComposite();
            break;
        // Clears the composite message and starts a new message with the
        //  client message starting the new message, aka lseq 0
        case 1:
            std::cout << "Clearing and starting a new message" << std::endl;
            clearComposite();
            // Marks the incoming message as the start of the new composite message
            message.lSeqNum = 0;
            addToComposite(message);
            break;
        // Just adds the client message to the composite message
        case 2:
            std::cout << "Just adding to composite" << std::endl;
            addToComposite(message);
            break;
        // Ignores client message and sends out composite message to all clients
        case 3:
            std::cout << "Sending out composite" << std::endl;
            sendComposite();
            break;
        // Unrecognized so do nothing
        default:
            break;
    }
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
            sendComposite();
            break;
        case 1:
            clearComposite();
            break;
        case 2:
            displayComposite();
            break;
        default:
            std::cout << "Command invalid" << std::endl;
            break;
    }
}

void ServerUDP::spawnWorkers()
{
    // Spawn necessary worker threads
    std::thread receiveMessagesThread(&ServerUDP::receiveMessages, this);
    std::thread promptUser(&ServerUDP::promptForCommand, this);

    // When the threads quit due to a shutdown then wait for them to finish
    receiveMessagesThread.join();
    promptUser.join();

    // Close the socket
    sockQuit();
}

int ServerUDP::getCompositeMsgSize()
{
    int size{0};
    for(const auto& msg : compositeMessage)
    {
        size += msg.second.nMsgLen;
    }
    return size;
}

void ServerUDP::addToComposite(udpMessage message)
{
    compositeMessage[message.lSeqNum] = message;

    if(getCompositeMsgSize() > kCompMessageMaxLength)
    {
        sendComposite();
    }

}

void ServerUDP::sendComposite()
{
    char chMsg[kCompMessageMaxLength]{0};
    char chMsgRemaining[kCompMessageMaxLength]{0};

    unsigned int sizeRemaining = createCompositeMsg(chMsg, chMsgRemaining).second;
    clearComposite();
    sendMessage(chMsg);
    if(sizeRemaining > 0)
    {
        udpMessage newMessage;
        memset(newMessage.chMsg, 0, kCompMessageMaxLength);
        newMessage.lSeqNum = 0;
        newMessage.nMsgLen = sizeRemaining;
        strncpy(newMessage.chMsg, chMsgRemaining, sizeRemaining);
        compositeMessage.insert({newMessage.lSeqNum, newMessage});
    }
}

void ServerUDP::sendMessage(char chMsg[kCompMessageMaxLength])
{
    int n;

//    n = sendto(sockfd, chMsg, 17, 0, (struct sockaddr *)&from, fromlen);
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
}

std::pair<int, int> ServerUDP::createCompositeMsg(char compMsg[kCompMessageMaxLength], char compMsgRemaining[kCompMessageMaxLength])
{
    unsigned int sizeMsg{0};
    unsigned int sizeRemaining{0};
    unsigned int msgLen{0};
    for (const auto& x : compositeMessage)
    {
        if(msgLen + x.second.nMsgLen <= kCompMessageMaxLength)
        {
            for(int i=0; i<x.second.nMsgLen;i++)
            {
                compMsg[i+msgLen] = x.second.chMsg[i];
            }
            msgLen += x.second.nMsgLen;
            sizeMsg = msgLen;
        }
        else
        {
            unsigned int i = 0;
            while(i + msgLen < kCompMessageMaxLength)
            {
                compMsg[i+msgLen] = x.second.chMsg[i];
                i++;
            }
            sizeMsg = msgLen + i;
            unsigned int j = 0;
            while(i < x.second.nMsgLen)
            {
                compMsgRemaining[j] = x.second.chMsg[i];
                i++;
                j++;
            }
            sizeRemaining = j;
        }
    }
    return std::make_pair(sizeMsg, sizeRemaining);
}

void ServerUDP::clearComposite()
{
    compositeMessage.clear();
}

void ServerUDP::displayComposite()
{

    char chMsg[kCompMessageMaxLength]{0};
    char chMsgRemaining[kCompMessageMaxLength]{0};
    auto result = createCompositeMsg(chMsg, chMsgRemaining);

    printf("Composite message: %.*s\n", result.first, chMsg);
}
