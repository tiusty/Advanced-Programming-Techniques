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

// <row, column>
using gridIndex = std::pair<int, int>;
// <coordinate, value>
using gridElement = std::pair<gridIndex,int>;

class GridComparison
{
public:
    bool operator() (const gridElement& lhs, gridElement& rhs) const
    {
        return (lhs.second<rhs.second);
    }
};


class Grid {
public: // Methods
    Grid() = default;
    explicit Grid(const char* filename);
    void updateMaxPossibleProduct(int value, std::priority_queue<int, std::vector<int>, std::greater<> > &productNums);
    void findMaxProductNeighbors();
    void largestProductAlongLine(int xVec, int yVec, gridElement elementToCheck);
    int productBetweenIndices(gridIndex startIndex, gridIndex endIndex);

public: // Members
    std::vector<std::vector<int>> matrix;
    std::priority_queue<gridElement, std::vector<gridElement>, GridComparison> element_queue;
    static constexpr unsigned int numAdjNumbers{4};
    int currentLargestProduct{0};
    int maxPossibleProduct{1};
    std::array<gridIndex, Grid::numAdjNumbers> indexMaxProduct;

private: // Methods

private: // Members
    unsigned int numRows{0};
    unsigned int numColumns{0};
};


#endif //HOMEWORK_2_GRID_HPP
