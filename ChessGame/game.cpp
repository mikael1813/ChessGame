#include "game.h"

Game::Game() {

	this->board.push_back({ "br","bk","bb","bq","bk","bb","bk","br" });
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
	this->board.push_back({ "wr","wk","wb","wq","wk","wb","wk","wr" });
}

tuple<unsigned short int, unsigned short int> Game::get_actual_postion(string position) {
	char letter = position.at(0);
	if (letter >= 'A' && letter <= 'Z') {
		letter = 'a' + (letter - 'A');
	}
	return { this->board_size - atoi(&position.at(1)),letter_positions.at(letter) };
}