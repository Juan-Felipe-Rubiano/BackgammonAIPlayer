// Backgammon Final Project
// Class: Obj Orient Pgm w/C++
// Programmed by: Kyle Opland
// Date: 6/9/14
// driver.cpp file
#include "dice.h"
#include "gameBoard.h"
#include <iostream>
#include <string>

using std::cout;

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
  int move1 = 0;
  int move2 = 0;
  int move3 = 0;
  int move4 = 0;

  bool check = false;
  bool stuck = false;
  bool penalty = false;
  int errorCheck;

  int rowChoice;
  int moved;
  dice dice1, dice2;
  int choice;

  std::cout << p1 << ", you are White. Rolling dice for your turn." << std::endl
            << std::endl;
  std::cout << std::endl << "You rolled a 1.) ";
  move1 = dice1.rollDice();
  move2 = dice2.rollDice();

  std::cout << move1 << " and a 2.) " << std::endl
            << move2 << std::endl
            << std::endl;

  if (move1 == move2) {

    std::cout << "You rolled doubles! You get to move twice for each die."
              << std::endl
              << std::endl;
    move3 = move1;
    move4 = move2;
  }

  penalty = backgammon.checkPenaltyWhite();

  while (penalty) {
    rowChoice = 25;
    stuck = backgammon.checkStuckWhite(move1, move2);
    if (stuck) {
      std::cout
          << "Your piece is stuck on the bar. You have no possible moves, "
             "your turn is over."
          << std::endl;
      return false;
    }
    if (move1 != 0 && move2 == 0) {
      std::cout << "Your remaining dice roll is: " << move1 << std::endl;
      choice = 1;
    } else if (move2 != 0 && move1 == 0) {
      std::cout << "Your remaining dice roll is: " << move2 << std::endl;
      choice = 2;
    } else {
      do {
        try {

          std::cout << "Please enter the die you would like to use first."
                    << std::endl
                    << "Type (1) for Dice 1.) " << move1 << std::endl
                    << "Type (2) for Dice 2.) " << move2 << std::endl
                    << ":";
          std::cin >> choice;
          if (!std::cin) {
            throw 3;
          }
          std::cout << std::endl << std::endl;
          check = true;
        }

        catch (int) {
          std::cout
              << std::endl
              << std::endl
              << "ERROR: Input invalid. Please enter a number between 1 and 2.";
          std::cin.clear();
          std::cin.ignore(100, '\n');
          std::cout << std::endl;
        }
      } while (check == false);
    }
    switch (choice) {
    case 1:
      if (move3 != 0) {
        moved = rowChoice - move3;
        errorCheck = backgammon.movePieceWhitePenalty(rowChoice, moved);
        if (errorCheck == 0) {
          move3 = 0;
          penalty = backgammon.checkPenaltyWhite();
          backgammon.printBoard();
        }
        break;
      }
      moved = rowChoice - move1;
      errorCheck = backgammon.movePieceWhitePenalty(rowChoice, moved);
      if (errorCheck == 0) {
        move1 = 0;
        penalty = backgammon.checkPenaltyWhite();
        backgammon.printBoard();
      }
      break;
    case 2:
      if (move4 != 0) {
        moved = rowChoice - move4;
        errorCheck = backgammon.movePieceWhitePenalty(rowChoice, moved);
        if (errorCheck == 0) {
          move4 = 0;
          penalty = backgammon.checkPenaltyWhite();
          backgammon.printBoard();
        }
        break;
      }

      moved = rowChoice - move2;
      errorCheck = backgammon.movePieceWhitePenalty(rowChoice, moved);
      if (errorCheck == 0) {
        move2 = 0;
        penalty = backgammon.checkPenaltyWhite();
        backgammon.printBoard();
      }
      break;
    default:
      std::cout
          << "That is not a valid input. Try again below by choosing the die "
             "you would want to start with."
          << std::endl
          << std::endl;
      break;
    }
  }

  do {
    if (move1 != 0 && move2 == 0) {
      std::cout << "Your remaining dice roll is: " << move1 << std::endl;
      choice = 1;
    } else if (move2 != 0 && move1 == 0) {
      std::cout << "Your remaining dice roll is: " << move2 << std::endl;
      choice = 2;
    } else {
      check = false;
      do {
        try {

          std::cout << "Please enter the die you would like to use first."
                    << std::endl
                    << "Type (1) for Dice 1.) " << move1 << std::endl
                    << "Type (2) for Dice 2.) " << move2 << std::endl
                    << ":";
          std::cin >> choice;
          if (!std::cin) {
            throw 3;
          }
          std::cout << std::endl << std::endl;
          check = true;
        }

        catch (int) {
          std::cout
              << std::endl
              << std::endl
              << "ERROR: Input invalid. Please enter a number between 1 and 2.";
          std::cin.clear();
          std::cin.ignore(100, '\n');
          std::cout << std::endl;
        }
      } while (check == false);
    }

    check = false;
    do {
      try {

        std::cout << "Now enter the row you want to move from: ";
        std::cin >> rowChoice; // add error handling

        if (!std::cin) {
          throw 4;
        }
        std::cout << std::endl << std::endl;
        check = true;
      }

      catch (int) {
        std::cout
            << std::endl
            << std::endl
            << "ERROR: Input invalid. Please enter a number between 1 and 24.";
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << std::endl;
      }
    } while (check == false);

    switch (choice) {
    case 1:
      if (move3 != 0) {
        moved = rowChoice - move3;
        errorCheck = backgammon.movePieceWhite(rowChoice, moved);
        if (errorCheck == 0) {
          move3 = 0;

          if (backgammon.checkWhiteWin()) {
            return true;
          }
        }
        break;
      }
      moved = rowChoice - move1;
      errorCheck = backgammon.movePieceWhite(rowChoice, moved);
      if (errorCheck == 0) {
        move1 = 0;

        if (backgammon.checkWhiteWin()) {
          return true;
        }
      }
      break;
    case 2:
      if (move4 != 0) {
        moved = rowChoice - move4;
        errorCheck = backgammon.movePieceWhite(rowChoice, moved);
        if (errorCheck == 0) {
          move4 = 0;

          if (backgammon.checkWhiteWin()) {
            return true;
          }
        }
        break;
      }

      moved = rowChoice - move2;
      errorCheck = backgammon.movePieceWhite(rowChoice, moved);
      if (errorCheck == 0) {
        move2 = 0;

        if (backgammon.checkWhiteWin()) {
          return true;
        }
      }
      break;
    default:
      std::cout
          << "That is not a valid input. Try again below by choosing the die "
             "you would want to start with."
          << std::endl
          << std::endl;
      break;
    }

    backgammon.printBoard();
    // if(backgammon.numOfWhites(rowChoice - 1) == 0)
    //{
    //}
  } while (move1 != 0 || move2 != 0);

  return false;
}

