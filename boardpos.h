#ifndef BOARDPOS_H_
#define BOARDPOS_H_

#include <utility>
#include "checkers.h"

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

bool isForward(const BoardPos& i, const BoardPos& f) {
	if(isKing(*i)) return true;
	if(isRed(*i)) return f.r > i.r;
	else if(isBlack(*i)) return f.r < i.r;
	return false;
}

#endif
