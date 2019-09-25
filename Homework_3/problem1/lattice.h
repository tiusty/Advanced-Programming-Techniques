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
    void findNumberOfPaths();
    unsigned int numLatNodes();
    unsigned int getNode(unsigned int row, unsigned int col);
    unsigned long long int getParentSum(unsigned int row, unsigned int col);
public: // Members
    static constexpr unsigned int maxLatElem{250000};
    std::array<long long int, maxLatElem> latNodes{-1};
private: // Methods
private: // Members
    unsigned int latHeight{0};
    unsigned int latWidth{0};
    unsigned int latHeightNodes{0};
    unsigned int latWidthNodes{0};
};


#endif //HOMEWORK_3_LATTICE_H
