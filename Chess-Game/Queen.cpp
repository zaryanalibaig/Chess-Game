#include "Game_Header.h"
#include<iostream>
#include<cmath>
Queen::Queen(Position pos, Color color) : Piece(pos, color)//constructor
{

}
bool Queen::isValidmove(Position to, Board& board)
{
	if (pos.row == to.row && pos.col == to.col)
	{
		return false;
	}
	//to check if it moves in the same row or column && abs to make the diff +ve 
	int rowDiff = abs(to.row - pos.row);
	int colDiff = abs(to.col - pos.col);
	//now to check whether it moves in the same row or column
	bool sameRow = (pos.row == to.row);
	bool sameCol = (pos.col == to.col);
	bool diagonal = (rowDiff == colDiff);
	if (!(sameRow || sameCol || diagonal))
	{
		return false;
	}
	//now checking the valid moves
	if (sameRow)
	{
		if (to.col > pos.col) // moving right
		{
			for (int j = pos.col + 1; j < to.col; j++)
			{
				if (board.Grid[pos.row][j] != nullptr)
				{
					return false;
				}
			}
		}
		else // moving left
		{
			for (int j = pos.col - 1; j > to.col; j--)
			{
				if (board.Grid[pos.row][j] != nullptr)
				{
					return false;
				}
			}
		}
	}
	else if (sameCol)
	{
		if (to.row > pos.row) // down
		{
			for (int i = pos.row + 1; i < to.row; i++)
			{
				if (board.Grid[i][pos.col] != nullptr)
				{
					return false;
				}
			}
		}
		else // up
		{
			for (int i = pos.row - 1; i > to.row; i--)
			{
				if (board.Grid[i][pos.col] != nullptr)
				{
					return false;
				}
			}
		}
	}
	else  if (abs(to.row - pos.row) == abs(to.col - pos.col)) // if this diff is not equal it can't move diagonally 
	{
		// down-right
		if (to.row > pos.row && to.col > pos.col)
		{
			int i = pos.row + 1;
			int j = pos.col + 1;
			while (i < to.row && j < to.col)
			{
				if (board.Grid[i][j] != nullptr)
				{
					return false;
				}
				i++;
				j++;
			}
		}
		// up-left
		if (to.row < pos.row && to.col < pos.col)
		{
			int i = pos.row - 1;
			int j = pos.col - 1;
			while (i > to.row && j > to.col)
			{
				if (board.Grid[i][j] != nullptr)
				{
					return false;
				}
				i--;
				j--;
			}
		}
		// down-left
		if (to.row > pos.row && to.col < pos.col)
		{
			int i = pos.row + 1;
			int j = pos.col - 1;
			while (i < to.row && j > to.col)
			{
				if (board.Grid[i][j] != nullptr)
				{
					return false;
				}
				i++;
				j--;
			}
		}
		// up-right
		if (to.row < pos.row && to.col > pos.col)
		{
			int i = pos.row - 1;
			int j = pos.col + 1;
			while (i > to.row && j < to.col)
			{
				if (board.Grid[i][j] != nullptr)
				{
					return false;
				}
				i--;
				j++;
			}
		}
	}
}
char Queen::getSymbol()
{
	return 'Q';
}
