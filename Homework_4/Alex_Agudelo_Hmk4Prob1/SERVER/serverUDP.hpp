/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description: 
*/

#ifndef HOMEWORK_4_SERVERUDP_HPP
#define HOMEWORK_4_SERVERUDP_HPP


class ServerUDP {
public: // Methods
    void startServer(int portno);
    void receiveMessages();

private: // Members
    bool initialized{false};
    int sockfd;
};


#endif //HOMEWORK_4_SERVERUDP_HPP
