using namespace std;
#include <cmath>
#include <iostream>

#define VACANT 1
#define RED 2
#define BLACK 3
#define RKING 4
#define BKING 5

#define ROW 8
#define COL 8

#define ISRED(x) (x == RKING || x == RED)
#define ISBLACK(x) (x== BKING || x == BLACK)
#define ISVACANT(x) (x ==1)

int board[][];
int i;

void printBoard(int board[][COL]);
char printPieces(int i);

void printBoard (int board[][COL])
{
    int l;
    int m;
    
    cout << " x---x---x---x---x---x---x---x\n";
    
    for (l=0; l<ROW; ++l)
    {
        cout << "%board I" << (l+1));
        for (m=0; m<COL; ++m)
        {
            cout << " %x I" << printPieces(board[l][m]);
        }
        cout << "\n";
        cout << " x---x---x---x---x---x---x---x\n";
    }
    
    cout << "    A   B   C   D   E   F   G   H\n";
}

char printPieces(int i)
{
	switch(i)
	{
	case 0:
		return '#';
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
	int board[ROW][COL] = 
	{
	{2,1,2,1,2,1,2,1},
	{1,2,1,2,1,2,1,2},
	{2,1,2,1,2,1,2,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,3,1,3,1,3,1,3},
	{3,1,3,1,3,1,3,1},
	{1,3,1,3,1,3,1,3},
	}
	return 0;
	
 	while(true) {
 		printBoard(board);
 	}
}
