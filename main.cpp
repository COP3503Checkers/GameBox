#ifndef NDEBUG
#define PDEBUG 1
#endif

#include <iostream>
#include <string>
#include "checkers.h"
#include "connectfour.h"

int main() {
	int checkersChoice = 0;
	int connectChoice = 0;
	int gameChoice = 0;

	do {
		std::cout << "Welcome to our Game Box!" << std::endl;
		std::cout << "1. Play Checkers" << std::endl;
		std::cout << "2. Play Connect 4" << std::endl;
		std::cout << "3. Exit" << std::endl;

		std::cin >> gameChoice;

		if(gameChoice == 1) do {

			std::cout << "Welcome to Checkers!" << std::endl;
			std::cout << "1. Choose names of players" << std::endl;
			std::cout << "2. How To Play" << std::endl;
			std::cout << "3. Play" << std::endl;
			std::cout << "4. Exit" << std::endl;

			std::cin >> checkersChoice;

			while(checkersChoice == 1) {
				std::string name1;
				std::string name2;
				int playerChoice;
				std::cout << checker::player1;
				std::cout << " is Red. ";
				std::cout << checker::player2;
				std::cout << " is Black. Which player name would you like to change? 1 or 2? Choose 0 to exit." << std::endl;
				std::cin >> playerChoice;
				//FIXME: cin to int is dangerous, use std::string instead
			if(playerChoice == 1) {
				std::cout << "What would you like to change Player 1's name to?" << std::endl;
				std::cin >> name1;
				checker::setPlayer1Name(name1);
			}
			if(playerChoice == 2) {
				std::cout << "What would you like to change Player 2's name to?" << std::endl;
				std::cin >> name2;
				checker::setPlayer2Name(name2);
			}
			if(playerChoice == 0) break;
			if(playerChoice != 1 && playerChoice != 2 && playerChoice != 0) std::cout << "Invalid Choice. Please choose 1 or 2." << std::endl << std::endl;
		}
		if(checkersChoice == 2) {
			std::cout << "This is a 2 player game of Checkers. Once the game begins, ";
			std::cout << checker::player1;
			std::cout << " has the red pieces and ";
			std::cout << checker::player2;
			std::cout << " has the black pieces. In order to move your pieces, simply type what row and column the piece is in and what row and column to move the piece to. Be sure to type the column letter first, then the row number. For example: A1 or D6. You can only move pieces diagonally forward, until you become a King piece and can move backwards. You become a King piece by getting to your opponent's side of the board. Have fun and good luck!" << std::endl << std::endl;
		}
		if(checkersChoice == 3) {
			checker::initBoard();
			while(checker::numRedsAlive && checker::numBlacksAlive)
				checker::play();
			std::cout << "Winner: " << (!checker::numBlacksAlive ? "Black" : "Red");
		}
		if(checkersChoice == 4) break;

	} while(checkersChoice == 1 || checkersChoice == 2 || checkersChoice == 3);

		if(gameChoice == 2) do {

			std::cout << "Welcome to Connect Four!";
			std::cout << std::endl;
			std::cout << "1. Play";
			std::cout << std::endl;
			std::cout << "2. Exit";
			std::cout << std::endl;

			std::cin >> connectChoice;

			if(connectChoice == 1) {
				con4::initBoard();
				while(con4::isVacant(con4::winner()))
					con4::play();
				con4::printBoard();
				std::cout << "Winner: " << (con4::isBlackTurn ? "Red" : "Black") << std::endl;
			}
			if(connectChoice == 2) break;

		} while(connectChoice == 1);

		if(gameChoice == 3) break;
	} while(gameChoice == 1 || gameChoice == 2);
}
