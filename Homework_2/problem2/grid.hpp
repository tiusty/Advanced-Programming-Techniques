/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Header file for the Grid class which stores the matrix of elements for the grid adn associated functions
*/

#ifndef HOMEWORK_2_GRID_HPP
#define HOMEWORK_2_GRID_HPP

#include <vector>         // std::vector
#include <array>          // std::array
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
    /**
     * Default constructor that initializes an empty matrix
     */
    Grid() = default;
    /**
     * Ctor that given a file loads a matrix into memory and stores it into matrix variable
     * @param filename The file name of the matrix to read in
     */
    explicit Grid(const char* filename);
    /**
     * Finds the max product of neighbors based on the number of number of neighbors desired
     */
    void findMaxProductNeighbors();
    /**
     * Determines the largest product on a given line that contains the elementToCheck and
     *  up to numAdjNeighbors away.
     * @param xVec The xUnitVector that determines the line to check along
     * @param yVec The yUnitVector that determines the line to check along
     * @param elementToCheck The point that is being checked. Must be contained within the line
     */
    void largestProductAlongLine(int xVec, int yVec, gridElement elementToCheck);
    /**
     * Determines the product between two indices. The indices must lie along a line,
     * i.e up/down, right/left, on diagonal
     * @param startIndex The start index to check
     * @param endIndex  The end index to check
     * @return The product of the indices
     */
    int productBetweenIndices(gridIndex startIndex, gridIndex endIndex);
    /**
     * Generates the output-file for the solution
     */
    void generateOutput();

public: // Members
    /**
     * Determines the number of adj neighbors that should be checked
     *      For the homework it should be set to 4
     */
    static constexpr unsigned int numAdjNeighbors{4};
    /**
     * Stores the input matrix
     */
    std::vector<std::vector<int>> matrix;
    /**
     * Priority queue stores all but the top numAdjNeighbors elements. Objects are stored
     *  as gridElements which stores their coordinates in the matrix as well as its value
     */
    std::priority_queue<gridElement, std::vector<gridElement>, GridComparison> restOfElements;
    /**
     * Priority queue stores the top numAdjNeighbors. The reason these are in a different
     * queue is because these are the elements that contribute to the maxPossibleProduct.
     * Since you can't iterate through priority queues, the important indices need to be
     * kept separately for easier manipulation
     */
    std::priority_queue<gridElement, std::vector<gridElement>, GridComparison> topAdjElements;
    /**
     * Stores the current largest product by any numAdjNeighbor elements
     */
    int currentLargestProduct{0};
    /**
     * Stores the possible largest product left. As the largest elements get checked the largest remaining
     *  possible product will slowly decrease. This is used as the exit condition to confirm that
     *  we found the best possible solution. This value is determined by multiplying the remaining
     *  largest elements.
     */
    int maxPossibleProduct{1};
    /**
     * Stores the start index and end index of the largest product
     */
    std::array<gridIndex, 2> indexMaxProduct;

private: // Members
    /**
     * Stores the number of rows in the matrix
     */
    unsigned int numRows{0};
    /**
     * Stores the number of columns in the matrix
     */
    unsigned int numColumns{0};
    /**
     * Stores the filename for the output file
     */
    static constexpr const char* outputFileName{"output2.txt"};
};


#endif //HOMEWORK_2_GRID_HPP
