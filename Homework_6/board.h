/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/14/2019
Description:
 Stores information about which pieces are on the board and where they are
*/

#ifndef HOMEWORK_6_BOARD_H
#define HOMEWORK_6_BOARD_H

#include <array>
#include "space.h"

/**
 * Board class stores the board layout with the corresponding pieces in the spaces.
 * Note: Even though I attempted to make sizes dynamic, I ended up hardcoding
 *  values in code due to lack of time.
 */
class Board {
public: // Methods
    /**
     * Ctor that sets up the board with the pieces in the initial position
     */
    Board();
    /**
     * Draws all the pieces on the board
     * @param enhanced Determines if the enhanced mode is being used or not
     */
    void drawPieces(bool enhanced);
    /**
     * Moves a random pawn and random direction. (Pawns can only move forward or backwards one space)
     */
    void movePawn();
    /**
     * Moves a random knight a random direction. (Following the L shape)
     */
    void moveKnight();
    /**
     * Determines if a given move is valid or not
     * @param x The x coordinated being tested
     * @param y The y coordinated being tested
     */
    bool checkIfValid(int x, int y);
    /**
     * This assumes that the move was already checked to be valid
     * Moves the piece on oldX, oldY to newX, newY keeping the same type and team
     * @param oldX The old x position of the piece
     * @param oldY The old y position of the piece
     * @param newX The new x position of the piece
     * @param newY The new y position of the piece
     */
    void movePiece(int oldX, int oldY, int newX, int newY);

public: // Members
    /**
     * The size of the edge of the square board
     */
    static constexpr unsigned int boardSize = 8;
    /**
     * The size of the edge of the square.
     */
    static constexpr double boardLen = 1; // The size of the length of one board
    /**
     * All the spaces on the board
     */
    std::array<std::array<Space, boardSize>, boardSize> board;
};


#endif //HOMEWORK_6_BOARD_H
