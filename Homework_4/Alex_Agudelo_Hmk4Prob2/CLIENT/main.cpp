/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description: 
*/

#include "clientUDP.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    int portno;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }


    portno = atoi(argv[2]);

    ClientUDP udp_client;
    udp_client.startClient(portno, argv[1]);
    udp_client.promptForCommand();
//    udp_client.sendAndReceiveMessage();
}

