#include"Game_Header.h"
#include<iostream>
#include<cstring>

//Player Class Constructor
Player::Player(string name, Color color) {
	this->name = name;
	this->color = color;
}
//Game Class Implementation

//Constructor
Game::Game() {
	string name;
	cout << "Player Name with White pieces : ";
	getline(cin, name);
	p1 = new Player(name,White);
	cout << "Player Name with black pieces : ";
	getline(cin, name);
	p2 = new Player(name, Black);
	currentPlayer = p1;
}

//Destructor
Game::~Game()
{
	delete p1;
	delete p2;
}

//Check Whether this move can be made or not
bool Game::makeMove(Position to, Position from)
{
	//Validation
	if (from.row < 0 || from.row >= 8 || from.col < 0 || from.col >= 8) {
		cout << "Invalid board position!\n";
		return false;
	}
	Piece* piece = board.Getpiece(from);

	//Castling Condition
	if (castleKingSide(board.Grid[from.row][from.col]->color,to) ||
		castleQueenSide(board.Grid[from.row][from.col]->color, to))
	{
		return true;
	}

	//Valid Move Condition
	else if (piece->isValidmove(to, board))
	{
		piece->isMoved = true;
		piece->move++;

		if (board.Grid[to.row][to.col] == nullptr)
		{
			int row;

			if (piece->color == White)		//Checks En Passant Piece
				row = to.row - 1;
			else
				row = to.row + 1;

			if (to.col != from.col && board.Grid[row][to.col] != nullptr)
			{
				delete board.Grid[row][to.col];
				board.Grid[row][to.col] = nullptr;
			}

			board.Grid[to.row][to.col] = board.Grid[from.row][from.col];
			piece->pos = to;
			board.Grid[from.row][from.col] = nullptr;
		}
		else
		{
			delete board.Grid[to.row][to.col];
			piece->pos = to;
			board.Grid[to.row][to.col] = board.Grid[from.row][from.col];
			board.Grid[from.row][from.col] = nullptr;
		}

		//Pawn Promotion

		if (piece->getSymbol() == 'p' && (piece->pos.row == 0 || piece->pos.row==7))
		{
			int ch;
			Color color = piece->color;

			cout << "\n----- Pawn Promotion -----\n";
			cout << "1. Queen\n2. Rook\n3. Knight\n4. Bishop\n";
			cout << "Enter your Choice: ";
			cin >> ch;
			cin.ignore();

			while (ch < 1 || ch>4)
			{
				cout << "Invalid Choice! Enter b/w 1 - 4: ";
				cin >> ch;
				cin.ignore();
			}

			delete piece;
			piece = nullptr;
			
			if (ch == 1)
			{
				piece = new Queen(to, color);
			}
			else if (ch == 2)
			{
				piece = new Rook(to, color);
			}
			else if (ch == 3)
			{
				piece = new Knight(to, color);
			}
			else
			{
				piece = new Bishop(to, color);
			}

			board.Grid[to.row][to.col] = piece;
			
		}
		return true;
	}
	else
	{

		return false;
	}
}

