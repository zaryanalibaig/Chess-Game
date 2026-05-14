#pragma once
#include<string>
using namespace std;
class Board;
struct Position {
	int row, col;
};
enum Color {
	White,
	Black
};
class Piece {
public:
	Position pos;
	Color color;
	bool isMoved = false;
	int move = 0;
	Piece(Position pos, Color color);
	Piece();
	virtual bool isValidmove(Position to, Board& board) = 0;
	virtual char getSymbol() = 0;
	virtual ~Piece() = default;
};
class Knight :public Piece {
public:
	Knight(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;

};
class Rook :public Piece {
public:
	bool rookMoved = false;
	Rook(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;
};
class Bishop :public Piece {
public:
	Bishop(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;

};
class Pawn :public Piece {
public:
	Pawn(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;

};
class Queen : public Piece {
public:
	Queen(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;

};
class King :public Piece {
public:
	
	King(Position pos, Color color);
	bool isValidmove(Position to, Board& board) override;
	char getSymbol() override;

};
class Board {
public:
	Piece* Grid[8][8];
	Board();
	Piece* Getpiece(Position);
	void highlightmove(Position);
	void display();
};
class Player {
public:
	string name;
	Color color;
	Player(string name, Color col);
};
class Game {
public:
	Board board;
	Player* p1;
	Player* p2;
	Player* currentPlayer;
	void start();
	Position FindKingLocation(Color color);
	bool isCheckmate(Color color);
	bool makeMove(Position to, Position from);
	bool castleKingSide(Color color, Position to);
	bool castleQueenSide(Color color, Position to);
	bool isinCheck(Color color);
	bool canEscape(Color color);
	void switchTurn();
	bool isStalemate(Color color);
	void getSafeline(string);
	Game();
	~Game();
};
#include <windows.h>

#define COLOR_WHITE_PIECE  14  // Bright yellow
#define COLOR_BLACK_PIECE  12  // Bright Red  
#define COLOR_HIGHLIGHT    10  // Bright Green
#define COLOR_SELECTED     11  // Bright cyan
#define COLOR_RESET         7  // Default grey

void setColor(int color);
void resetColor();