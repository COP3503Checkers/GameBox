#ifndef CONNECTFOUR_H_
#define CONNECTFOUR_H_

namespace con4 {

//defined as const variables instead of #define
//to avoid problems with multiple declarations
const int VACANT = 0;
const int RED = 1;
const int BLACK = -1;

const int ROW = 6;
const int COL = 7;

bool isRed(int x) {
	return x == RED;
}
bool isBlack(int x) {
	return x == BLACK;
}
bool isVacant(int x) {
	return x == VACANT;
}
bool isMatching(int a, int b) {
	return isRed(a) ? isRed(b) : (isBlack(a) ? isBlack(b) : false);
}
bool isOpposite(int a, int b) {
	return isRed(a) ? isBlack(b) : (isBlack(a) ? isRed(b) : false);
}

} //namespace con4

#include <cstddef>
#include <utility>

namespace con4 {

struct BoardPos {
	static int **board;

	int r, c;

	BoardPos()
			: r(), c() {
	}
	BoardPos(int r, int c)
			: r(r), c(c) {
	}
	BoardPos(const BoardPos& p)
			: r(p.r), c(p.c) {
	}
	BoardPos& operator=(const BoardPos& p) {
		r = p.r, c = p.c;
		return *this;
	}

	int& operator*() {
		return board[r][c];
	}
	int& operator*() const {
		return board[r][c];
	}
	BoardPos operator-() const {
		return BoardPos(-r, -c);
	}
	BoardPos operator+(const BoardPos& p) const {
		return BoardPos(r + p.r, c + p.c);
	}
	BoardPos& operator+=(const BoardPos& p) {
		return *this = (*this + p);
	}
	BoardPos operator-(const BoardPos& p) const {
		return *this + -BoardPos(p);
	}
	BoardPos& operator-=(const BoardPos& p) {
		return *this = (*this - p);
	}
	//midpoint
	BoardPos operator/(const BoardPos& p) const {
		return BoardPos((r + p.r) / 2, (c + p.c) / 2);
	}
	bool operator==(const BoardPos& p) const {
		return r == p.r && c == p.c;
	}
};
int **BoardPos::board = NULL;

typedef std::pair<BoardPos, BoardPos> ifpos_pair_type;

} //namespace con4

#include <iostream>
#include <limits>
#include <iomanip>

namespace con4 {

//return char representation of how pieces should be displayed
char pieceRep(int i) {
	switch(i) {
	case RED:
		return 'r';
	case BLACK:
		return 'b';
	}
	return ' ';
}

void printBoard() {
	std::cout << "+---+---+---+---+---+---+---+\n";
	for(int l = 0; l < ROW; ++l) {
		for(int m = 0; m < COL; ++m)
			std::cout << "|" << std::setw(2) << pieceRep(*BoardPos(l, m)) << " ";
		std::cout << "|\n+---+---+---+---+---+---+---+\n";
	}
	std::cout << "  1   2   3   4   5   6   7\n";
}

int **board = NULL;
const int INITBOARD[ROW][COL] = { { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT } };
bool isBlackTurn = false;

//delete old board and make new board
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
	BoardPos::board = board;
}

//put a piece into column numbered c
//columns are indexed from 0
bool dropPiece(unsigned c) {
	unsigned i = 0;
	if(c > ROW) return 0;
	while(i < ROW && isVacant(*BoardPos(i, c)))
		++i;
	if(i == 0) return false;
	--i;
	if(isBlackTurn) *BoardPos(i, c) = BLACK;
	else *BoardPos(i, c) = RED;
	isBlackTurn = !isBlackTurn;
	return true;
}

//go through one turn
void play() {
	int c;
	printBoard();
	std::cout << (isBlackTurn ? "Black" : "Red") << "'s turn!" << std::endl;
	std::cout << "Where would you like to drop your piece? ";
	while(!(std::cin >> c)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error: NaN, try again: ";
	}
	if(dropPiece(c - 1)) {
		std::cout << "Congratulations" << std::endl;
	} else std::cout << "That's not on the board!" << std::endl;
}

//return if position represented by p is within bounds
bool withinBounds(const BoardPos& p) {
	return 0 <= p.r && p.r < ROW && 0 <= p.c && p.c < COL;
}

int winner() {
	typedef BoardPos b;
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			b p(i, j), q;
			if(isVacant(*p)) continue;
			if(withinBounds(q = (p + b(1, 1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, 2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, 3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			if(withinBounds(q = (p + b(1, 0))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, 0))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, 0))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			if(withinBounds(q = (p + b(1, -1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, -2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, -3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			if(withinBounds(q = (p + b(0, 1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(0, 2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(0, 3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
		}
	}
	return VACANT;
}

} //namespace con4

/*
example playthrough:
int main() {
	con4::initBoard();
	while(con4::isVacant(con4::winner()))
		con4::play();
	con4::printBoard();
	std::cout << "Winner: " << (con4::isBlackTurn ? "Red" : "Black") << std::endl;
}
*/

#endif
