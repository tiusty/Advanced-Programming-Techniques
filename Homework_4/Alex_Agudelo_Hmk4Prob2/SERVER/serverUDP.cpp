/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/17/19
Description: Implements the server UDP functionality
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>
#include <limits>       // std::numeric_limits
#include "serverUDP.hpp"
#include <thread>
#include <mutex>

// Mutex to protect server commands and receiving messages
std::mutex compositeMutex;

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
    // Loop indefinetly receiving messages from clients
    while (true)
    {
        // Receive a message
        n = recvfrom(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0)
        {
            error("recvfrom");
        }
        // Store the clients info in the map
        // Duplicates are overriden
        clientMachines[from.sin_port] = from;

        // Process the messaged
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
    // Mutex to protect against data race's with server command prompts
    std::lock_guard<std::mutex> guard(compositeMutex);

    // Convert to host values
    message.lSeqNum = ntohl(message.lSeqNum);
    message.nMsgLen = ntohs(message.nMsgLen);

    // If the message is not version 1 then ignore
    if (message.nVersion != 1) {
        return;
    }

    // Determines functionality based on message type
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
            addToComposite(message);
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
}

void ServerUDP::promptForCommand()
{
    int command;

    // Keep prompting for a command until the sever is being shutdown
    while(!shutDown)
    {
        // make sure there is nothing on cin
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
    // Use mutex to protect against data race from receiving messages
    std::lock_guard<std::mutex> guard(compositeMutex);
    switch(command)
    {
        // Case that sends out the composite message to all clients
        case 0:
            sendComposite();
            break;
            // case that clears the current composite message
        case 1:
            clearComposite();
            break;
            // Case that displays the current composite message
        case 2:
            displayComposite();
            break;
            // Print error for invalid command
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

    // Loop through all client messages and add their message lengths
    for(const auto& msg : compositeMessage)
    {
        size += msg.second.nMsgLen;
    }
    return size;
}

void ServerUDP::addToComposite(udpMessage message)
{
    // Add the message to the composite message
    compositeMessage[message.lSeqNum] = message;

    // Determine if an overflow occurred and if so then send
    //  out the composite message
    if(getCompositeMsgSize() > kCompMessageMaxLength)
    {
        sendComposite();
    }

}

void ServerUDP::sendComposite()
{
    char chMsg[kCompMessageMaxLength]{0};
    char chMsgRemaining[kCompMessageMaxLength]{0};

    // Retrieve the part that is being sent and also the part of the message
    //  that will make up the beginnnig of the new composite message
    auto result = createCompositeMsg(chMsg, chMsgRemaining);

    // Now that the strings have been evaluted clear the composite message container
    clearComposite();

    // Send out the composite message t all clients
    sendMessage(chMsg, result.first);

    // If there was any portion of overflow, then add it back to the composite message container
    //  as seq=0
    if(result.second > 0)
    {
        udpMessage newMessage{};
        memset(newMessage.chMsg, 0, kCompMessageMaxLength);
        newMessage.lSeqNum = 0;
        newMessage.nMsgLen = result.second;
        strncpy(newMessage.chMsg, chMsgRemaining, result.second);
        compositeMessage.insert({newMessage.lSeqNum, newMessage});
    }
}

void ServerUDP::sendMessage(char chMsg[kCompMessageMaxLength], int msgLen)
{
    int n;
    socklen_t fromlen = 0;
    fromlen = sizeof(struct sockaddr_in);

    // Convert host values to network values and create the message to send to clients
    udpMessage message{0};
    message.lSeqNum = htonl(compSeqNum);
    message.nMsgLen = htons(msgLen);
    strncpy(message.chMsg, chMsg, msgLen);

    // Send out the composite message to all connected clients
    for(const auto &x : clientMachines)
    {
        n = sendto(sockfd, &message, sizeof(message), 0, (struct sockaddr *)&x.second, fromlen);
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
    }
    // Increment sequence for the next composite message
    compSeqNum++;
}

std::pair<int, int> ServerUDP::createCompositeMsg(char compMsg[kCompMessageMaxLength], char compMsgRemaining[kCompMessageMaxLength])
{
    unsigned int compMsgLen{0};
    unsigned int compMsgRemainingLen{0};

    // Loop through all client messages to build the composite message
    for(const auto& msg : compositeMessage)
    {
        for(int i=0; i<msg.second.nMsgLen; i++)
        {
            // If the composite message is not filled then add to it
            if(compMsgLen < kCompMessageMaxLength)
            {
                compMsg[compMsgLen] = msg.second.chMsg[i];
                compMsgLen++;
            }
            // Once the composite message is filled then add to the remaining char,
            //  which will populate the new composite message
            else
            {
                compMsgRemaining[compMsgRemainingLen] = msg.second.chMsg[i];
                compMsgRemainingLen++;
            }
        }

    }

    // Return both lengths
    return std::make_pair(compMsgLen, compMsgRemainingLen);
}

void ServerUDP::clearComposite()
{
    // Deletes all client messages
    compositeMessage.clear();
}

void ServerUDP::displayComposite()
{

    char chMsg[kCompMessageMaxLength]{0};
    char chMsgRemaining[kCompMessageMaxLength]{0};
    // Generate the current composite message
    auto result = createCompositeMsg(chMsg, chMsgRemaining);

    // Displays the current composite message
    printf("Composite message: %.*s\n", result.first, chMsg);
}
