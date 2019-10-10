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

#endif

int ClientUDP::sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

int ClientUDP::sockQuit(void)
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

void ClientUDP::sendAndReceiveMessage()
{
    int n;
    socklen_t fromlen = 0;
    struct sockaddr from;
    memset((char *)&from, 0, sizeof(sockaddr));
    char message[1024];
    char response[1024];
    udpMessage buffer{};

    while (true)
    {
        printf("Please enter the message: ");

        memset(&buffer, 0, sizeof(buffer));
        fgets(message, 1023, stdin);
        strcpy(buffer.chMsg, message);
        
        buffer.nVersion =1;
        buffer.lSeqNum = 2;

        n = sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        if (n < 0)
            error("ERROR writing to socket");

        memset(&buffer, 0, sizeof(buffer));

        //       n = recv(sockfd, buffer, 1023, 0);
        fromlen = sizeof(serv_addr);
        n = recvfrom(sockfd, response, 1023, 0, (sockaddr *)&from, &fromlen);

        if (n == -1)
        {
            wprintf(L"recvfrom failed with error %d\n", errno);
        }

        if (n < 0)
            error("ERROR reading from socket");
        else
            message[n] = 0;

        printf("%s\n", message);
    }

    sockClose(sockfd);
    sockQuit();

#ifdef _WIN32
    std::cin.get();
#endif
}

void ClientUDP::startClient(int portno, const char *server_address)
{
    struct hostent *server;

    sockInit();
    // Convert string to int

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

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

//    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//       error("ERROR connecting");

    initialized = true;
}