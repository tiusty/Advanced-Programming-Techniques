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

class ClientUDP {
public: // Methods
    void startClient(int portno, const char* server_address);
    void sendAndReceiveMessage();
private: // Methods
    int sockInit();
    int sockQuit();
    int sockClose(SOCKET sock);
private: // Members
    bool initialized{false};
    int sockfd;
    struct sockaddr_in serv_addr;

};


#endif //HOMEWORK_4_CLIENTUDP_HPP
