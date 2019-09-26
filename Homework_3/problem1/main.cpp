/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description:
 Main function for the program
*/

#include "lattice.h"

#include <iostream>
#include <unistd.h>

/**
 * Executes the main program
 */
int main(int argc, char *argv[])
{
    int opt;
    int height{0};
    int width{0};
    bool badArgs{false};

    // Gets arguments
    while((opt = getopt(argc, argv, "w:h:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                printf("height: %s\n", optarg);
                height = std::stoi(optarg);
                break;
            case 'w':
                printf("width: %s\n", optarg);
                width = std::stoi(optarg);
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                badArgs = true;
                break;
        }
    }

    // Only run the lattice program if the arguments were valid
    if (not badArgs)
    {
        Lattice lat(height,width);
        lat.findNumberOfPaths();
    } else {
        std::cerr << "Bad options specified" << std::endl;
    }
    return 1;
}
