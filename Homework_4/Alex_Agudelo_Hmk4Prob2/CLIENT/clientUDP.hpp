/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description: 
*/

#ifndef HOMEWORK_4_CLIENTUDP_HPP
#define HOMEWORK_4_CLIENTUDP_HPP

#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */

typedef int SOCKET;

// Copied in the server and client to make it easier to submit the assignment
struct udpMessage
{
    unsigned char nVersion;
    unsigned char nType;
    unsigned short nMsgLen;
    unsigned long lSeqNum;
    char chMsg[1000];
};


class ClientUDP {
public: // Methods
    static constexpr unsigned int kMessageLength = 1024;
    void startClient(int portno, const char* server_address);
    void promptForCommand();
    bool parseCommand(const char command[kMessageLength]);
    void sendMessage(udpMessage buffer);
    void receiveMessage();
    void closeSockets();
    void spawnWorkers();
    void handleReceivedMessage(udpMessage message);
private: // Methods
    int sockInit();
    int sockQuit();
    int sockClose(SOCKET sock);
private: // Members
    static constexpr unsigned int kRecvTimout{900000};
    unsigned int versionNum{0};
    bool ready{false};
    int sockfd;
    struct sockaddr_in serv_addr;
    bool shutDown{false};
};


#endif //HOMEWORK_4_CLIENTUDP_HPP
