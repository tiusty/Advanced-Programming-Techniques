/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/18/19
Description:
 Starts a UDP server
*/

#include <serverUDP.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    int portno;

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    // Store the port number the server is going to listen for connections on
    portno = atoi(argv[1]);

    // Create the server and start it
    ServerUDP udp_server;
    udp_server.startServer(portno);
    udp_server.spawnWorkers();
}
