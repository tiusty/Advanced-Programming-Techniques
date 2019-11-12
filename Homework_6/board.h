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

public: // Members
    static constexpr unsigned int boardLen = 8;
    std::array<std::array<Space, boardLen>, boardLen> board;
};


#endif //HOMEWORK_6_BOARD_H
