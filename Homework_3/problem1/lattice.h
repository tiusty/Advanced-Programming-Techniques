/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description:
 Class stores a lattice and computes the number of paths to the bottom right of the lattice
*/

#ifndef HOMEWORK_3_LATTICE_H
#define HOMEWORK_3_LATTICE_H

#include <array>

/**
 * Stores a lattice and helps fine the number of paths to bottom right
 * Note: Only the upper triangle is stored of the lattice matrix due to symmetry. There is no reason to
 * duplicate the matrix for the bottom half. We can still find the number of paths to bottom right using
 * the upper triangle information.
 */
class Lattice {

public: // Methods
    /**
     * Default ctor
     */
    Lattice() = default;
    /**
     * Ctor that initializes the lattice with the given height and width
     * @param height The height of the lattice
     * @param width The width of the lattice
     */
    Lattice(unsigned int height, unsigned width);
    /**
     * Function determines the number of paths in the given lattice
     */
    void findNumberOfPaths();
    /**
     * Uses a single threaded approach to solving number of paths
     */
    void findNumberOfPathsSingleThread();
    /**
     * Uses openmp for solving the number of paths
     */
    void findNumberOfPathsOpenMp();
    /**
     * Determines the number of nodes in the lattice
     * @return Number of nodes in the lattice
     */
    unsigned int numLatNodes();
    /**
     * Gets a node index in the array given the coordinates that it corresponds to.
     * Note: Only the upper triangle is stored, so if a lower triangular node is requested, it will throw an exception
     * @param row The row of the node
     * @param col The column of the node
     * @return The index of the node in the array
     */
    unsigned int getNode(unsigned int row, unsigned int col);
    /**
     * Returns the sum of the nodes parents. I.e the top and left nodes
     * @param row The row of the desired node
     * @param col The column of the desired node
     * @return The sum (if they exist) of the parents
     */
    unsigned long long int getParentSum(unsigned int row, unsigned int col);
    /**
     * Outputs the result to console and to a file
     */
    void outputResults();
public: // Members
    /**
     * Determines the maximum number of elements that can be populated
     */
    static constexpr unsigned int maxLatElem{400000};
    /**
     * Stores all the elements in the lattice.
     */
    std::array<unsigned long long int, maxLatElem> latNodes{{0}};
private: // Members
    /**
     * Determines if openMP support is being used
     */
    static constexpr bool openMPSupport{true};
    /**
     * Constexpr for the output file name
     */
    static constexpr const char* outputFileName{"output1.txt"};
    /**
     * The height of the lat in squares
     */
    unsigned int latHeight{0};
    /**
     * The width of the lat in squares
     */
    unsigned int latWidth{0};
    /**
     * The height of the lat in number of nodes
     */
    unsigned int latHeightNodes{0};
    /**
     * The width of the lattice in number of nodes
     */
    unsigned int latWidthNodes{0};
};


#endif //HOMEWORK_3_LATTICE_H
