#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

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

static int board[ROW][COL]=
{
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {1,3,1,3,1,3,1,3},
    {3,1,3,1,3,1,3,1},
    {1,3,1,3,1,3,1,3},
};

static int numReds = 0; static int numBlacks = 0;

void printBoard(int board[][COL]);
char printPieces(int i);

void printBoard (int board[][COL])
{
    int l;
    int m;
    
    cout << " x---x---x---x---x---x---x---x\n";
    
    for (l=0; l<ROW; ++l)
    {
        cout << setw(1) << l+1;
        for (m=0; m<COL; ++m)
        {
            if ((l%2)==0) {
                cout << setw(3) << printPieces(board[l][m]) << " ";
            }
            else {
                for (m=0; m<COL-1; ++m) {
                    cout << setw(3) << printPieces(board[l][m]) << " ";
                }
            }
        }
        cout << "\n";
        cout << " x---x---x---x---x---x---x---x\n";
    }
    
    cout << "   A   B   C   D   E   F   G\n";
}

char printPieces(int i)
{
    switch(i)
    {
        case 0:
            return 'o';
        case 1:
            return ' ';
        case 2:
            return 'R';
        case 3:
            return 'B';
    }
    return ('X');
}

int columnFinder(string p) {
    switch(p.at(0)) {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
    }
    return -1;
}

void getDestinations();

void movePiece(int r, int c, int rf, int cf) {
    
    //Check if the user is trying to jump over a piece
    if ( (r - rf) == -2 || (r - rf) == 2) {
        if (board[(r+rf)/2][(c+cf)/2] == 2) {
            board[(r+rf)/2][(c+cf)/2] = 0;
            numReds++;
        }
        else if (board[(r+rf)/2][(c+cf)/2] == 3) {
            board[(r+rf)/2][(c+cf)/2] = 0;
            numBlacks++;
        }
        else {
            std::cin.clear();
            std::cin.ignore();
            
            std::cout << "Error, can only jump over a piece, Try Again \n";
            getDestinations();
        }
    }
    
    int temp = board[r][c];
    board[r][c] = board[rf][cf];
    board[rf][cf] = temp;
    
}

void inputErrors (string p, string pf)  {
    int r = p.at(1) - '1';
    int rf = pf.at(1) - '1';
    int c = columnFinder(p);
    int cf = columnFinder(pf);
    int difr = abs(r - rf);
    int difc = abs(c - cf);
    
    while (board[r][c] == 1 || board[r][c] == 0) {
        std::cin.clear();
        std::cin.ignore();
        
        std::cout << "Error, can only move a red or black piece, Try Again \n";
        getDestinations();
    }
    
    while (difc != difr) {
        std::cin.clear();
        std::cin.ignore();
        
        std::cout << "Error, can only move diagonal, Try Again \n";
        getDestinations();
    }
    
    while (board[rf][cf] != 0) {
        std::cin.clear();
        std::cin.ignore();
        
        std::cout << "Error, can only move to an 'o' space, Try Again \n";
        getDestinations();
    }
    
    while ( difr > 2 || difc > 2) {
        std::cin.clear();
        std::cin.ignore();
        
        std::cout << "Error, can only move as far as 2 diagonal spaces, Try Again \n";
        getDestinations();
    }
    
    movePiece(r, c, rf, cf);
}

void getDestinations () {
    
    //Ask the user what piece they want to move
    string pieceStart; string pieceFinish;
    cout << "What piece do you want to move\n";
    cin >> pieceStart;
    
    cout << "Where do want to move it to\n";
    cin >> pieceFinish;
    
    inputErrors(pieceStart, pieceFinish);
}

int main() {
    //TODO
    
    for(int i=0; i<1; i++) {
        printBoard(board);
    }
    
    getDestinations();
    
    
    for(int i=0; i<1; i++) {
        printBoard(board);
    }
    
    return 0;
    
}