//Strt Function - Starts Game
void Game::start() {
	Position to, from;
	char arr[3],arr1[3];
	//For Gameplay - Till Checkmate
	while (true)
	{

		board.display();

		cout << "Current Player: ";
		(currentPlayer->color == White) ?
			cout << "White\n" : cout << "Black\n";
		cout << endl;

		cout << "Select the piece to move (Like e4): ";
		cin.getline(arr,3);

		//Conversion of Column(Alphabet) to respective integer 
		arr[0] = tolower(arr[0]);
		arr[0] = arr[0] - 'a';
		from.row = arr[1]-'0' - 1;;

		//Validation
		while (arr[0] > 7 || from.row>7)
		{
			cout << "Enter again : ";
			cin.getline(arr, 3);
			arr[0] = arr[0] - 'a';
			from.row = arr[1] - '0' - 1;

		}
		from.col = arr[0];
		//Displays '*' on path of a Piece
		board.highlightmove(from);
		cout << "Select the destination (Like e4): ";
		cin.getline(arr1, 3);
		
		//Conversion of Column(Alphabet) to respected integer 
		arr1[0] = tolower(arr1[0]);
		arr1[0] = arr1[0] - 'a';
		to.row = arr1[1] - '0' - 1;
		//Validation
		while (arr1[0] > 7 || to.row> 7)
		{
			cout << "Enter again : ";
			cin.getline(arr1, 3);
			arr1[0] = arr1[0] - 'a';
			to.row = arr1[1] - '0' - 1;
		}

		to.col = arr1[0];

		bool a = makeMove(to, from);

		//Swith Turn
		if (a)
		{
			if (isinCheck(currentPlayer->color))
			{
				cout << "Your king will be exposed \n";
				continue;
			}
			else 
			{
				switchTurn();
				if (isCheckmate(currentPlayer->color))
				{
					cout << currentPlayer->name << " lost \n";
					break;
				}
			}
		}
		else
			cout << "Invalid Move\n";
	}
}

//Check Function - Whether King is in Check or not
bool Game::isinCheck(Color color)
{
	Position P = Game::FindKingLocation(color);
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (board.Grid[i][j] != nullptr)
			{
				if (board.Grid[i][j]->color != color &&
					board.Grid[i][j]->isValidmove(P, board))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//Switch Function - To Swith Turn between Players
void Game::switchTurn() {
	if (currentPlayer == p1) {
		currentPlayer = p2;
	}
	else
		currentPlayer = p1;
}

//Checkmate Function - Checks Whether it is Checkmate or not
bool Game::isCheckmate(Color color) {
	if (!canEscape(color) && isinCheck(color)) {
		return true;
	}
	else
		return false;
}

//Escape Function - Checks Whether King can Escape from Check or not
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

//Finds King Location on the board
Position Game::FindKingLocation(Color color)
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (board.Grid[i][j] != nullptr)
			{
				if (board.Grid[i][j]->getSymbol() == 'K' &&
					board.Grid[i][j]->color == color)
				{
					return { i, j };
				}
			}
		}
	}
	return { -1,-1 };
}

//King Side Castling
bool Game::castleKingSide(Color color, Position to)
{
	if (to.col != 6)
	{
		return false;
	}

	if (isinCheck(color))
	{
		return false;
	}

	Position pos;

	//White Side Castling
	if (color == White)
	{
		pos.row = 0;

		// Check king and rook existence
		if (board.Grid[0][4] == nullptr || board.Grid[0][7] == nullptr)
		{
			return false;
		}

		// Check correct pieces
		if (board.Grid[0][4]->getSymbol() != 'K' ||
			board.Grid[0][7]->getSymbol() != 'R' ||
			board.Grid[0][4]->isMoved ||
			board.Grid[0][7]->isMoved)
		{
			return false;
		}
		// Path clearance between king and rook
		for (int i = 5; i < 7; i++)
		{
			if (board.Grid[0][i] != nullptr)
			{
				return false;
			}
		}
		// Checks Attack on Path
		for (int i = 4; i <= 6; i++)
		{
			pos.col = i;
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (board.Grid[j][k] &&
						board.Grid[j][k]->color == Black &&
						board.Grid[j][k]->isValidmove(pos, board))
					{
						return false;
					}
				}
			}
		}
		
		board.Grid[0][6] = board.Grid[0][4];		//King Movement
		board.Grid[0][5] = board.Grid[0][7];		//Rook Movement

		board.Grid[0][4] = nullptr;
		board.Grid[0][7] = nullptr;

		return true;
	}

	//Black Side Castling
	else
	{
		pos.row = 7;

		// Check king and rook existence
		if (board.Grid[7][4] == nullptr || board.Grid[7][7] == nullptr)
		{
			return false;
		}

		// Check correct pieces
		if (tolower(board.Grid[7][4]->getSymbol()) != 'k' ||
			tolower(board.Grid[7][7]->getSymbol()) != 'r' ||
			board.Grid[7][4]->isMoved ||
			board.Grid[7][7]->isMoved)
		{
			return false;
		}
		// Path clearance between king and rook
		for (int i = 5; i < 7; i++)
		{
			if (board.Grid[7][i] != nullptr)
			{
				return false;
			}
		}
		// Checks Attack on Path
		for (int i = 4; i <= 6; i++)
		{
			pos.col = i;
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (board.Grid[j][k] &&
						board.Grid[j][k]->color == White &&
						board.Grid[j][k]->isValidmove(pos, board))
					{
						return false;
					}
				}
			}
		}

		board.Grid[7][6] = board.Grid[7][4];		//King Movement
		board.Grid[7][5] = board.Grid[7][7];		//Rook Movement

		board.Grid[7][4] = nullptr;
		board.Grid[7][7] = nullptr;

		return true;
	}

	return false;
}

