#ifndef CONNECTFOUR_H_
#define CONNECTFOUR_H_

namespace con4 {

//defined as const variables instead of #define
// to avoid problems with multiple declarations
//constants here
const int VACANT = 0;
const int RED = 1;
const int BLACK = -1;

//board dimensions
const int ROW = 6;
const int COL = 7;

//helper functions, inline these if necessary
bool isRed(int x) {
	return x == RED;
}
bool isBlack(int x) {
	return x == BLACK;
}
bool isVacant(int x) {
	return x == VACANT;
}
//return if both a and b are on same/opposite side, respectively
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

//object representation of board position
//only allows 1 board per run due to static int **board
struct BoardPos {
	//pointer to board as a 2d int array
	static int **board;

	//position represented by two ints
	//change to unsigned?
	int r, c;
	
	//constructors
	BoardPos()
			: r(), c() {
	}
	BoardPos(int r, int c)
			: r(r), c(c) {
	}
	
	//copy constructor and equals overload
	BoardPos(const BoardPos& p)
			: r(p.r), c(p.c) {
	}
	BoardPos& operator=(const BoardPos& p) {
		r = p.r, c = p.c;
		return *this;
	}
	
	//return value of piece on board
	//because *BoardPos(1,2) looks nicer than board[1][2]?
	//lol get outta here
	int& operator*() {
		return board[r][c];
	}
	int& operator*() const {
		return board[r][c];
	}
	
	//position arithmetic
	//treats position as a vector
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
	
	//midpoint of this and p
	BoardPos operator/(const BoardPos& p) const {
		return BoardPos((r + p.r) / 2, (c + p.c) / 2);
	}
	
	bool operator==(const BoardPos& p) const {
		return r == p.r && c == p.c;
	}
};

//just to be pedantic
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

//output board representation to cout
void printBoard() {
	std::cout << "+---+---+---+---+---+---+---+\n";
	for(int l = 0; l < ROW; ++l) {
		for(int m = 0; m < COL; ++m)
			std::cout << "|" << std::setw(2) << pieceRep(*BoardPos(l, m)) << " ";
		std::cout << "|\n+---+---+---+---+---+---+---+\n";
	}
	std::cout << "  1   2   3   4   5   6   7\n";
}

//the board with int values being manipulated as the game progresses
int **board = NULL;
//the default board
const int INITBOARD[ROW][COL] = { { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT } };
//flag for whether it's black's turn
//isBlackTurn = !isBlackTurn to flip turns
bool isBlackTurn = false;

//delete old board and make new board
void initBoard() {
	//delete old board
	if(board != NULL) {
		for(int i = 0; i < ROW; ++i)
			delete board[i];
		delete board;
	}
	//and...
	//make new board
	board = new int*[ROW];
	for(int i = 0; i < ROW; ++i) {
		board[i] = new int[COL];
		for(int j = 0; j < COL; ++j)
			board[i][j] = INITBOARD[i][j];
	}
	//set pointer in BoardPos to the new board
	//30 minutes of debugging >.>
	BoardPos::board = board;
}

//put a piece into column numbered c
//columns are indexed from 0
//returns whether drop was successful
bool dropPiece(unsigned c) {
	//get first unfilled space going down in the column
	unsigned i = 0;
	if(c > ROW) return 0;
	while(i < ROW && isVacant(*BoardPos(i, c)))
		++i;
	//column is completely filled, return unsuccessful
	if(i == 0) return false;
	//go back up to unfilled slot
	--i;
	//fill the slot and flip turns
	if(isBlackTurn)
		*BoardPos(i, c) = BLACK;
	else
		*BoardPos(i, c) = RED;
	isBlackTurn = !isBlackTurn;
	return true;
}

//go through one turn
void play() {
	int c;
	
	printBoard();
	std::cout << (isBlackTurn ? "Black" : "Red") << "'s turn!" << std::endl;
	
	//get column
	std::cout << "Where would you like to drop your piece? ";
	//TODO: put this into its own function
	while(!(std::cin >> c)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error: NaN, try again: ";
	}
	
	//attempt to drop and display whether it was successful
	if(dropPiece(c - 1))
		std::cout << "Piece dropped successfully!" << std::endl;
	else
		std::cout << "That's not on the board!" << std::endl;
}

//return if position represented by p is within bounds
bool withinBounds(const BoardPos& p) {
	return 0 <= p.r && p.r < ROW && 0 <= p.c && p.c < COL;
}

//return which side is the winner
//returns VACANT if there is no winner
int winner() {
	typedef BoardPos b;
	
	//iterate through each slot and...
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			b p(i, j), q;
			
			//skip if slot is vacant
			if(isVacant(*p))
				continue;
			//check along main diagonal
			if(withinBounds(q = (p + b(1, 1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, 2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, 3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			//check downwards
			if(withinBounds(q = (p + b(1, 0))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, 0))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, 0))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			//check along anti-diagonal
			if(withinBounds(q = (p + b(1, -1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(2, -2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(3, -3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			//check rightwards
			if(withinBounds(q = (p + b(0, 1))) && isMatching(*p, *q)) {
				if(withinBounds(q = (p + b(0, 2))) && isMatching(*p, *q)) {
					if(withinBounds(q = (p + b(0, 3))) && isMatching(*p, *q)) {
						return *p;
					}
				}
			}
			//upwards and leftwards check not needed
		}
	}
	//no slots and directions produce winner
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
