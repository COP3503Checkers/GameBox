#ifndef CHECKERS_H_
#define CHECKERS_H_

const int VACANT = 0;
const int RED = 1;
const int BLACK = -1;
const int RKING = 2;
const int BKING = -2;


const int ROW = 8;
const int COL = 8;

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
bool isMatching(int a, int b) {
	return isRed(a) ? isRed(b) : (isBlack(a) ? isBlack(b) : false);
}
bool isOpposite(int a, int b) {
	return isRed(a) ? isBlack(b) : (isBlack(a) ? isRed(b) : false);
}
int toKing(int x) {
	return isRed(x) ? RKING : (isBlack(x) ? BKING : VACANT);
}

#endif
