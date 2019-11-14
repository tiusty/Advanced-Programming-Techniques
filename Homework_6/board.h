/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description:
 Stores information about which pieces are on the board and where they are
*/

#ifndef HOMEWORK_6_BOARD_H
#define HOMEWORK_6_BOARD_H

#include <array>
#include "space.h"

class Board {
public: // Methods
    Board();
    void drawPieces(bool enhanced);

public: // Members
    static constexpr unsigned int boardSize = 8;
    static constexpr double boardLen = 1; // The size of the length of one board
    std::array<std::array<Space, boardSize>, boardSize> board;
};


#endif //HOMEWORK_6_BOARD_H
