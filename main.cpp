#ifndef NDEBUG
#define PDEBUG 1
#endif

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <cctype>
#include <vector>
#include "checkers.h"
#include "boardpos.h"
#include "inputerror.h"

//using namespace std;

//board position
//    c0 c1 c2 ...
// r0
// r1
// r2
// ...

BoardPos getPos(const char*);
ifpos_pair_type getPosPair();

int **board = NULL;
const int INITBOARD[ROW][COL] = { { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, RED, VACANT, RED, VACANT, RED, VACANT, RED }, { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK }, { BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK } };

void initBoard() {
	if(board != NULL) {
		for(int i = 0; i < ROW; ++i)
			delete board[i];
		delete board;
	}
	board = new int*[ROW];
	for(int i = 0; i < ROW; ++i) {
		board[i] = new int[COL];
		for(int j = 0; j < COL; ++j)
			board[i][j] = INITBOARD[i][j];
	}
	BoardPos::board = ::board;
}

int numRedsAlive = 24;
int numBlacksAlive = 24; //#BlackLivesMatter

bool blackTurn = false;

int getTurn() {
	return blackTurn ? BLACK : RED;
}

char pieceRep(int i) {
	switch(i) {
	case RED:
		return 'r';
	case RKING:
		return 'R';
	case BLACK:
		return 'b';
	case BKING:
		return 'B';
	}
	return ' ';
}

#if PDEBUG
void printBoard() {
	for(int l = 0; l < ROW; ++l) {
		std::cout << std::setw(1) << l + 1;
		for(int m = 0; m < COL; ++m)
			std::cout << std::setw(2) << pieceRep(*BoardPos(l, m)); //hahaha >:D
		std::cout << "\n";
	}
	std::cout << "  A B C D E F G H\n";
	std::cout << std::endl;
}
#else
void printBoard() {
	std::cout << " x---x---x---x---x---x---x---x---x\n";
	for(int l = 0; l < ROW; ++l) {
		std::cout << std::setw(1) << l + 1;
		for(int m = 0; m < COL; ++m)
		std::cout << std::setw(4) << pieceRep(*(l[board] + m)); //hahaha >:D
		std::cout << "\n";
		std::cout << " x---x---x---x---x---x---x---x---x\n";
	}
	std::cout << "    A   B   C   D   E   F   G   H\n";
}
#endif

int columnFinder(const std::string& p) {
	int c = int(p[0]);
	if('A' <= c && c <= 'H') return c - 'A';
	if('a' <= c && c <= 'h') return c - 'a';
	return -1;
}

void moveCheck(const BoardPos& i, const BoardPos& f) {
	BoardPos d(f - i);
	d.r = std::abs(d.r);
	d.c = std::abs(d.c);

	//time to play baseball
	if(isVacant(*i)) throw input_error("can only move a red or black piece");
	if(!isMatching(*i, getTurn())) throw input_error("can only move your own piece");
	if(!isVacant(*f)) throw input_error("can only move to an empty space");
	if(d.r != d.c) throw input_error("can only move diagonal");
	if(d.r > 2) throw input_error("can only move as far as 2 diagonal spaces");
	if(d.r == 0) throw input_error("cannot stay at the same spot");
	if(d.r == 2 && !isOpposite(*i, *(i / f))) throw input_error("can only jump over opposite piece");
	if(!isForward(i, f)) throw input_error("can only move forward");
}

//check if midpoint is complement and f is vacant
bool jumpCheck(const BoardPos& i, const BoardPos& f) {
	return 0 <= f.r && f.r < ROW && 0 <= f.c && f.c < COL && isOpposite(*i, *(i / f)) && isVacant(*f) && isForward(i, f);
}

std::vector<BoardPos> getValidJumps(const BoardPos& p) {
	const BoardPos main(2, 2), anti(2, -2);
	BoardPos f[] = { p + main, p - anti, p - main, p + anti };
	std::vector<BoardPos> ret;
	for(unsigned i = 0; i < 4; ++i)
		if(jumpCheck(p, i[f])) ret.push_back(f[i]);
	return ret;
}

//code's a bit jumbled here
//forgive me plz :c
BoardPos jumpFrom(const BoardPos& p) {
	auto valid = getValidJumps(p); //number of valid jumps from p
	if(valid.size() == 0) {
		blackTurn = !blackTurn;
		return p;
	}
	{
		std::cout << "Continue jumping? (Y/N)\n";
		char c = '\0';
		while(c != 'y') {
			std::string s;
			std::cin >> s;
			if((c = std::tolower(s[0])) == 'n') return p;
		}
	}
	BoardPos jump = valid[0];
	if(valid.size() != 1) {
		jump = BoardPos(-1, -1);
		while(!jumpCheck(p, jump))
			try { //TODO: implement lambda for try/catch
				jump = getPos("Where would you like to jump to?\n");
			} catch(const std::exception& e) {
				std::cout << "Error: " << e.what() << "\n";
			}
	}
	*(p / jump) = VACANT;
	std::swap(*p, *jump);
	return jump;
}

bool movePiece(const BoardPos& i, const BoardPos& f) {
	moveCheck(i, f);
	if((f - i).r == 1) {
		std::swap(*i, *f);
		blackTurn = !blackTurn;
		return false;
	}
	*(i / f) = VACANT;
	std::swap(*i, *f);
	if(isRed(*(i / f))) --numRedsAlive;
	else --numBlacksAlive;
	jumpFrom(f);
	return true;
}

bool movePiece(const ifpos_pair_type& p) {
	return movePiece(p.first, p.second);
}

BoardPos getPos(const char* msg) {
	std::cout << msg;
	std::string s;
	std::cin >> s;
	if(s.length() != 2) throw input_error("input length is not 2");
	int r = int(s[1]) - int('1'), c = columnFinder(s);
	if(c == -1) throw input_error("invalid column");
	if(!(0 <= r && r < ROW)) throw input_error("invalid row");
	return BoardPos(r, c);
}

//Ask the user what pieces they want to move
ifpos_pair_type getPosPair() {
	std::cout << (blackTurn ? "Black" : "Red") << "'s turn!\n";
	BoardPos i = getPos("What piece do you want to move?\n");
	BoardPos f = getPos("Where do want to move it to?\n");
	return ifpos_pair_type(i, f);
}

void play() {
	printBoard();
	try {
		auto move = getPosPair();
		BoardPos i, f;
		if(movePiece(move)) {
			printBoard();
			i = move.second;
			while(!((f = jumpFrom(i)) == i)) {
				printBoard();
				i = f;
			}
		}
	} catch(const std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}

int main() {
	initBoard();
	while(numRedsAlive && numBlacksAlive)
		play();
	std::cout << "Winner: " << (!numBlacksAlive ? "Black" : "Red");
}
