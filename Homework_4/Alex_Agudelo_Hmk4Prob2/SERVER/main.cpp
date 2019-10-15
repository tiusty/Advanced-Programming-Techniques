/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/10/19
Description: 
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

    portno = atoi(argv[1]);

    ServerUDP udp_server;
    udp_server.startServer(portno);
    udp_server.spawnWorkers();
}
