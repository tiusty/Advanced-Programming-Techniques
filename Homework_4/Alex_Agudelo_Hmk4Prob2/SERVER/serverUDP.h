/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/17/19
Description:
 Class that supports UDP server. Code is written for linux but there are only a few
    changes that are necessary to make it compatible with windows
*/

#ifndef HOMEWORK_4_SERVERUDP_H
#define HOMEWORK_4_SERVERUDP_H

#include <map>
#include <unordered_set>
#include <netinet/in.h>
#include <sys/socket.h>

typedef int SOCKET;
using portInfo = struct sockaddr_in;

//  Udp Message struct
struct udpMessage
{
    unsigned char nVersion;
    unsigned char nType;
    unsigned short nMsgLen;
    unsigned long lSeqNum;
    char chMsg[1000];
};

/**
 * Server UDP receives messages from clients and organizes them via sequence number
 *  and then when either the buffer overflows or the server is commanded to send the
 *  composite message, it sends it to all clients who has sent the server a message
 *
 *  Server will store a list of all the clients that sent it a message and will
 *      send the composite message to all the clients when instructed to do so
 */
class ServerUDP {
public: // Methods
    /**
     *  Determines the max length of a message
     */
    static constexpr unsigned int kCompMessageMaxLength{1000};
    /**
     * Starts the UDP server by binding it to a port
     * @param portno The port number to bind the server to
     */
    void startServer(int portno);
    /**
     * Spawns all the worker threads. For this server, there is a thread receiving commands
     *  from the user and also a thread receiving messages from client machines
     */
    void spawnWorkers();
    /**
     * Function that is passed to the thread to receive messages from client machines
     */
    void receiveMessages();
    /**
     * Handles messages and determines what to do based on the message contents
     * @param message The message that was received via a client
     */
    void handleMessage(udpMessage message);
    /**
     * The function that is passed to a thread to handle user prompts
     */
    void promptForCommand();
    /**
     * Adds a message to the container storing all the client messages
     * @param message the message to add
     * @return True -> A message was sent out
     *         False -> A message was not sent out
     */
    bool addToComposite(udpMessage message);
    /**
     * Creates the composite message by looping through the stored client messages. It uses the first
     * 1000 bytes as the composite message and will store the remaining to create a new composite message
     * @param compMsg The string of the current composite message
     * @param compMsgRemaining The remaining part of the composite message due to overrun
     * @return std::pair<> First -> The size of the composite message
     *                     Second -> The size of the remaining bytes from the overflow
     */
    std::pair<int, int> createCompositeMsg(char compMsg[kCompMessageMaxLength], char compMsgRemaining[kCompMessageMaxLength]);
    /**
     * Wraps functionality if the composite message should be sent. Creates the composite message and handles
     *  and overflow that may occur
     */
    void sendComposite();
    /**
     * Actually sends out the composite message to all clients that have sent a message to the server
     * @param chMsg The string to send
     * @param msgLen The length of the string
     */
    void sendMessage(char chMsg[kCompMessageMaxLength], int msgLen);
    /**
     * Gets the size of the composite message by adding all the sizes of the client messages
     * @return The size of the composite message
     */
    int getCompositeMsgSize();
    /**
     * Clears the composite message by removing all client messages from the container
     */
    void clearComposite();
    /**
     * Displays the current stored composite message
     */
    void displayComposite();
private: // Methods
    /**
     * Parses the command passed in by the user
     * @param command The command passed in by the user
     */
    void parseCommand(int command);
    /**
     * Closes the socket
     */
    int sockClose(SOCKET sock);
    /**
     * Quits the socket
     */
    int sockQuit();
    /**
     * Initializes the socket
     */
    int sockInit();
    /**
     * Displays an error and exits
     * @param msg The error message
     */
    void error(const char *msg);
private: // Members
    /**
     * Stores all the clients that sent the server a message
     */
    std::map<int, portInfo> clientMachines;
    /**
     * indicates whether or not the server is shutting down
     */
    bool shutDown{false};
    /**
     * Stores the socket id
     */
    int sockfd{-1};
    /**
     * Stores all the current client messages the server received
     */
    std::map<unsigned int, udpMessage> compositeMessage;
    /**
     * Stores the seq num of the composite message
     */
    unsigned int compSeqNum{0};
};


#endif //HOMEWORK_4_SERVERUDP_H
