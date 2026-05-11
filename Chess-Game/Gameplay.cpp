#include"Game_Header.h"
#include<iostream>

int main()
{
	cout << "\n--------------------------------- Game Instructions -------------------------------\n";
	cout << "1. 8x8 Grid\n2. White pieces on rows 1-2, Black on rows 7-8\n";
	cout << "3. You input moves like e2 then e4 (column letter + row number)\n";
	cout << "4. White always goes first\n5. You cannot move into check (where your King is under attack)\n";
	cout << "6. If your King is in check you must get out of it\n7. Checkmate = King is in check with no escape → you lose\n";
	cout << "8. Castling - King moves 2 squares toward a Rook, Rook jumps to other side\n";
	cout << "9. En Passant - Special pawn capture (advanced)\n";
	cout << "10. To Win - Checkmate your opponent's King\n";
	cout << "-------------------------------------------------------------------------------------\n";
	Game game;
	game.start();
	return 0;
}