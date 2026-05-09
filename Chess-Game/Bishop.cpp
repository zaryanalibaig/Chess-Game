#include"Game_Header.h"
Bishop::Bishop(Position pos, Color color) {
	this->pos = pos;
	this->color = color;
}
bool Bishop::isValidmove(Position to, Board& B) {
	// checking if the square is not empty and also the color is same then 
	if (B.Grid[to.row][to.col] != nullptr && B.Grid[to.row][to.col]->color == this->color) {
		return false;
	}
	// finding row difference and column difference for bishop movement 
	int rowDif = pos.row - to.row;
	int colDif = pos.col - to.col;
	// row and column difference must be same as bishop moves in diagonal
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
		// chcecking if a piece is blocking the path 
		if (B.Grid[r][c] != nullptr) {
			return false;
		}
		r += rowStep;
		c += colStep;
	}
	return true;
}
// getting symbol to diaply it in board displaying
char Bishop::getSymbol() {
	return 'B';
}