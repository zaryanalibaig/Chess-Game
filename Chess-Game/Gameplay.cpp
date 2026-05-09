#include"Game_Header.h"
#include<iostream>
bool Game::isinCheck(Color color)
{
	//checking the king whether it is in check or not 
	Position P = Game::FindKingLocation(color);
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (board.Grid[i][j] != nullptr)
			{
				if (board.Grid[i][j]->color != color && board.Grid[i][j]->isValidmove(P, board))
				{
					return true;
				}
			}
		}
	}
	return false;
}
Position Game::FindKingLocation(Color color)
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (board.Grid[i][j] != nullptr)
			{
				if (board.Grid[i][j]->getSymbol() == 'K' && board.Grid[i][j]->color == color)
				{
					return { i, j };
				}
			}
		}
	}
	return { -1,-1 };
}