#include<iostream>
#include"Game_Header.h"

//Parameterized Constructor
Pawn::Pawn(Position pos, Color color) :Piece(pos, color)
{

}

//Move Function
bool Pawn::isValidmove(Position to, Board& board)
{
	if (color == White)
	{
		int row_diff = abs(to.row - pos.row);
		int col_diff = abs(to.col - pos.col);

		if (to.row > pos.row)
		{
			if (row_diff == 1 && col_diff == 1 &&
				board.Grid[to.row][to.col] != nullptr)
			{
				//Diagonal Movement of Pawn
				if (board.Grid[to.row][to.col]->color == Black)
				{
					return true;
				}
				else
				{
					return false;
				}
				//En Passant
			}
			else if (to.col == pos.col)
			{
				//2 Steps in First Move
				if (pos.row == 1 && to.row == 3 &&
					board.Grid[2][to.col] == nullptr &&
					board.Grid[3][to.col] == nullptr)
				{
					return true;
				}
				//Pawn Movement
				else if (to.row == pos.row + 1 &&
					board.Grid[to.row][to.col] == nullptr)
				{
					return true;
				}
				//Invalid Move
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		//Pawn cannot move back
		else
		{
			return false;
		}
	}
	else
	{
		int row_diff = abs(to.row - pos.row);
		int col_diff = abs(to.col - pos.col);

		if (to.row < pos.row)
		{
			if (row_diff == 1 && col_diff == 1 &&
				board.Grid[to.row][to.col] != nullptr)
			{
				//Diagonal Movement of Pawn
				if (board.Grid[to.row][to.col]->color == White)
				{
					return true;
				}
				else
				{
					return false;
				}
				//En Passant
			}
			else if (to.col == pos.col)
			{
				//2 Steps in First Move
				if (pos.row == 6 && to.row == 4 &&
					board.Grid[5][to.col] == nullptr &&
					board.Grid[4][to.col] == nullptr)
				{
					return true;
				}
				//Pawn Movement
				else if (to.row == pos.row - 1 &&
					board.Grid[to.row][to.col] == nullptr)
				{
					return true;
				}
				//Invalid Move
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		//Pawn cannot move back
		else
		{
			return false;
		}
	}
}

char Pawn::getSymbol()
{
	return 'p';
}