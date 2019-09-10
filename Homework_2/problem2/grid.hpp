/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Header file for the Grid class which stores the matrix of elements for the grid adn associated functions
*/

#ifndef HOMEWORK_2_GRID_HPP
#define HOMEWORK_2_GRID_HPP

#include <vector>

class Grid {
public: // Methods
    Grid() = default;
    Grid(const char* filename);

public: // Members
    std::vector<std::vector<int>> matrix;

private: // Members
    unsigned int numRows;
    unsigned int numColumns;
};


#endif //HOMEWORK_2_GRID_HPP