//Queen Side Castling
bool Game::castleQueenSide(Color color, Position to)
{
	if (to.col != 2)
	{
		return false;
	}

	if (isinCheck(color))
	{
		return false;
	}

	Position pos;

	//White Side Castling
	if (color == White)
	{
		pos.row = 0;

		// Check king and rook existence
		if (board.Grid[0][4] == nullptr || board.Grid[0][0] == nullptr)
		{
			return false;
		}

		// Check correct pieces
		if (board.Grid[0][4]->getSymbol() != 'K' ||
			board.Grid[0][0]->getSymbol() != 'R' ||
			board.Grid[0][4]->isMoved ||
			board.Grid[0][0]->isMoved)
		{
			return false;
		}

		// Path clearance between king and rook
		for (int i = 1; i < 4; i++)
		{
			if (board.Grid[0][i] != nullptr)
			{
				return false;
			}
		}

		// Checks Attack on Path
		for (int i = 2; i <= 4; i++)
		{
			pos.col = i;

			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (board.Grid[j][k] &&
						board.Grid[j][k]->color == Black &&
						board.Grid[j][k]->isValidmove(pos, board))
					{
						return false;
					}
				}
			}
		}

		board.Grid[0][2] = board.Grid[0][4];   // King Movement
		board.Grid[0][3] = board.Grid[0][0];   // Rook Movement

		board.Grid[0][4] = nullptr;
		board.Grid[0][0] = nullptr;

		return true;
	}

	//Black Side Castling
	else
	{
		pos.row = 7;

		// Check king and rook existence
		if (board.Grid[7][4] == nullptr || board.Grid[7][0] == nullptr)
		{
			return false;
		}

		// Check correct pieces 
		if (tolower(board.Grid[7][4]->getSymbol()) != 'k' ||
			tolower(board.Grid[7][0]->getSymbol()) != 'r' ||
			board.Grid[7][4]->isMoved ||
			board.Grid[7][0]->isMoved)
		{
			return false;
		}

		// Path clearance between king and rook
		for (int i = 1; i < 4; i++)
		{
			if (board.Grid[7][i] != nullptr)
			{
				return false;
			}
		}

		// Checks Attack on Path
		for (int i = 2; i <= 4; i++)
		{
			pos.col = i;

			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					if (board.Grid[j][k] &&
						board.Grid[j][k]->color == White &&
						board.Grid[j][k]->isValidmove(pos, board))
					{
						return false;
					}
				}
			}
		}

		board.Grid[7][2] = board.Grid[7][4];   // King Movement
		board.Grid[7][3] = board.Grid[7][0];   // Rook Movement

		board.Grid[7][4] = nullptr;
		board.Grid[7][0] = nullptr;

		return true;
	}

	return false;
}