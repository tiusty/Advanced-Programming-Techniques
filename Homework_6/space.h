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
    void draw(bool enhanced);
    void drawRegular();
    void drawPawn();
    void drawRook();
    void drawKnight();
    void drawBishop();
    void drawQueen();
    void drawKing();
    void drawEnhanced();
    void drawPawnEnhanced();
    void drawRookEnhanced();
    void drawKnightEnhanced();
    void drawBishopEnhanced();
    void drawQueenEnhanced();
    void drawKingEnhanced();
    void setColor();

public: // Members
    bool team{false};
    bool occupied{false};
    Piece type{Piece::nothing};
};


#endif //HOMEWORK_6_SPACE_H
