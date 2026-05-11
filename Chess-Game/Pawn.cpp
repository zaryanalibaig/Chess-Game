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
		//cout << "Move:" << move << endl;
		int row_diff = abs(to.row - pos.row);
		int col_diff = abs(to.col - pos.col);

		if (to.row > pos.row)
		{
			if (row_diff == 1 && col_diff == 1)
			{
				//Diagonal Movement of Pawn
				if (board.Grid[to.row][to.col] != nullptr &&
					board.Grid[to.row][to.col]->color == Black)
				{
					return true;
				}
				//En Passant
				else if (pos.row == 4 && board.Grid[to.row][to.col] == nullptr)
				{
					// Check which side the move is going toward
					if (pos.col + 1 <= 7 &&
						to.col == pos.col + 1 &&                          // moving toward right
						board.Grid[4][pos.col + 1] != nullptr &&
						board.Grid[4][pos.col + 1]->color == Black &&
						board.Grid[4][pos.col + 1]->move == 1)
					{
						return true;
					}
					else if (pos.col - 1 >= 0 &&
						to.col == pos.col - 1 &&                     // moving toward left
						board.Grid[4][pos.col - 1] != nullptr &&
						board.Grid[4][pos.col - 1]->color == Black &&
						board.Grid[4][pos.col - 1]->move == 1)
					{
						return true;
					}
				}
				return false;
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
	//Black Pawn
	else
	{
		int row_diff = abs(to.row - pos.row);
		int col_diff = abs(to.col - pos.col);

		if (to.row < pos.row)
		{
			if (row_diff == 1 && col_diff == 1)
			{
				//Diagonal Movement of Pawn
				if (board.Grid[to.row][to.col] != nullptr &&
					board.Grid[to.row][to.col]->color == White)
				{
					return true;
				}
				//En Passant
				else if (pos.row == 3 &&
					board.Grid[to.row][to.col] == nullptr)  // landing square must be empty
				{
					// Check which side the move is going toward
					if (pos.col + 1 <= 7 &&
						to.col == pos.col + 1 &&                          // moving toward right
						board.Grid[3][pos.col + 1] != nullptr &&
						board.Grid[3][pos.col + 1]->color == White &&
						board.Grid[3][pos.col + 1]->move == 1)
					{
						return true;
					}
					else if (pos.col - 1 >= 0 &&
						to.col == pos.col - 1 &&                     // moving toward left
						board.Grid[3][pos.col - 1] != nullptr &&
						board.Grid[3][pos.col - 1]->color == White &&
						board.Grid[3][pos.col - 1]->move == 1)
					{
						return true;
					}
				}
				return false;
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