#include"Game_Header.h"
#include<iostream>

bool Game::castling(Position to, Board& board)
{
	if (isinCheck(White) || isinCheck(Black))
	{
		return false;
	}
	else
	{
		//Castling Implementation(White)
		if (board.Grid[0][4] != nullptr && board.Grid[0][4]->getSymbol() == 'K' &&
			!(board.Grid[0][4]->isMoved) && board.Grid[0][0] != nullptr &&
			!(board.Grid[0][0]->isMoved) && board.Grid[0][7] != nullptr &&
			!(board.Grid[0][7]->isMoved))
		{
			Position pos;
			pos.row = 0;
			int col_diff = to.col - 4;
			if (col_diff < 0)		//Queen Side Castling
			{
				//Path Check
				for (int i = 3;i > 0;i--)
				{
					if (board.Grid[0][i] != nullptr)
					{
						return false;
					}
				}
				//Attack on Path Check
				for (int i = 1;i < 4;i++)
				{
					pos.col = i;
					for (int j = 0;j <= 7;j++)
					{
						for (int k = 0;k <= 7;k++)
						{
							if (board.Grid[j][k] != nullptr &&
								board.Grid[j][k]->color == Black &&
								board.Grid[j][k]->isValidmove(pos, board))
							{
								return false;
							}
						}
					}
				}
				return true;
			}
			else				//King Side Castling
			{
				//Path Check
				for (int i = 5;i < 7;i++)
				{
					if (board.Grid[0][i] != nullptr)
					{
						return false;
					}
				}
				//Attack on Path
				for (int i = 5;i < 7;i++)
				{
					pos.col = i;
					for (int j = 0;j <= 7;j++)
					{
						for (int k = 0;k <= 7;k++)
						{
							if (board.Grid[j][k] != nullptr &&
								board.Grid[j][k]->color == Black &&
								board.Grid[j][k]->isValidmove(pos, board))
							{
								return false;
							}
						}
					}
				}
				return true;
			}
		}
		//Castling Implemetation(Black)
		else
		{
			if (board.Grid[7][4] != nullptr && board.Grid[7][4]->getSymbol() == 'k' &&
				!(board.Grid[7][4]->isMoved) &&
				board.Grid[7][0] != nullptr && !(board.Grid[7][0]->isMoved) &&
				board.Grid[7][7] != nullptr && !(board.Grid[7][7]->isMoved))
			{
				Position pos;
				pos.row = 7;
				int col_diff = to.col - 4;

				if (col_diff < 0)    // Queen Side Castling
				{
					//Path Check
					for (int i = 3; i > 0; i--)
					{
						if (board.Grid[7][i] != nullptr)
						{
							return false;
						}
					}
					//Attack on Path
					for (int i = 1; i < 4; i++)
					{
						pos.col = i;
						for (int j = 0; j <= 7; j++)
						{
							for (int k = 0; k <= 7; k++)
							{
								if (board.Grid[j][k] != nullptr &&
									board.Grid[j][k]->color == White &&
									board.Grid[j][k]->isValidmove(pos, board))
								{
									return false;
								}
							}
						}
					}
					return true;
				}
				else                 // King Side Castling
				{
					//Path Check
					for (int i = 5; i < 7; i++)
					{
						if (board.Grid[7][i] != nullptr)
						{
							return false;
						}
					}
					//Attack on Path
					for (int i = 5; i < 7; i++)
					{
						pos.col = i;
						for (int j = 0; j <= 7; j++)
						{
							for (int k = 0; k <= 7; k++)
							{
								if (board.Grid[j][k] != nullptr &&
									board.Grid[j][k]->color == White &&
									board.Grid[j][k]->isValidmove(pos, board))
								{
									return false;
								}
							}
						}
					}
					return true;
				}
			}
		}
	}
}
