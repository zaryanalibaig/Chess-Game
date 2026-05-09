#include "Game_Header.h"
#include <iostream>
#include <cmath>
Queen::Queen(Position pos, Color color) : Piece(pos, color)
{

}
bool Queen::isValidmove(Position to, Board& board)
{
    if (board.Grid[to.row][to.col] != nullptr && board.Grid[to.row][to.col]->color == color)
    {
        return false;
    }
    if (pos.row == to.row && pos.col == to.col)
    {
        return false;
    }
    //column difference and row difference to determine how many squares it will move 
    int rowDiff = to.row - pos.row;
    int colDiff = to.col - pos.col;
    //checking whether it will move in the same row or column 
    bool sameRow = (rowDiff == 0);
    bool sameCol = (colDiff == 0);
    //checking whether it will move diagonally 
    bool diagonal = (abs(rowDiff) == abs(colDiff));
    if (!(sameRow || sameCol || diagonal))
    {
        return false;
    }
    // direction of movement
    int rowStep = 0;
    int colStep = 0;
    if (rowDiff > 0)
    {
        rowStep = 1;//indicates forward movement 
    }
    else if (rowDiff < 0)
    {
        rowStep = -1;//indicates backward movement 
    }
    if (colDiff > 0)
    {
        colStep = 1;//forward 
    }
    else if (colDiff < 0)
    {
        colStep = -1;//backward 
    }
    // start checking from next square
    int i = pos.row + rowStep;
    int j = pos.col + colStep;
    // path checking
    while (i != to.row || j != to.col)
    {
        if (board.Grid[i][j] != nullptr)
        {
            return false;
        }
        i += rowStep;
        j += colStep;
    }
    return true;
}

char Queen::getSymbol()
{
    return 'Q';
}