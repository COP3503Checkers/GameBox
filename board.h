#ifndef BOARD_H_
#define BOARD_H_

#include "piece.h"
#include <iostream>

class Board {
protected:
    const int xSize;
    const int ySize;
    
    Piece * * const * const board;
    
public:
    virtual Board() = 0;
    
    virtual Board(const int, const int) = 0;
    
    virtual ~Board();
    
    virtual Piece* pieceAt(int, int) const;
    
    virtual Piece* pieceAt(const Position&) const;
    
    virtual Piece* operator()(int, int) const;
    
    virtual Piece* movePiece(const Position&, const Position&);
    
    virtual Side getWinner() const;
};

virtual friend std::ostream& operator<<(std::ostream&, const Board&);

#endif
