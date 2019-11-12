/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description:
 Implements the board class
*/

#include "board.h"

Board::Board()
{
    for(int i=0; i < boardLen; i++)
    {
        for(int j=0; j < boardLen; j++)
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
                    type = Piece::rock;
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
        }
    }
}
