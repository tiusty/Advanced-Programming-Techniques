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
    rook,
    knight,
    bishop,
    king,
    queen
};

class Space {
public: // Methods
    void draw();
    void drawPawn();
    void drawRook();
    void drawKnight();
    void drawBishop();
    void drawQueen();
    void drawKing();
    void setColor();

public: // Members
    bool team{false};
    bool occupied{false};
    Piece type{Piece::nothing};
};


#endif //HOMEWORK_6_SPACE_H
