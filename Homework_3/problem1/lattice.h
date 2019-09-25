/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
*/

#ifndef HOMEWORK_3_LATTICE_H
#define HOMEWORK_3_LATTICE_H

#include <array>

class Lattice {

public: // Methods
    Lattice() = default;
    Lattice(unsigned int height, unsigned width);
    unsigned int numLatNodes();
    unsigned int getNode(unsigned int row, unsigned int col);
public: // Members
private: // Methods
private: // Members
    static constexpr unsigned int maxLatElem{250000};
    unsigned int latHeight{0};
    unsigned int latWidth{0};
    std::array<int, maxLatElem> latNodes{-1};
};


#endif //HOMEWORK_3_LATTICE_H
