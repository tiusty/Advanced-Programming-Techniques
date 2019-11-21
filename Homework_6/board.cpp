/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/14/2019
Description:
 Implements the board class
*/

#include <GL/glut.h>
#include "board.h"
#include <random>
#include <tuple>

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
            // Only rows, 0,1,6,7 are occupied in the beginning of the game
            if(i == 0 || i == 1 || i == 6 || i == 7)
            {
                board.at(i).at(j).occupied = true;
            }
            board.at(i).at(j).team = team;
        }
    }
}

void Board::drawPieces(bool enhanced)
{
    // Loops through all the spaces on the board and if it is occuppied,
    //  then the corresponding piece is drawn
    for(int i=0; i < boardSize; i++)
    {
        for(int j=0; j < boardSize; j++)
        {
            if(board.at(i).at(j).occupied)
            {
                glPushMatrix();
                // Translate piece to middle of the square
                glTranslatef(j*Board::boardLen+Board::boardLen/2, i*Board::boardLen+Board::boardLen/2, 0);
                // Scale the piece so it is bounded properly in the square
                glScalef(.75, .75, 1);
                // Draw the piece
                board.at(i).at(j).draw(enhanced);
                glPopMatrix();
            }
        }
    }
}

void Board::movePawn()
{
    bool pieceMoved{false};

    // Stores the pawns that were attempted to be moved
    // Prevents repeating pawns and also if there is no solution, then instead of looping
    //  forever, once all the pawns have been tried, then the loop will exit
    std::array<std::tuple<int,int>, 16> triedPawns;
    //Stores how many pawns are in the triedArray
    int triedPawnsCounter{0};

    while(!pieceMoved)
    {
        // End condition if no pawns can move
        if(triedPawnsCounter == triedPawns.size())
        {
            break;
        }

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 7); // define the range
        std::uniform_int_distribution<> distr2(0, 1); // define the range
        int x = distr(eng);
        int y = distr(eng);

        // Tests to see if this pawn was already tested
        bool alreadyTested{false};
        for(auto &test : triedPawns)
        {
            if(std::get<0>(test) == x && std::get<1>(test) == y)
            {
                alreadyTested = true;
            }
        }
        if(alreadyTested)
        {
            continue;
        }

        // If the space has a pawn and it is occupied then attempt to move the pawn
        if(board.at(y).at(x).type == Piece::pawn && board.at(y).at(x).occupied)
        {
            // Mark that the pawn has been tried
            triedPawns.at(triedPawnsCounter) = std::make_tuple(x,y);
            triedPawnsCounter++;

            // Randomly determine the direction the pawn will move first
            int direction = distr2(eng);
            // Since the random number is 0 and 1, a 0 means -1.
            if(direction == 0)
            {
                direction = -1;
            }

            // Loop through the 2 possible moves the pawn can do
            for(int i=0; i<2;i++)
            {
                // Determine the new x and y coordinates based on the direction
                int newX = x;
                int newY = y+direction;

                // If the move is valid, then move the piece
                if(checkIfValid(newX, newY))
                {
                    movePiece(x,y,newX, newY);
                    pieceMoved = true;
                    break;
                }
                // If the move is not valid then try the other direction
                else
                {
                    if(direction == -1)
                    {
                        direction = 1;
                    }
                    else
                    {
                        direction = -1;
                    }
                }
            }
        }
    }
}

void Board::moveKnight()
{
    bool pieceMoved{false};

    // Stores the pawns that were attempted to be moved
    // Prevents repeating pawns and also if there is no solution, then instead of looping
    //  forever, once all the pawns have been tried, then the loop will exit
    std::array<std::tuple<int,int>, 4> triedKnights;
    //Stores how many pawns are in the triedArray
    int triedKnightsCounter{0};

    while(!pieceMoved)
    {
        // End condition if no pawns can move
        if(triedKnightsCounter == triedKnights.size())
        {
            break;
        }

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 7); // define the range
        int x = distr(eng);
        int y = distr(eng);

        // Tests to see if this pawn was already tested
        bool alreadyTested{false};
        for(auto &test : triedKnights)
        {
            if(std::get<0>(test) == x && std::get<1>(test) == y)
            {
                alreadyTested = true;
            }
        }
        if(alreadyTested)
        {
            continue;
        }

        // If the space has a pawn and it is occupied then attempt to move the pawn
        if(board.at(y).at(x).type == Piece::knight && board.at(y).at(x).occupied)
        {
            // Mark that the pawn has been tried
            triedKnights.at(triedKnightsCounter) = std::make_tuple(x, y);
            triedKnightsCounter++;

            // Randomly determine the direction the knight will move first
            // This helps make some randomness in the movement of the knights
            int direction = distr(eng);

            // Loop through the 8 possible moves the knight can do
            for(int i=0; i<8;i++)
            {
                int newX{0}, newY{0};
                // From the randomly choicen number, loop through all the possible moves the knight can do
                int move = direction +i % 8;

                // Each move case corresponds to a different move the knight can do
                if(move == 0)
                {
                    newX = x + 1;
                    newY = y + 2;
                }
                else if (move == 1)
                {
                    newX = x + 2;
                    newY = y+1;
                }
                else if (move == 2)
                {
                    newX = x + 2;
                    newY = y-1;
                }
                else if (move == 3)
                {
                    newX = x+1;
                    newY = y-2;
                }
                else if (move == 4)
                {
                    newX = x-1;
                    newY = y-2;
                }
                else if (move == 5)
                {
                    newX = x-2;
                    newY = y-1;
                }
                else if (move == 6)
                {
                    newX = x-2;
                    newY = y+1;
                }
                else if (move == 7)
                {
                    newX = x-1;
                    newY = y+2;
                }

                // Check to see if the move is valid, if it is then move the piece
                if(checkIfValid(newX, newY))
                {
                    movePiece(x,y,newX,newY);
                    pieceMoved = true;
                    break;
                }
            }
        }
    }
}

bool Board::checkIfValid(int x, int y)
{
    // Piece can't be off the board, in an occupied space
    return !(x > 7 || x < 0 || y > 7 || y < 0 || board.at(y).at(x).occupied);
}

void Board::movePiece(int oldX, int oldY, int newX, int newY)
{
    // Set new sapce
    board.at(newY).at(newX).type = board.at(oldY).at(oldX).type;
    board.at(newY).at(newX).team = board.at(oldY).at(oldX).team;
    board.at(newY).at(newX).occupied=true;

    // Reset old space
    board.at(oldY).at(oldX).occupied = false;
    board.at(oldY).at(oldX).type = Piece::nothing;
}
