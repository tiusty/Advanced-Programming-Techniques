/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description:
 Class that supports UDP server. Code is written for linux but there are only a few
    changes that are necessary to make it compatible with windows
*/

#ifndef HOMEWORK_4_SERVERUDP_HPP
#define HOMEWORK_4_SERVERUDP_HPP

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

class ServerUDP {
public: // Methods
    void startServer(int portno);
    void receiveMessages();
    void promptForCommand();
private: // Methods
    void parseCommand(int command);
    int sockClose(SOCKET sock);
    int sockQuit();
    int sockInit();
    void error(const char *msg);
private: // Members
    bool shutDown{false};
    bool initialized{false};
    int sockfd;
};


#endif //HOMEWORK_4_SERVERUDP_HPP
