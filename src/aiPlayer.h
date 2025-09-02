#pragma once
#include "dice.h"
#include "gameBoard.h"
#include <limits>
#include <string>
#include <vector>

class aiPlayer {
public:
  struct Movement {
    int start, end;
  };

  double heuristicsEvaluation(gameBoard &backgammon);
  std::vector<Movement> findAllMovesB(gameBoard &backgammon, int diceScore);
  std::vector<Movement> findAllMovesW(gameBoard &backgammon, int diceScore);
  void doMove(gameBoard &backgammon, Movement move, bool isBlack);
  double minMax(gameBoard &backgammon, int depth, bool isMaxi);
  double findMin(gameBoard &backgammon, int diceScore);
  double getRandomnessAvg(gameBoard &backgammon);
  bool findMax(gameBoard &backgammon, std::string p1, std::string p2);
};
