#ifndef PIECE_H_
#define PIECE_H_

#include "position.h"

class Piece {
protected:
	Position pos;

public:
	virtual Piece() = 0;

	virtual Piece(const Position&) = 0;

	virtual ~Piece();

	virtual Position getPosition() const {
		return pos;
	}
};

enum Side {
	WHITE, BLACK, NEITHER
};

class PlayablePiece: public Piece {
protected:
	Side side;

public:
	virtual PlayablePiece() = 0;

	virtual PlayablePiece(const Position&) = 0;

	virtual ~PlayablePiece();

	virtual Position move(const Position&);

	virtual Side getSide() const {
		return side;
	}

	//the cake is an abstract falsehood!
	//virtual short cake() = 0;
};

#endif
