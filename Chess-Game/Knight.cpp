#include<iostream>
#include"Game_Header.h"

//Parameterized Constructor
Knight::Knight(Position pos, Color color) :Piece(pos, color)
{

}

//Move Function
bool Knight::isValidmove(Position to, Board& board)
{
	int row_diff = abs(to.row - pos.row);
	int col_diff = abs(to.col - pos.col);
	//Testing for valid move

	if (!((row_diff == 2 && col_diff == 1) ||		//Knight movement
		(row_diff == 1 && col_diff == 2)))
	{
		return false;
	}
	else if ((board.Grid[to.row][to.col] != nullptr) &&			//Box Color and Occupation
		(board.Grid[to.row][to.col]->color == color))
	{
		return false;
	}
	else		//Knight can move to Position
	{
		return true;
	}
}

//Getter to Display Symbol on Board
char Knight::getSymbol()
{
	return 'n';
}
