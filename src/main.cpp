using namespace std;
#include <cmath>
#include <iostream>

#define VACANT 1
#define RED 2
#define BLACK 3
#define RKING 4
#define BKING 5

#define ISRED(x) (x == RKING || x == RED)
#define ISBLACK(x) (x== BKING || x == BLACK)
#define ISVACANT(x) (x ==1)

#define ROW 10
#define COL 10

char pieceprints(int i)
{
	switch(i)
	{
	case 0:
		return ' ';
	case 1: 
		return ' ';
	case 2:
		return 'R';
	case 3:
		return 'B';
	}
	return ('X');
}


int main(int argc, char *argv[]) {
	//TODO
	#define
	return 0;
}
