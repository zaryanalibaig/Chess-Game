#include"Game_Header.h"
using namespace std;
#include<iostream>
Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Grid[i][j] = nullptr;
		}
	}

	// Making the Board 
	// Making the first row for white
	Grid[0][0] = new Rook({ 0,0 }, White);
	Grid[0][1] = new Knight({ 0,1 }, White);
	Grid[0][2] = new Bishop({ 0,2 }, White);
	Grid[0][3] = new Queen({ 0,3 }, White);
	Grid[0][4] = new King({ 0,4 }, White);
	Grid[0][5] = new Bishop({ 0,5 }, White);
	Grid[0][6] = new Knight({ 0,6 }, White);
	Grid[0][7] = new Rook({ 0,7 }, White);

	// Initializing the pawn pieces

	Grid[1][0] = new Pawn({ 1,0 }, White);
	Grid[1][1] = new Pawn({ 1,1 }, White);
	Grid[1][2] = new Pawn({ 1,2 }, White);
	Grid[1][3] = new Pawn({ 1,3 }, White);
	Grid[1][4] = new Pawn({ 1,4 }, White);
	Grid[1][5] = new Pawn({ 1,5 }, White);
	Grid[1][6] = new Pawn({ 1,6 }, White);
	Grid[1][7] = new Pawn({ 1,7 }, White);
	// Initializing the Bllack pieces
	Grid[7][0] = new Rook({ 7,0 }, Black);
	Grid[7][1] = new Knight({ 7,1 }, Black);
	Grid[7][2] = new Bishop({ 7,2 }, Black);
	Grid[7][3] = new Queen({ 7,3 }, Black);
	Grid[7][4] = new King({ 7,4 }, Black);
	Grid[7][5] = new Bishop({ 7,5 }, Black);
	Grid[7][6] = new Knight({ 7,6 }, Black);
	Grid[7][7] = new Rook({ 7,7 }, Black);
	// Initializing the black pawns
	Grid[6][0] = new Pawn({ 6,0 }, Black);
	Grid[6][1] = new Pawn({ 6,1 }, Black);
	Grid[6][2] = new Pawn({ 6,2 }, Black);
	Grid[6][3] = new Pawn({ 6,3 }, Black);
	Grid[6][4] = new Pawn({ 6,4 }, Black);
	Grid[6][5] = new Pawn({ 6,5 }, Black);
	Grid[6][6] = new Pawn({ 6,6 }, Black);
	Grid[6][7] = new Pawn({ 6,7 }, Black);

}
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
Piece* Board::Getpiece(Position pos) {
	Piece* P = Grid[pos.row][pos.col];
	return P;
}
void Board::display() {
	cout << "  ---------------------------------\n";
	for (int row = 7; row >= 0; row--) {
		cout << row + 1;
		for (int col = 0; col < 8; col++) {
			if (Grid[row][col] != nullptr) {
				char symbol = Grid[row][col]->getSymbol();
				if (Grid[row][col]->color == White) {
					setColor(COLOR_WHITE_PIECE);
					symbol = toupper(symbol);
				}
				else {
					setColor(COLOR_BLACK_PIECE);
					symbol = tolower(symbol);
				}
				cout << " | " << symbol;
				resetColor();
			}
			else {
				cout << " | .";
				// empty square where there is nullptr
			}
		}
		cout << " | " << row + 1;
		cout << "\n  ---------------------------------\n";

	}
	cout << "    a   b   c   d   e   f   g   h\n\n";
}
void Board::highlightmove(Position pos) {
	if (pos.row < 0 || pos.row >= 8 || pos.col < 0 || pos.col >= 8) {
		cout << "Invalid board position!\n";
		return;
	}
	Piece* p = Grid[pos.row][pos.col];

	if (p == nullptr) {
		cout << "Invalid move , No piece at that position !\n";
		return;
	}
	cout << "  ---------------------------------\n";
	for (int row = 7; row >= 0; row--) {
		cout << row + 1;
		for (int col = 0; col < 8; col++) {
			Position to = { row, col };

			if (row == pos.row && col == pos.col) {
				cout << " | ";
				setColor(COLOR_SELECTED);
				cout << "X";          // selected the piece to move
				resetColor();
			}
			else if (p->isValidmove(to, *this)) {
				cout << " | ";
				setColor(COLOR_HIGHLIGHT);
				cout << "*";          // valid move square
				resetColor();
			}
			else if (Grid[row][col] != nullptr) {
				char symbol = Grid[row][col]->getSymbol();
				if (Grid[row][col]->color == White) {
					symbol = toupper(symbol);
					cout << " | ";
					setColor(COLOR_WHITE_PIECE);
				}
				else {
					symbol = tolower(symbol);
					cout << " | ";
					setColor(COLOR_BLACK_PIECE);

				}cout << symbol;
				resetColor();

			}
			else {
				cout << " | .";
				// empty square where there is nullptr
			}
		}
		cout << " | " << row + 1;
		cout << "\n  ---------------------------------\n";

	}
	cout << "    a   b   c   d   e   f   g   h\n\n";
}
Board::~Board() {
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++) {
			if (Grid[i][j] != nullptr) {
				delete Grid[i][j];
				Grid[i][j] = nullptr;
			}
		}
	}
}
