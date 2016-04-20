#ifndef CHECKERS_H_
#define CHECKERS_H_

namespace checker {

//constants and stuff
//hooray constants
//const double PI = 3.2f;
//>.>
const int VACANT = 0;
const int RED = 1;
const int BLACK = -1;
const int RKING = 2;
const int BKING = -2;

//board dimensions
const int ROW = 8;
const int COL = 8;

//helper functions, inline these if necessary
bool isRed(int x) {
	return x == RKING || x == RED;
}
bool isBlack(int x) {
	return x == BKING || x == BLACK;
}
bool isKing(int x) {
	return x == RKING || x == BKING;
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
//make a piece the king of their respective color
int toKing(int x) {
	return isRed(x) ? RKING : (isBlack(x) ? BKING : VACANT);
}

} //namespace checker

#include <utility>
#include <cstddef>

namespace checker {

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

//return if piece can move from i to f if the piece is not a king
bool isForward(const BoardPos& i, const BoardPos& f) {
	if(isKing(*i)) return true;
	if(isRed(*i)) return f.r > i.r;
	else if(isBlack(*i)) return f.r < i.r;
	return false;
}
//return whether piece should be kinged
bool isAtEnd(const BoardPos& p) {
	if(isVacant(*p)) return false;
	if(isRed(*p)) return p.r == 0;
	return p.r == ROW - 1;
}

} //namespace checker

#include <exception>
#include <stdexcept>

namespace checker {

//thrown to indicate bad input
class input_error: public std::runtime_error {
public:
	explicit input_error(const std::string& msg)
			: std::runtime_error(msg) {
	}
};

} //namespace checker

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <cctype>
#include <vector>

//using namespace std;

//board position
//    c0 c1 c2 ...
// r0
// r1
// r2
// ...

namespace checker {

std::string player1 = "Player 1";
std::string player2 = "Player 2";

BoardPos getPos(const char*);
ifpos_pair_type getPosPair();

//the board with int values being manipulated as the game progresses
int **board = NULL;
//the default board
const int INITBOARD[ROW][COL] = { { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, RED, VACANT, RED, VACANT, RED, VACANT, RED }, { RED, VACANT, RED, VACANT, RED, VACANT, RED, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK }, { BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT }, { VACANT, BLACK, VACANT, BLACK, VACANT, BLACK, VACANT, BLACK } };

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
    BoardPos::board = checker::board;
}

//game win at numRedsAlive == 0 && numBlacksAlive == 0
int numRedsAlive = 24;
int numBlacksAlive = 24; //#BlackLivesMatter
//flag for whether it's black's turn
//BlackTurn = !BlackTurn to flip turns
bool blackTurn = false;

//this shouldnt really be necessary, blackTurn is already boolean, lol
int getTurn() {
    return blackTurn ? BLACK : RED;
}

//return char representation of how pieces should be displayed
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
//output board representation to cout
//less extraneous crap so it fits into debugging window
void printBoard() {
    for(int l = 0; l < ROW; ++l) {
        std::cout << std::setw(1) << l + 1;
        for(int m = 0; m < COL; ++m)
            std::cout << std::setw(2) << pieceRep(*BoardPos(l, m));
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl;
    std::cout << "# Reds Taken = " << 24 - numRedsAlive << std::endl;
    std::cout << "# Blacks Taken = " << 24 - numBlacksAlive << std::endl;
    std::cout << (blackTurn ? player2 : player1) << "'s turn!" << std::endl;
}
#else
//output board representation to cout
//"pretty" version
void printBoard() {
    std::cout << " x---x---x---x---x---x---x---x---x\n";
    for(int l = 0; l < ROW; ++l) {
        std::cout << std::setw(1) << l + 1;
        for(int m = 0; m < COL; ++m)
            std::cout << std::setw(4) << pieceRep(*BoardPos(l, m));
        std::cout << "\n x---x---x---x---x---x---x---x---x\n";
    }
    std::cout << "    A   B   C   D   E   F   G   H\n";
}
#endif

//return column number
int columnFinder(const std::string& p) {
    int c = int(p[0]);
    if('A' <= c && c <= 'H') return c - 'A';
    if('a' <= c && c <= 'h') return c - 'a';
    return -1;
}

//check if move from i to f is valid
//if not valid, throws input_error with respective error message
void moveCheck(const BoardPos& i, const BoardPos& f) {
    BoardPos d(f - i);
    d.r = std::abs(d.r);
    d.c = std::abs(d.c);

    //time to play baseball
    //throw errors if anything is wrong
    if(isVacant(*i)) throw input_error("can only move a red or black piece");
    if(!isMatching(*i, getTurn())) throw input_error("can only move your own piece");
    if(!isVacant(*f)) throw input_error("can only move to an empty space");
    if(d.r != d.c) throw input_error("can only move diagonal");
    if(d.r > 2) throw input_error("can only move as far as 2 diagonal spaces");
    if(d.r == 0) throw input_error("cannot stay at the same spot");
    if(d.r == 2 && !isOpposite(*i, *(i / f))) throw input_error("can only jump over opposite piece");
    if(!isForward(i, f)) throw input_error("can only move forward");
}

//get all valid jumps form p
std::vector<BoardPos> getValidJumps(const BoardPos& p) {
    const BoardPos main(2, 2), anti(2, -2);
    BoardPos f[] = { p + main, p - anti, p - main, p + anti };
    std::vector<BoardPos> ret;
    for(unsigned i = 0; i < 4; ++i) {
        try {
            moveCheck(p, i[f]);
            ret.push_back(f[i]);
        } catch(const std::exception& e) {
        }
    }
    return ret;
}

//jump from position p
//used only when a move has already been made by the turn
//code's a bit jumbled here
//forgive me plz :c
BoardPos jumpFrom(const BoardPos& p) {
    auto valid = getValidJumps(p); //vector of valid jumps from p
   
    //no valid jumps
    if(valid.size() == 0) {
        blackTurn = !blackTurn;
        return p;
    }
    
    //ask if player wants to continue to jump
    //who wouldnt lol
    {
        std::cout << "Continue jumping? (Y/N)\n";
        char c = '\0';
        while(c != 'y') {
            std::string s;
            std::cin >> s;
            if((c = std::tolower(s[0])) == 'n') {
                blackTurn = !blackTurn;
                return p;
            }
        }
    }
    
    //get where the player wants to jump to then check if it's allowed
    BoardPos jump = valid[0];
    if(valid.size() != 1) {
        jump = BoardPos(-1, -1);
        bool move = false;
        while(!move)
            try { //TODO: implement lambda for try/catch
            	//this should take care if whether it is a correct jump
            	//vector::contains(jump) may or may not be better
                moveCheck(p, jump);
                jump = getPos("Where would you like to jump to?\n");
            } catch(const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
    }
    
    //jump is allowed
    *(p / jump) = VACANT;
    std::swap(*p, *jump);
    if(isAtEnd(p)) *p = toKing(*p);
    return jump;
}

//move a piece from i to f
bool movePiece(const BoardPos& i, const BoardPos& f) {
    //validity check
    moveCheck(i, f);
    
    //not a jump
    if(std::abs((f - i).r) == 1) {
        std::swap(*i, *f);
        blackTurn = !blackTurn;
        if(isAtEnd(f)) *f = toKing(*f);
        return false;
    }
    
    //is a jump
    if(isRed(*(i / f))) --numRedsAlive;
    else --numBlacksAlive;
    *(i / f) = VACANT;
    std::swap(*i, *f);
    if(isAtEnd(f)) *f = toKing(*f);
    return true;
}

//helper function
inline bool movePiece(const ifpos_pair_type& p) {
    return movePiece(p.first, p.second);
}

//get a position from the user, with the prompt msg displayed beforehand with no newlines
BoardPos getPos(const char* msg) {
    std::cout << msg;
    std::string s;
    std::cin >> s;
    
    //basic checks on input before passing to moveCheck
    if(s.length() != 2) throw input_error("input length is not 2");
    int r = int(s[1]) - int('1'), c = columnFinder(s);
    if(c == -1) throw input_error("invalid column");
    if(!(0 <= r && r < ROW)) throw input_error("invalid row");
    return BoardPos(r, c);
}

//Ask the user what pieces they want to move
ifpos_pair_type getPosPair() {
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

void setPlayer1Name(std::string name){
    player1 = name;
}

std::string getPlayer1Name(){
    return player1;
}

void setPlayer2Name(std::string name){
    player2 = name;
}

std::string getPlayer2Name(){
    return player2;
}

} //namespace checker

/*
example playthrough:
int main() {
	checker::initBoard();
	while(checker::numRedsAlive && checker::numBlacksAlive)
	checker::play();
	std::cout << "Winner: " << (!checker::numBlacksAlive ? "Black" : "Red");
}
 */

#endif
