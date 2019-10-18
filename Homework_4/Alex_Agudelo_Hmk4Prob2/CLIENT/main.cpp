/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/18/19
Description:
 Starts up a UDP client
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

    // Store the port number the client wants to connect to
    portno = atoi(argv[2]);

    // Create the server and start it
    ClientUDP udp_client;
    udp_client.startClient(portno, argv[1]);
    udp_client.spawnWorkers();
}

