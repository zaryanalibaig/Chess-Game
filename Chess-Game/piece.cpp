#include"Game_Header.h"
Piece::Piece(Position pos,Color color) {
	this->pos = pos;
	this->color = color;
}
Piece::Piece() {
	this->pos = { -1,-1 };
	this->color = White;
}