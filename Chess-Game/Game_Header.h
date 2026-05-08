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
	void highlightmove();
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
	void start();
	Game();
	~Game();
};