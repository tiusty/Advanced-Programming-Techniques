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

#include <map>

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
    static constexpr unsigned int kCompMessageMaxLength{10};
    void startServer(int portno);
    void spawnWorkers();
    void handleMessages();
    void promptForCommand();
    void addToComposite(udpMessage message);
    void createCompositeMsg(udpMessage message, char compMsg[kCompMessageMaxLength], char compMsgRemaining[kCompMessageMaxLength]);
    void sendComposite(udpMessage message);
//    void clearComposite();
//    void displayComposite();
private: // Methods
    void parseCommand(int command);
    int sockClose(SOCKET sock);
    int sockQuit();
    int sockInit();
    void error(const char *msg);
private: // Members
//    std::list clientAddress;
    bool shutDown{false};
    bool initialized{false};
    int sockfd{-1};
    std::map<unsigned int, udpMessage> compositeMessage;
    unsigned int compMessLen{0};
    unsigned int compSeqNum{0};
};


#endif //HOMEWORK_4_SERVERUDP_HPP
