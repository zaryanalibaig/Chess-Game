#include"Game_Header.h"
#include<iostream>
#include<cstring>
Player::Player(string name, Color color) {
	this->name = name;
	this->color = color;
}
Game::Game() {
	string name;
	cout << "Enter the Name for Player with White pieces : " << endl;
	getline(cin, name);
	p1 = new Player(name,White);
	cout << "Enter the Name for player with black pieces : " << endl;
	getline(cin, name);
	p2 = new Player(name, Black);
	currentPlayer = p1;

}
void Game::start() {
	Position to, from;
	char arr[3],arr1[3];
	while (true) {
		board.display();
		cout << "Select the piece to move (in the classical form like e4): ";
		cin.getline(arr,2);
		arr[0] = tolower(arr[0]);
		arr[0] = arr[0] - 48;
		while (arr[0] > 7 || arr[2]>7) {
			cout << "Enter again : ";
			cin.getline(arr, 2);
			arr[0] = arr[0] - 'a';
		}
		from.col = arr[0]-'a';
		from.row = arr[1]-1;
		board.highlightmove(from);
		cout << "Select the destination (in the classical form like e4): ";
		cin.getline(arr1, 2);
		
		arr1[0] = tolower(arr1[0]);
		arr1[0] = arr1[0] - 'a';
		while (arr1[0] > 7 || arr1[2] > 7) {
			cout << "Enter again : ";
			cin.getline(arr1, 2);
			arr1[0] = arr1[0] - 'a';
		}
		to.col = arr1[0];
		to.row = arr1[1] - 1;
		bool a = board.makeMove(to, from);
		if (a) {
			if (isinCheck(currentPlayer->color)) {
				cout << "Your king will be exposed \n";
				continue;
			}
			else 
			{
				switchTurn();
				if (isCheckmate(currentPlayer->color)) {
					cout << currentPlayer->name << " lost \n";
					break;
				}
			}
		}
	}
}
void Game::switchTurn() {
	if (currentPlayer == p1) {
		currentPlayer = p2;
	}
	else
		currentPlayer = p1;
}
bool Game::isCheckmate(Color color) {
	if (!canEscape(color) && isinCheck(color)) {
		return true;
	}
	else
		return false;
}
bool Game::canEscape(Color color) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* p = board.Getpiece({ i, j });
			if (p == nullptr || p->color != color) 
				continue;

			for (int r = 0; r < 8; r++) {
				for (int c = 0; c < 8; c++) {
					if (i == r && j == c)
						continue;

					Position to = { r, c };
					Piece* target = board.Getpiece(to);
					if (target != nullptr && target->color == color) continue;

					if (p->isValidmove(to, board)) {
						// temp move
						Piece* captured = board.Grid[r][c];
						Position oldPos = p->pos;
						board.Grid[r][c] = p;
						board.Grid[i][j] = nullptr;
						p->pos = to;
						// checking whther after capturing or
						// blocking there is till check
						bool stillInCheck = isinCheck(color);

						// undo move
						board.Grid[i][j] = p;
						board.Grid[r][c] = captured;
						p->pos = oldPos;

						if (!stillInCheck) return true;
					}
				}
			}
		}
	}
	return false;
}

