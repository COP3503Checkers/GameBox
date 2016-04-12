//just doing this so board is easier to see for debugging
//TODO: remove at shipping
#ifndef NDEBUG
#define PDEBUG 1
#endif

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>

//using namespace std;

//define thsese as global consts for type safety?
//at least add postfixes
#define VACANT 0
#define RED 1
#define BLACK -1
#define RKING 2
#define BKING -2

#define ROW 8
#define COL 8

//this seems familiar...
inline bool isRed(int x) {
	return x == RKING || x == RED;
}
inline bool isBlack(int x) {
	return x == BKING || x == BLACK;
}
inline bool isKing(int x) {
	return x == RKING || x == BKING;
}
inline bool isVacant(int x) {
	return x == VACANT;
}

//board position
//    c0 c1 c2 ...
// r0
// r1
// r2
// ...

//static outside of a class... this compiles?! O.o
int board[ROW][COL] = { { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, RED, VACANT, RED, VACANT, RED, VACANT, RED }, { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK }, { BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK } };

int numRedsDead = 0;
int numBlacksDead = 0;

bool blackTurn = false;

//get whose turn it is as defined by #def
int getTurn() {
	return blackTurn ? BLACK : RED;
}

//void printBoard(int board[][COL]);
//char printPieces(int i);

inline char printPieces(int i) {
	switch(i) {
//	case 0:
//	this just means space is vacant? no need for return 'o'?
//		return 'o';
//	case VACANT:
//		return ' ';
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

void printBoard(int board[][COL]) {
#if !PDEBUG
	std::cout << " x---x---x---x---x---x---x---x\n";
#endif
	for(int l = 0; l < ROW; ++l) {
		std::cout << std::setw(1) << l + 1;
		for(int m = 0; m < COL; ++m)
			std::cout << std::setw(4) << printPieces(*(l[board] + m)); //hahaha >:D
		std::cout << "\n";
#if !PDEBUG
		cout << " x---x---x---x---x---x---x---x\n";
#endif
	}

	std::cout << "    A   B   C   D   E   F   G   H\n";
#if PDEBUG
	std::cout << std::endl;
#endif
}

inline int columnFinder(const std::string& p) {
	char c = p[0];
	if('A' <= c && c <= 'H') return c - 'A';
	return -1;
}

void getDestinations();

//TODO: rewrite to avoid recursion
void inputErrorsHandle(const char* errMsg) {
	std::cin.clear();
	std::cin.ignore();
	std::cout << errMsg;
	getDestinations();
}

//(r,c) to (rf,cf)
void movePiece(int r, int c, int rf, int cf) {
	//Check if the user is trying to jump over a piece
	if(std::abs(r - rf) == 2 && std::abs(c - cf) == 2) {
		int& midpoint = board[(r + rf) / 2][(c + cf) / 2];
		if(isRed(midpoint)) { //if piece at midpoint (r,c) (rf,cf) = 2
			midpoint = VACANT;
			++numRedsDead;
		} else if(isBlack(midpoint)) { //if piece at midpoint (r,c) (rf,cf) = 3
			midpoint = VACANT;
			++numBlacksDead;
		}
	} else blackTurn = !blackTurn;
	std::swap(board[r][c], board[rf][cf]);
}

//check and move positions p to pf
void inputErrors(const std::string& p, const std::string& pf) {
	int r = p.at(1) - '1';
	int rf = pf.at(1) - '1';
	int c = columnFinder(p);
	int cf = columnFinder(pf);
	int difr = std::abs(r - rf);
	int difc = std::abs(c - cf);

	while(isVacant(board[r][c]))
		inputErrorsHandle("Error, can only move a red or black piece, Try Again \n");
	while(!isVacant(board[rf][cf]))
		inputErrorsHandle("Error, can only move to an 'o' space, Try Again \n");
	while(difc != difr)
		inputErrorsHandle("Error, can only move diagonal, Try Again \n");
	while(difr > 2)
		inputErrorsHandle("Error, can only move as far as 2 diagonal spaces, Try Again \n");
	while(difr == 0)
		inputErrorsHandle("Error, must actually move. Try Again \n");
	while(difr == 2 && !isVacant(board[(r + rf) / 2][(c + cf) / 2]))
		inputErrorsHandle("Error, can only jump over a piece, Try Again \n");

	movePiece(r, c, rf, cf);
}

inline void getDestinations() {
	//Ask the user what piece they want to move
	std::string pieceStart, pieceFinish;
	std::cout << "What piece do you want to move\n";
	std::cin >> pieceStart;
	std::cout << "Where do want to move it to\n";
	std::cin >> pieceFinish;
	inputErrors(pieceStart, pieceFinish);
}

int main() {
	printBoard(board);

//	getDestinations();
	movePiece(2, 6, 3, 5);

	printBoard(board);
}
