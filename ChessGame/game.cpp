#include "game.h"

Game::Game() {

	this->board.push_back({ "br","bn","bb","bq","bk","bb","bn","br" });
	for (int i = 1; i < this->board_size - 1; i++) {
		vector<string> row;
		for (int j = 0; j < this->board_size; j++) {
			switch (i) {
			case 1:
				row.push_back("bp");
				break;
			case 6:
				row.push_back("wp");
				break;
			default:
				row.push_back("");
				break;
			}
		}
		this->board.push_back(row);
	}
	this->board.push_back({ "wr","wn","wb","wq","wk","wb","wn","wr" });
}

tuple<unsigned short int, unsigned short int> Game::get_actual_postion(const string position) {

	regex reg("[a-hA-H][0-9]");
	if (position.size() != 2 || !regex_match(position, reg)) {
		throw ;
	}

	char letter = position.at(0);
	if (letter >= 'A' && letter <= 'Z') {
		letter = 'a' + (letter - 'A');
	}
	return { this->board_size - atoi(&position.at(1)),letter_positions.at(letter) };
}

vector< tuple<unsigned short int, unsigned short int>> Game::get_all_possible_moves(const unsigned short int i, const unsigned short int j) {
	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	const string piece = this->board.at(i).at(j);

	if (piece == "bp") {
		if (this->board.at(i + 1).at(j) == "") {
			possible_moves.push_back({ i + 1,j });
		}
		if (i == 1 && this->board.at(i + 2).at(j) == "") {
			possible_moves.push_back({ i + 2,j });
		}
		if (j < this->board_size - 1 && this->board.at(i + 1).at(j + 1).at(0) == 'w') {
			possible_moves.push_back({ i + 1,j + 1 });
		}
		if (j > 0 && this->board.at(i + 1).at(j - 1).at(0) == 'w') {
			possible_moves.push_back({ i + 1,j + 1 });
		}
	}

	else if (piece == "wp") {
		if (this->board.at(i - 1).at(j) == "") {
			possible_moves.push_back({ i - 1,j });
		}
		if (i == this->board_size - 1 && this->board.at(i - 2).at(j) == "") {
			possible_moves.push_back({ i - 2,j });
		}
		if (j < this->board_size - 1 && this->board.at(i - 1).at(j + 1).at(0) == 'b') {
			possible_moves.push_back({ i - 1,j + 1 });
		}
		if (j > 0 && this->board.at(i - 1).at(j - 1).at(0) == 'b') {
			possible_moves.push_back({ i - 1,j + 1 });
		}
	}

	else if (piece.at(1) == 'n') {
		vector<int> moves{ -2,-1,1,2 };
		for (auto k : moves){
			for (auto l : moves) {
				if (abs(k) != abs(l)) {
					int posi = i + k, posj = j + l;
					if ((!(0 <= posi < this->board_size && 0 <= posj < this->board_size)) || this->board.at(posi).at(posj).at(0) == piece.at(0)) {
						break;
					}
					else if (this->board.at(posi).at(posj) == "") {
						possible_moves.push_back({ posi,posj });
					}
					else if (this->board.at(posi).at(posj).at(0) != piece.at(0)) {
						possible_moves.push_back({ posi,posj });
						break;
					}
				}
			}
		}
	}

	else if (piece.at(1) == 'b') {
		possible_moves = this->get_all_bishop_moves(i, j);
	}

	else if (piece.at(1) == 'r') {
		possible_moves = this->get_all_rook_moves(i, j);
	}

	else if (piece.at(1) == 'q') {
		possible_moves = this->get_all_queen_moves(i, j);
	}

	else if (piece.at(1) == 'k') {
		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				if (k != 0 && l != 0 && 0 <= i + k < this->board_size && 0 <= j + l < this->board_size && this->board.at(i + k).at(j + l) == "") {
					possible_moves.push_back({ i + k,j + l });
				}
			}
		}
	}

	return possible_moves;
}

vector< tuple<unsigned short int, unsigned short int>> Game::get_all_bishop_moves(const unsigned short int i, const unsigned short int j) {
	const char color = this->board.at(i).at(j).at(0);

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	for (int k = -1; j <= 1; k = k + 2) {
		for (int l = -1; l <= 1; l = l + 2) {
			vector< tuple<unsigned short int, unsigned short int>> aux = this->get_moves(i, j, k, l, color);
			possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
		}
	}

	return possible_moves;
}


vector< tuple<unsigned short int, unsigned short int>> Game::get_all_rook_moves(const unsigned short int i, const unsigned short int j) {
	const char color = this->board.at(i).at(j).at(0);

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	for (int k = -1; j <= 1; k = k + 2) {
		vector< tuple<unsigned short int, unsigned short int>> aux = this->get_moves(i, j, k, 0, color);
		possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
	}
	for (int l = -1; l <= 1; l = l + 2) {
		vector< tuple<unsigned short int, unsigned short int>> aux = this->get_moves(i, j, 0, l, color);
		possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());
	}

	return possible_moves;
}

vector< tuple<unsigned short int, unsigned short int>> Game::get_all_queen_moves(const unsigned short int i, const unsigned short int j) {
	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	vector< tuple<unsigned short int, unsigned short int>> aux;

	aux = this->get_all_bishop_moves(i, j);
	possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());

	aux = this->get_all_rook_moves(i, j);
	possible_moves.insert(possible_moves.end(), aux.begin(), aux.end());

	return possible_moves;
}

vector< tuple<unsigned short int, unsigned short int>> Game::get_moves(short int i, short int j, const short int k, const short int l, const char color) {

	vector< tuple<unsigned short int, unsigned short int>> possible_moves;

	while (true) {
		i += k;
		j += l;
		if ((!(0 <= i < this->board_size && 0 <= j < this->board_size)) || this->board.at(i).at(j).at(0) == color) {
			break;
		}
		else if (this->board.at(i).at(j) == "") {
			possible_moves.push_back({ i,j });
		}
		else if (this->board.at(i).at(j).at(0) != color) {
			possible_moves.push_back({ i,j });
			break;
		}
	}

	return possible_moves;
}