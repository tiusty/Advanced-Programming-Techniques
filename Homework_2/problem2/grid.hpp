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
#include <queue>          // std::priority_queue

// <row, column>
using gridIndex = std::pair<int, int>;
// <coordinate, value>
using element = std::pair<gridIndex,int>;

class GridComparison
{
public:
    bool operator() (const element& lhs, element& rhs) const
    {
        return (lhs.second<rhs.second);
    }
};


class Grid {
public: // Methods
    Grid() = default;
    Grid(const char* filename);

public: // Members
    std::vector<std::vector<int>> matrix;
    std::priority_queue<element, std::vector<element >, GridComparison> element_queue;

private: // Members
    unsigned int numRows;
    unsigned int numColumns;
};


#endif //HOMEWORK_2_GRID_HPP
