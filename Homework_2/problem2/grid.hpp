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
#include <array>
#include <queue>          // std::priority_queue

// Stores an index i.e coordinate
// <row, column>
using gridIndex = std::pair<int, int>;
// Stores a grid element, with the coordinate and the value associated with that index
// <coordinate, value>
using gridElement = std::pair<gridIndex,int>;

/**
 * Grid Comparison operator that compares two gridElements
 */
class GridComparison
{
public:
    /**
     * Orders the priority queue largest at top to smallest
     */
    bool operator() (const gridElement& lhs, gridElement& rhs) const
    {
        return (lhs.second<rhs.second);
    }
};

/**
 * Class takes a given matrix and will find the largest numAdjElements product in the matrix
 */
class Grid {
public: // Methods

    Grid() = default;
    explicit Grid(const char* filename);
    void findMaxProductNeighbors();
    void largestProductAlongLine(int xVec, int yVec, gridElement elementToCheck);
    int productBetweenIndices(gridIndex startIndex, gridIndex endIndex);

public: // Members
    std::vector<std::vector<int>> matrix;
    std::priority_queue<gridElement, std::vector<gridElement>, GridComparison> restOfElements;
    std::priority_queue<gridElement, std::vector<gridElement>, GridComparison> topAdjElements;
    static constexpr unsigned int numAdjNumbers{4};
    int currentLargestProduct{0};
    int maxPossibleProduct{1};
    std::array<gridIndex, Grid::numAdjNumbers> indexMaxProduct;

private: // Members
    unsigned int numRows{0};
    unsigned int numColumns{0};
};


#endif //HOMEWORK_2_GRID_HPP
