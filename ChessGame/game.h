#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

class Game {
private:
	vector<vector<string>> board;
	const unsigned short int board_size = 8;
	const map<char, unsigned short int> letter_positions{ {'a',0},{'b',1},{'c',2},{'d',3},{'e',4},{'f',5},{'g',6},{'h',7} };
public:
	Game();

	//position is a actual chess board position like E3 (so position is like [a-hA-H][0-9])
	//return actual position in matrix of position (ex. get_actual_postion("E3") => (5,4) )
	tuple<unsigned short int, unsigned short int> get_actual_postion(string position);

	vector< tuple<unsigned short int, unsigned short int>> get_all_possible_moves(const unsigned short int i, const unsigned short int j);

	vector< tuple<unsigned short int, unsigned short int>> get_all_bishop_moves(const unsigned short int i, const unsigned short int j);

	vector< tuple<unsigned short int, unsigned short int>> get_all_rook_moves(const unsigned short int i, const unsigned short int j);

	vector< tuple<unsigned short int, unsigned short int>> get_all_queen_moves(const unsigned short int i, const unsigned short int j);

	vector< tuple<unsigned short int, unsigned short int>> get_moves(const short int i, const short int j, const short int k, const short int l,const char color);



};


#endif // !'GAME_H_'