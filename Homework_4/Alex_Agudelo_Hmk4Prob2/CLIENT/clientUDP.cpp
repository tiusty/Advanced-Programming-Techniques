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
#include <limits>
#include <iostream>
#include <stdio.h>

#include "clientUDP.hpp"

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> /* Needed for close() */
#include <thread>

#endif

// Define constexpr members
constexpr unsigned int ClientUDP::kMaxMessageLength;

int ClientUDP::sockInit()
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

int ClientUDP::sockQuit()
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

/* Note: For POSIX, typedef SOCKET as an int. */

int ClientUDP::sockClose(SOCKET sock)
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

void error(const char *msg)
{
    perror(msg);

    exit(0);
}

void ClientUDP::sendMessage(udpMessage buffer)
{
    int n;
    buffer.nVersion = versionNum;
    n = sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
}


void ClientUDP::receiveMessage()
{
    // Loop until the system goes into shutdown
    while(!shutDown)
    {
        // Declare necessary variables
        int n;
        socklen_t fromlen = 0;
        struct sockaddr from{};
        memset((char *)&from, 0, sizeof(sockaddr));
        udpMessage response{};

        fromlen = sizeof(serv_addr);
        n = recvfrom(sockfd, &response, sizeof(response), 0, (sockaddr *)&from, &fromlen);

        // If the recvfrom error is from timing out then don't try to parse the result
        //  just loop again
        if(errno == EAGAIN)
        {
            continue;
        }

        // If an error occurred, print out the error
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        // If the message was received successfully then print out the message
        else
        {
            // Only handle messages that have at least size 1
            if(n > 0)
            {
                handleReceivedMessage(response);
            }
        }

    }
}

void ClientUDP::handleReceivedMessage(udpMessage message)
{
    message.nMsgLen = ntohs(message.nMsgLen);
    message.lSeqNum = ntohl(message.lSeqNum);

    printf("Received Msg Type: %d, Seq: %ld, Msg: %.*s\n", message.nType, message.lSeqNum, message.nMsgLen, message.chMsg);
}

void ClientUDP::startClient(int portno, const char *server_address)
{
    struct hostent *server;

    sockInit();

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Get server address
    server = gethostbyname(server_address);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    // Zero out serv_addr variable
    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    memmove((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    // If a connection is desired
//    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//       error("ERROR connecting");
}

void ClientUDP::promptForCommand()
{
    int commandNum;
    char command[kMaxMessageLength];

    // Keep prompting for a command until the sever is being shutdown
    while(!shutDown)
    {
        std::cin.clear();

        // Prompt the user for a command
        std::cout << "Please enter a command: " << std::endl;

        // Retrieve input from user
        fgets(command, 1023, stdin);

        // Strip the new line
        command[strcspn(command, "\n")] = 0;

        // Parse the passed in command
        parseCommand(command);
    }
    shutdown(sockfd, SHUT_RDWR);
}

bool ClientUDP::parseCommand(const char command[kMaxMessageLength])
{
    enum CommandType { setVersion, setType, setSequence, setMessage, Quit, None};
    CommandType commandType{CommandType::None};

    // Returns first token
    char commandToParse[kMaxMessageLength]{0};
    strcpy(commandToParse, command);
    char *token = strtok(commandToParse, " ");

    // Variables regarding sending a message
    udpMessage message{};

    // Keep printing tokens while one of the
    // delimiters present in command.
    while (token != nullptr)
    {
        // When the command type is none, then we don't know which type of command
        //   we are going to be parsing
        if(commandType == CommandType::None)
        {
            if(strlen(token) != 1)
            {
                std::cout << "Command must be one chacater" << std::endl;
                return false;
            }

            switch(token[0])
            {
                case 'v':
                    commandType = CommandType::setVersion;
                    break;
                case 't':
                    commandType = CommandType::setType;
                    break;
                case 'q':
                    shutDown = true;
                    return true;
                default:
                    std::cout << "Not a valid arguments" << std::endl;
                    return false;
            }
        }
        // If we are parsing a version then parse the version and set it
        else if(commandType == CommandType::setVersion)
        {
            char *pEnd;
            int tempVersionNum = strtol(token, &pEnd, 10);
            if(tempVersionNum < 0)
            {
                std::cout << "Error: Version must be greater than or equal to 0" << std::endl;
                return false;
            }
            versionNum = tempVersionNum;
            std::cout << "Version now: " << versionNum << std::endl;
            return true;
        }
        else if (commandType == CommandType::setType)
        {
            char *pEnd;
            int tempMType = strtol(token, &pEnd, 10);
            if(tempMType < 0)
            {
                std::cout << "Error: Version must be greater than or equal to 0" << std::endl;
                return false;
            }
            message.nType = tempMType;
            commandType = CommandType::setSequence;
        }
        else if (commandType == CommandType::setSequence)
        {
            char *pEnd;
            int tempMSeq = strtol(token, &pEnd, 10);
            if(tempMSeq < 0)
            {
                std::cout << "Error: Version must be greater than or equal to 0" << std::endl;
                return false;
            }
            message.lSeqNum = tempMSeq;
            commandType = CommandType::setMessage;
        }
        else if (commandType == CommandType::setMessage)
        {
            message.nMsgLen = strlen(token);

            // Limit client to sending out the message length
            if(message.nMsgLen > kMaxMessageLength)
            {
                message.nMsgLen = kMaxMessageLength;
            }

            // Copy the desired amount of characters
            strncpy(message.chMsg,token, message.nMsgLen);

            // Convert all values to network order
            message.nMsgLen = htons(message.nMsgLen);
            message.lSeqNum = htonl(message.lSeqNum);

            sendMessage(message);
            return true;
        }

        // If we are now setting the message, then grab the rest of the char as the message
        if(commandType == CommandType::setMessage)
        {
            token = strtok(nullptr, "\0");
        }
        // Otherwise delimit by spaces to grab the different arguments
        else
        {
            token = strtok(nullptr, " ");
        }
    }

    std::cout << "Command not valid" << std::endl;
    return false;
}

void ClientUDP::spawnWorkers()
{
    // Spawn necessary worker threads
    std::thread receiveMessagesThread(&ClientUDP::receiveMessage, this);
    std::thread promptUser(&ClientUDP::promptForCommand, this);

    // When the threads quit due to a shutdown then wait for them to finish
    receiveMessagesThread.join();
    promptUser.join();

    // Close the socket
    closeSockets();
}

void ClientUDP::closeSockets()
{
    sockClose(sockfd);
    sockQuit();

#ifdef _WIN32
    std::cin.get();
#endif
}