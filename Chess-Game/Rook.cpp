#include"Game_Header.h"
Rook::Rook(Position pos, Color color) {
    this->pos = pos;
    this->color = color;
}
bool Rook::isValidmove(Position to, Board& B) {
    if (pos.col != to.col && pos.row != to.row) {
        return false;
    }
    int rowdif = 0;
    int coldif = 0;
    if (to.col > pos.col) {
        coldif = 1;
    }
    else if (to.col < pos.col) {
        coldif = -1;
    }
    if (to.row > pos.row) {
        rowdif = 1;
    }
    else if (to.row < pos.row) {
        rowdif = -1;
    }
    int r = pos.row + rowdif;
    int c = pos.col + coldif;

    while (r != to.row || c != to.col) {
        if (B.Grid[r][c] != nullptr) {
            return false;
        }
        r += rowdif;
        c += coldif;
    }
    if (B.Grid[to.row][to.col] != nullptr) {
        if (B.Grid[to.row][to.col]->color == this->color) {
            return false;
        }
    }
    return true;
}
char Rook::getSymbol() {
    return 'R';
}