bool blackTurn(gameBoard &backgammon, string p1, string p2) {
  int move1 = 0;
  int move2 = 0;
  int move3 = 0;
  int move4 = 0;

  bool check = false;
  bool stuck;
  bool penalty;

  int errorCheck;

  int rowChoice;
  int moved;
  dice dice1, dice2;
  int choice;

  std::cout << p2 << ", you are Black. Rolling dice for your turn." << std::endl
            << std::endl;
  std::cout << "You rolled a 1.) ";
  move1 = dice1.rollDice();
  move2 = dice2.rollDice();

  std::cout << move1 << " and a 2.) " << move2 << std::endl << std::endl;

  if (move1 == move2) {

    std::cout << "You rolled doubles! You get to move twice for each die."
              << std::endl
              << std::endl;
    move3 = move1;
    move4 = move2;
  }

  penalty = backgammon.checkPenaltyBlack();

  while (penalty) {
    rowChoice = 0;
    stuck = backgammon.checkStuckBlack(move1, move2);
    if (stuck) {
      std::cout
          << "Your piece is stuck on the bar.You have no possible moves, your "
             "turn is over."
          << std::endl;

      return false;
    }
    if (move1 != 0 && move2 == 0) {
      std::cout << "Your remaining dice roll is: " << move1 << std::endl;
      choice = 1;
    } else if (move2 != 0 && move1 == 0) {
      std::cout << "Your remaining dice roll is: " << move2 << std::endl;
      choice = 2;
    } else {

      check = false;
      do {
        try {

          std::cout << "Please enter the die you would like to use first."
                    << std::endl
                    << "Type (1) for Dice 1.) " << move1 << std::endl
                    << "Type (2) for Dice 2.) " << move2 << std::endl
                    << ":";
          std::cin >> choice;
          if (!std::cin) {
            throw 3;
          }
          std::cout << std::endl << std::endl;
          check = true;
        }

        catch (int) {
          std::cout
              << std::endl
              << std::endl
              << "ERROR: Input invalid. Please enter a number between 1 and 2.";
          std::cin.clear();
          std::cin.ignore(100, '\n');
          std::cout << std::endl;
        }
      } while (check == false);
    }
    switch (choice) {
    case 1:
      if (move3 != 0) {
        moved = rowChoice + move3;
        errorCheck = backgammon.movePieceBlackPenalty(rowChoice, moved);
        if (errorCheck == 0) {
          move3 = 0;
          penalty = backgammon.checkPenaltyBlack();
          backgammon.printBoard();
        }
        break;
      }
      moved = rowChoice + move1;
      errorCheck = backgammon.movePieceBlackPenalty(rowChoice, moved);
      if (errorCheck == 0) {
        move1 = 0;
        penalty = backgammon.checkPenaltyBlack();
        backgammon.printBoard();
      }
      break;
    case 2:
      if (move4 != 0) {
        moved = rowChoice + move4;
        errorCheck = backgammon.movePieceBlackPenalty(rowChoice, moved);
        if (errorCheck == 0) {
          move4 = 0;
          penalty = backgammon.checkPenaltyBlack();
          backgammon.printBoard();
        }

        break;
      }

      moved = rowChoice + move2;
      errorCheck = backgammon.movePieceBlackPenalty(rowChoice, moved);
      if (errorCheck == 0) {
        move2 = 0;
        penalty = backgammon.checkPenaltyBlack();
        backgammon.printBoard();
      }
      break;
    default:
      std::cout
          << "That is not a valid input. Try again below by choosing the die "
             "you would want to start with."
          << std::endl
          << std::endl;
      break;
    }
  }

  do {
    if (move1 != 0 && move2 == 0) {
      std::cout << "Your remaining dice roll is: " << move1 << std::endl;
      choice = 1;
    } else if (move2 != 0 && move1 == 0) {
      std::cout << "Your remaining dice roll is: " << move2 << std::endl;
      choice = 2;
    } else {
      check = false;
      do {
        try {

          std::cout << "Please enter the die you would like to use first."
                    << std::endl
                    << "Type (1) for Dice 1.) " << move1 << std::endl
                    << "Type (2) for Dice 2.) " << move2 << std::endl
                    << ":";
          std::cin >> choice;
          if (!std::cin) {
            throw 3;
          }
          std::cout << std::endl << std::endl;
          check = true;
        }

        catch (int) {
          std::cout
              << std::endl
              << std::endl
              << "ERROR: Input invalid. Please enter a number between 1 and 2.";
          std::cin.clear();
          std::cin.ignore(100, '\n');
          std::cout << std::endl;
        }
      } while (check == false);
    }

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
      }

      catch (int) {
        std::cout
            << std::endl
            << std::endl
            << "ERROR: Input invalid. Please enter a number between 1 and 24.";
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << std::endl;
      }
    } while (check == false);

    switch (choice) {
    case 1:
      if (move3 != 0) {
        moved = rowChoice + move3;
        errorCheck = backgammon.movePieceBlack(rowChoice, moved);
        if (errorCheck == 0) {
          move3 = 0;

          if (backgammon.checkBlackWin()) {
            return true;
          }
        }
        break;
      }
      moved = rowChoice + move1;
      errorCheck = backgammon.movePieceBlack(rowChoice, moved);
      if (errorCheck == 0) {
        move1 = 0;

        if (backgammon.checkBlackWin()) {
          return true;
        }
      }
      break;
    case 2:
      if (move4 != 0) {
        moved = rowChoice + move4;
        errorCheck = backgammon.movePieceBlack(rowChoice, moved);
        if (errorCheck == 0) {
          move4 = 0;

          if (backgammon.checkBlackWin()) {
            return true;
          }
        }
        break;
      }

      moved = rowChoice + move2;
      errorCheck = backgammon.movePieceBlack(rowChoice, moved);
      if (errorCheck == 0) {
        move2 = 0;

        if (backgammon.checkBlackWin()) {
          return true;
        }
      }
      break;
    default:
      std::cout
          << "That is not a valid input. Try again below by choosing the die "
             "you would want to start with."
          << std::endl
          << std::endl;
      break;
    }

    backgammon.printBoard();
    // if(backgammon.numOfWhites(rowChoice - 1) == 0)
    //{
    //}
  } while (move1 != 0 || move2 != 0);

  return false;
}
