/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description: 
*/

#ifndef HOMEWORK_6_SPACE_H
#define HOMEWORK_6_SPACE_H

enum class Piece
{
    nothing,
    pawn,
    rock,
    knight,
    bishop,
    king,
    queen
};

class Space {
public: // Members
    bool occupied{false};
    Piece type{Piece::nothing};
};


#endif //HOMEWORK_6_SPACE_H
