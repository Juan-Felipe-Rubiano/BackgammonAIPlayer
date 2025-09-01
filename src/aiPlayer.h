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
  double findMin(gameBoard &backgammon, int diceScore);
  double getRandomnessAvg(gameBoard &backgammon);
  bool findMax(gameBoard &backgammon, std::string p1, std::string p2);
};
