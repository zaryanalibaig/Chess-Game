#include"Game_Header.h"
#include<iostream>
#include<cmath>
King::King(Position pos, Color color) : Piece(pos, color)//constructor
{

}
bool King::isValidmove(Position to, Board& board)
{
	if (pos.row == to.row && pos.col == to.col)
	{
		return false;
	}
	// row and column difference
	int rowDiff = abs(to.row - pos.row);
	int colDiff = abs(to.col - pos.col);
	//As king can move only one square
	if (rowDiff > 1 || colDiff > 1)
	{
		return false;
	}
	//to check whether it is a valid move or not
	if (board.Grid[to.row][to.col] != nullptr)
	{
		//to check if king and the other piece at its destination is of same color 
		if (board.Grid[to.row][to.col]->color == color)
		{
			return false;
		}
	}
	return true;
}
char King::getSymbol()
{
	return 'K';
}