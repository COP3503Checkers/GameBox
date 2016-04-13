#ifndef CHECKERS_H_
#define CHECKERS_H_

#define VACANT 0
#define RED 1
#define BLACK -1
#define RKING 2
#define BKING -2

#define ROW 8
#define COL 8

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

#endif
