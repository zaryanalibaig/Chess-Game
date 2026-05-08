#include"Game_Header.h"
Bishop::Bishop(Position pos, Color color) {
	this->pos = pos;
	this->color = color;
}
bool Bishop::isValidmove(Position to, Board& B) {
	if (B.Grid[to.row][to.col] != nullptr && B.Grid[to.row][to.col]->color == this->color) {
		return false;
	}
	int rowDif = pos.row - to.row;
	int colDif = pos.col - to.col;
	if (abs(rowDif) != abs(colDif)) {
		return false;
	}
	int rowStep;
	int colStep;
	if (rowDif > 0) {
		rowStep = -1;
	}
	else
		rowStep = +1;
	if (colDif > 0) {
		colStep = -1;
	}
	else
		colStep = +1;
	int r = pos.row + rowStep;
	int c = pos.col + colStep;
	while (r != to.row || c != to.col) {
		if (B.Grid[r][c] != nullptr) {
			return false;
		}
		r += rowStep;
		c += colStep;
	}
	return true;
}
char Bishop::getSymbol() {
	return 'B';
}