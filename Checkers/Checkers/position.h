#ifndef POSITION_H_
#define POSITION_H_

struct Position {
	int xpos;
	int ypos;

	Position()
			: xpos(0), ypos(0) {
	}

	Position(int xpos, int ypos)
			: xpos(xpos), ypos(ypos) {
	}

	Position(const Position& p)
			: xpos(p.xpos), ypos(p.ypos) {
	}

	Position& operator=(const Position& p) {
		xpos = p.xpos;
		ypos = p.ypos;
		return *this;
	}

	//ADDED: THESE

	//operator+ and operator+= does not check for bounds
	//caution ye who uses these!
	Position operator+(const Position& p) {
		return Position(xpos + p.xpos, ypos + p.ypos);
	}

	//operator+ and operator+= does not check for bounds
	//caution ye who uses these!
	Position& operator+=(const Position& p) {
		xpos += p.xpos;
		ypos += p.ypos;
		return *this;
	}
};

#endif
