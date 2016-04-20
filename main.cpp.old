#ifndef NDEBUG
#define PDEBUG 1
#endif

#include <iostream>
#include <string>
#include "checkers.h"
#include "connectfour.h"

#include <QApplication>
#include "galaga.h"

Galaga * galaga;

int main(int argc, char *argv[]) {
	//selected option under checkers menu
	int checkersChoice = 0;
	//selected option under connect four menu
	int connectChoice = 0;
	//selected option under main menu
	int gameChoice = 0;

	do {
		//main menu
		std::cout << "Welcome to our Game Box!" << std::endl;
		std::cout << "1. Play Checkers" << std::endl;
		std::cout << "2. Play Connect 4" << std::endl;
		std::cout << "3. Play Galaga" << std::endl;
		std::cout << "4. Exit" << std::endl;

		std::cin >> gameChoice;

		if(gameChoice == 1) do {
			//checkers menu
			std::cout << "Welcome to Checkers!" << std::endl;
			std::cout << "1. Choose names of players" << std::endl;
			std::cout << "2. How To Play" << std::endl;
			std::cout << "3. Play" << std::endl;
			std::cout << "4. Exit" << std::endl;

			std::cin >> checkersChoice;

			while(checkersChoice == 1) {
				//choose player name
				std::string name1;
				std::string name2;
				int playerChoice;
				std::cout << checker::player1;
				std::cout << " is Red. ";
				std::cout << checker::player2;
				std::cout << " is Black. Which player name would you like to change? 1 or 2? Choose 0 to exit." << std::endl;
				std::cin >> playerChoice;
				//cin to int is dangerous, use std::string instead
				//TODO: implement function to get int safely
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
			if(playerChoice == 0)
				break;
			if(playerChoice != 1 && playerChoice != 2 && playerChoice != 0) std::cout << "Invalid Choice. Please choose 1 or 2." << std::endl << std::endl;
		}
		if(checkersChoice == 2) {
			//how to play checkers
			std::cout << "This is a 2 player game of Checkers. Once the game begins, ";
			std::cout << checker::player1;
			std::cout << " has the red pieces and ";
			std::cout << checker::player2;
			std::cout << " has the black pieces. In order to move your pieces, simply type what row and column the piece is in and what row and column to move the piece to. Be sure to type the column letter first, then the row number. For example: A1 or D6. You can only move pieces diagonally forward, until you become a King piece and can move backwards. You become a King piece by getting to your opponent's side of the board. Have fun and good luck!" << std::endl << std::endl;
		}
		if(checkersChoice == 3) {
			//play checkers
			checker::initBoard();
			//while no winner play through one turn
			//TODO: implement bool checker::winner();
			while(checker::numRedsAlive && checker::numBlacksAlive)
				checker::play();
			std::cout << "Winner: " << (!checker::numBlacksAlive ? "Black" : "Red");
		}
		//return to main menu
		if(checkersChoice == 4)
			break;

	} while(checkersChoice == 1 || checkersChoice == 2 || checkersChoice == 3);

		if(gameChoice == 2) do {
			//connect4 menu
			std::cout << "Welcome to Connect Four!";
			std::cout << std::endl;
			std::cout << "1. Play";
			std::cout << std::endl;
			std::cout << "2. Exit";
			std::cout << std::endl;

			std::cin >> connectChoice;

			if(connectChoice == 1) {
				//play connect4
				con4::initBoard();
				while(con4::isVacant(con4::winner()))
					con4::play();
				con4::printBoard();
				std::cout << "Winner: " << (con4::isBlackTurn ? "Red" : "Black") << std::endl;
			}
			//exit
			if(connectChoice == 2)
				break;

		} while(connectChoice == 1);
		
		if(gameChoice == 3) {	
			//galaga
			QApplication a(argc, argv);
			galaga = new Galaga();
			galaga->show();
			a.exec()
		}
		
		//exit main menu
		if(gameChoice == 4)
			break;
	} while(gameChoice == 1 || gameChoice == 2 || gameChoice == 3);
}
