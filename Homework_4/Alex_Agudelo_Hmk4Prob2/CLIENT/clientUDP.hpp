/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/18/19
Description:
 Creates a client UDP program which can send messages to a UDP server over a socket. Various
 message types can be sent to determine desired functionality
*/

#ifndef HOMEWORK_4_CLIENTUDP_HPP
#define HOMEWORK_4_CLIENTUDP_HPP

#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */

typedef int SOCKET;

// UDP message struture
struct udpMessage
{
    unsigned char nVersion;
    unsigned char nType;
    unsigned short nMsgLen;
    unsigned long lSeqNum;
    char chMsg[1000];
};

/**
 * Client UDP class that handles sending and receiving messages from a UDP server.
 *  Message versions determine if the message is accepted or rejected and the message
 *  types allow for different functionality
 */
class ClientUDP {
public: // Methods
    /**
     * Constexpr to determine message max length
     */
    static constexpr unsigned int kMaxMessageLength{1000};
    /**
     * Starts the client UDP socket
     * @param portno The port to look for the server
     * @param server_address The address to look for the server
     */
    void startClient(int portno, const char* server_address);
    /**
     * Function is passed to a thread to handle commands from the user
     */
    void promptForCommand();
    /**
     * Parses the command passed in by the user to determine what the client should do
     * @param command The command the user typed
     * @return True -> The command was valid
     *         False -> The command was not valid
     */
    bool parseCommand(const char command[kMaxMessageLength]);
    /**
     * Sends a UDP message to the server
     * @param buffer The udp message to send
     */
    void sendMessage(udpMessage buffer);
    /**
     * Function handled by thread to listen for messages the server may send to the client
     */
    void receiveMessage();
    /**
     * Closes the socket when the program wants to terminate
     */
    void closeSockets();
    /**
     * Spawns all the worker threads the client needs to execute functionality
     */
    void spawnWorkers();
    /**
     * Handles a message that was received by the server
     * @param message The message received from the server
     */
    void handleReceivedMessage(udpMessage message);
private: // Methods
    /**
     * Initializes a socket
     */
    int sockInit();
    /**
     * Quits a socket
     */
    int sockQuit();
    /**
     * Closes a socket
     */
    int sockClose(SOCKET sock);
private: // Members
    /**
     * Determines the version number for the client messages that are being sent
     */
    unsigned int versionNum{0};
    /**
     * The socket id
     */
    int sockfd;
    /**
     * The address of the server
     */
    struct sockaddr_in serv_addr;
    /**
     * Determines if the client is being shutdown or not
     */
    bool shutDown{false};
};


#endif //HOMEWORK_4_CLIENTUDP_HPP
