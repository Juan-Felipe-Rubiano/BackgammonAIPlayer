// Backgammon Final Project
// Class: Obj Orient Pgm w/C++
// Programmed by: Kyle Opland
// Date: 6/9/14
// driver.cpp file
#include "dice.h"
#include "gameBoard.h"
#include <iostream>
#include <string>

bool whiteTurn(gameBoard &, std::string, std::string);
// Purpose:
//	Runs through the steps for the white player's turn.
// Precondition:
//	Turn variable must be an odd number.
// Postcondition:
//	Turn variable is incremented causing the blackTurn() function to be
// called, unless the player won on their turn.
bool blackTurn(gameBoard &, std::string, std::string);
// Purpose:
//	Runs through the steps for the black player's turn.
// Precondition:
//	Turn variable must be an odd number.
// Postcondition:
//	Turn variable is incremented causing the whiteTurn() function to be
// called, unless the player won on their turn.

int main() {
  int turn = 3;
  std::string p1, p2;
  gameBoard backgammon;
  bool whiteWin = false;
  bool blackWin = false;
  dice dice1, dice2;

  std::cout << "Welcome to Backgammon!" << std::endl;
  std::cout
      << "The object of the game is to try and get all of your pieces to the "
         "home location."
      << std::endl;

  std::cout << "Enter name of player one: ";
  getline(std::cin, p1);
  std::cout << std::endl;

  std::cout << "Enter name of player two: ";
  getline(std::cin, p2);
  std::cout << std::endl;

  std::cout << "To determine who goes first, roll the dice for the players.";
  std::cout << std::endl;
  system("pause");

  do {
    dice1.rollDice();
    dice2.rollDice();
    std::cout << p1 << " rolled a ";
    dice1.printDice();
    std::cout << std::endl;
    std::cout << p2 << " rolled a ";
    dice2.printDice();
    std::cout << std::endl;

    if (dice1.getDice() == dice2.getDice()) {
      std::cout << "Roll is a tie, rolling again." << std::endl;
    }
  } while (dice1.getDice() == dice2.getDice());

  if (dice1.getDice() > dice2.getDice()) {
    std::cout << p1 << " goes first.";
  }

  else if (dice1.getDice() < dice2.getDice()) {
    std::cout << p2 << " goes first.";
    turn++;
  }

  std::cout << std::endl << std::endl;

  system("pause");

  backgammon.printBoard();
  std::cout << std::endl << std::endl;

  while (!whiteWin && !blackWin) {

    if (turn % 2 == 0) {
      blackWin = blackTurn(backgammon, p1, p2);
      turn++;
    } else {
      whiteWin = whiteTurn(backgammon, p1, p2);
      turn++;
    }
    whiteWin = backgammon.checkWhiteWin();
    blackWin = backgammon.checkBlackWin();
  }

  backgammon.printBoard();

  if (whiteWin) {
    std::cout << std::endl
              << std::endl
              << p1
              << ", the white player, has won the game!!! Congratulations!!!"
              << std::endl;
    system("pause");
    return 0;
  }

  if (blackWin) {
    std::cout << std::endl
              << std::endl
              << p2
              << ", the black player, has won the game!!! Congratulations!!!"
              << std::endl;
    system("pause");
    return 0;
  }
}

bool whiteTurn(gameBoard &backgammon, std::string p1, std::string p2) {
  int move = 0;

  bool check = false;
  bool stuck = false;
  bool penalty = false;
  int errorCheck;

  int rowChoice;
  int moved;
  dice dice1;

  std::cout << p1 << ", you are White. Rolling dice for your turn." << std::endl
            << std::endl;

  move = dice1.rollDice();
  std::cout << std::endl << "You rolled a " << move << "\n";

  penalty = backgammon.checkPenaltyWhite();

  while (penalty) {
    rowChoice = 25;
    stuck = backgammon.checkStuckWhite(move);
    if (stuck) {
      std::cout
          << "Your piece is stuck on the bar. You have no possible moves, "
             "your turn is over."
          << std::endl;
      return false;
    }

    moved = rowChoice - move;
    errorCheck = backgammon.movePieceWhitePenalty(rowChoice, moved);
    if (errorCheck == 0) {
      move = 0;
      penalty = backgammon.checkPenaltyWhite();
      backgammon.printBoard();
    } else {
      std::cout << "Invalid move, try again.\n";
      return false;
    }
  }

  if (move != 0) {
    do {
      check = false;
      do {
        try {
          std::cout << "Now enter the row you want to move from: ";
          std::cin >> rowChoice; // add error handling

          if (!std::cin || rowChoice < 1 || rowChoice > 24) {
            throw 1;
          }
          std::cout << std::endl << std::endl;
          check = true;
        } catch (int) {
          std::cout << std::endl
                    << std::endl
                    << "ERROR: Input invalid. Please enter a number between 1 "
                       "and 24.";
          std::cin.clear();
          std::cin.ignore(100, '\n');
          std::cout << std::endl;
        }
      } while (check == false);

      moved = rowChoice - move;
      errorCheck = backgammon.movePieceWhite(rowChoice, moved);
      if (errorCheck == 0) {
        move = 0;

        if (backgammon.checkWhiteWin()) {
          return true;
        }
      } else {
        std::cout << "Invalid move, try again\n";
      }

      backgammon.printBoard();
    } while (move != 0);
  }

  return false;
}

bool blackTurn(gameBoard &backgammon, std::string p1, std::string p2) {
  int move1 = 0;
  bool check = false;
  bool stuck = false;
  bool penalty = false;
  int errorCheck;

  int rowChoice;
  int moved;
  dice dice1;
  int choice = 1;

  std::cout << p2 << ", you are Black. Rolling dice for your turn." << std::endl
            << std::endl;
  std::cout << "You rolled a ";
  move1 = dice1.rollDice();
  std::cout << move1 << std::endl << std::endl;

  penalty = backgammon.checkPenaltyBlack();
  while (penalty) {
    rowChoice = 0;
    stuck = backgammon.checkStuckBlack(move1);
    if (stuck) {
      std::cout << "Your piece is stuck on the bar. You have no possible "
                   "moves, your turn is over."
                << std::endl;
      return false;
    }

    moved = rowChoice + move1;
    errorCheck = backgammon.movePieceBlackPenalty(rowChoice, moved);
    if (errorCheck == 0) {
      move1 = 0;
      penalty = backgammon.checkPenaltyBlack();
      backgammon.printBoard();
    }
  }

  do {
    std::cout << "Your remaining dice roll is: " << move1 << std::endl;

    check = false;
    do {
      try {
        std::cout << "Now enter the row you want to move from: ";
        std::cin >> rowChoice;

        if (!std::cin) {
          throw 4;
        }
        std::cout << std::endl << std::endl;
        check = true;
      } catch (int) {
        std::cout << std::endl
                  << std::endl
                  << "ERROR: Input invalid. Please enter a number between 1 "
                     "and 24.";
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << std::endl;
      }
    } while (check == false);

    moved = rowChoice + move1;
    errorCheck = backgammon.movePieceBlack(rowChoice, moved);
    if (errorCheck == 0) {
      move1 = 0;

      if (backgammon.checkBlackWin()) {
        return true;
      }
    }

    backgammon.printBoard();
  } while (move1 != 0);

  return false;
}
