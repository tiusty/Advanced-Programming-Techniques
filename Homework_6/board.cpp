/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description:
 Implements the board class
*/

#include <GL/glut.h>
#include "board.h"

// Define constexpr
constexpr double Board::boardLen;
constexpr unsigned int Board::boardSize;

Board::Board()
{
    bool team = true;
    for(int i=0; i < boardSize; i++)
    {
        // After finishing the first team, the second team will be true
        if(i > 3)
        {
            team = false;
        }
        for(int j=0; j < boardSize; j++)
        {
            Piece type{Piece::nothing};

            // These rows start with all pawns
            if(i == 1 || i == 6)
            {
                type = Piece::pawn;
            }
            // These rows depend on the column
            else if(i == 0 || i == 7)
            {
                if(j == 0 || j == 7)
                {
                    type = Piece::rook;
                }
                else if(j == 1 || j == 6)
                {
                    type = Piece::knight;
                }
                else if(j == 2 || j == 5)
                {
                    type = Piece::bishop;
                }
                else if(j == 3)
                {
                    type = Piece::queen;
                }
                else if(j == 4)
                {
                    type = Piece::king;
                }

            }
            board.at(i).at(j).type = type;
            board.at(i).at(j).occupied = true;
            board.at(i).at(j).team = team;
        }
    }
}

void Board::drawPieces()
{

    for(int i=0; i < boardSize; i++)
    {
        for(int j=0; j < boardSize; j++)
        {
            glPushMatrix();
                glTranslatef(j*Board::boardLen+Board::boardLen/2, i*Board::boardLen+Board::boardLen/2, 0);
            glScalef(.75, .75, 1);
            board.at(i).at(j).draw();
            glPopMatrix();
        }
    }
}
