/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/14/2019
Description:
 Stores information regarding a single space
*/

#ifndef HOMEWORK_6_SPACE_H
#define HOMEWORK_6_SPACE_H

/**
 * Enum determines the type of the space
 */
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

/**
 * Stores information regarding a single space on the chess board
 */
class Space {
public: // Methods
    /**
     * Draws the space if it is a piece
     * @param enhanced Determines if the enhanced mode should be used or not
     */
    void draw(bool enhanced);
    /**
     * Draws the unenhanced version of the space
     */
    void drawRegular();
    /**
     * Draws the unenhanced pawn
     */
    void drawPawn();
    /**
     * Draws the unenhanced rook
     */
    void drawRook();
    /**
     * Draws the unenhanced knight
     */
    void drawKnight();
    /**
     * Draws the unenhanced bishop
     */
    void drawBishop();
    /**
     * Draws the unenhanced queen
     */
    void drawQueen();
    /**
     * Draws the unenhanced king
     */
    void drawKing();
    /**
     * Draws the enhanced piece
     */
    void drawEnhanced();
    /**
     * Draws the enhanced pawn
     */
    void drawPawnEnhanced();
    /**
     * Draws the enhanced rook
     */
    void drawRookEnhanced();
    /**
     * Draws the enhanced knight
     */
    void drawKnightEnhanced();
    /**
     * Draws the enhanced bishop
     */
    void drawBishopEnhanced();
    /**
     * Draws the enhanced queen
     */
    void drawQueenEnhanced();
    /**
     * Draws the enhanced King
     */
    void drawKingEnhanced();
    /**
     * Sets the color, and material properites for the piece
     */
    void setColor();

public: // Members
    bool team{false};
    bool occupied{false};
    Piece type{Piece::nothing};
};


#endif //HOMEWORK_6_SPACE_H
