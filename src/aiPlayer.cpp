#include "aiPlayer.h"

double aiPlayer::heuristicsEvaluation(gameBoard &backgammon) {
  double heuristicsTotal = 0;
  int cntBarBlack = backgammon.getNumBlackPenalty();
  int cntBarWhite = backgammon.getNumWhitePenalty();
  int blackOut = backgammon.getBlackTotal();
  int whiteOut = backgammon.getWhiteTotal();
  int rowsToWinWhite = 0;
  int rowsToWinBlack = 0;
  for (int i = 0; i < 24; i++) {
    int distToEndB = 24 - i;
    int distToEndW = i + 1;
    rowsToWinBlack += backgammon.numOfBlacks(i) * (distToEndB);
    rowsToWinWhite += backgammon.numOfWhites(i) * distToEndW;
  }
  heuristicsTotal -= (rowsToWinBlack - rowsToWinWhite);
  heuristicsTotal -= cntBarBlack * 50;
  heuristicsTotal += cntBarWhite * 50;
  heuristicsTotal += blackOut * 100;
  heuristicsTotal -= whiteOut * 100;
  return heuristicsTotal;
}

double aiPlayer::findMin(gameBoard &backgammon, int diceScore) {
  std::vector<Movement> candidateMovments;
  if (backgammon.checkPenaltyWhite()) {
    int start = 25;
    int end = start - diceScore;
    gameBoard tmp = backgammon;
    if (tmp.movePieceWhite(start, end) == 0)
      candidateMovments.push_back({start, end});
  } else {
    for (int i = 1; i <= 24; i++) {
      if (backgammon.numOfWhites(i - 1) > 0) {
        Movement actual = {i, i - diceScore};
        gameBoard tmp = backgammon;
        if (tmp.movePieceWhite(actual.start, actual.end) == 0)
          candidateMovments.push_back(actual);
      }
    }
  }
  if (candidateMovments.empty())
    return heuristicsEvaluation(backgammon);

  // Choose min generating movment for op
  double min = std::numeric_limits<double>::infinity();
  for (Movement m : candidateMovments) {
    gameBoard tmp = backgammon;
    if (m.start == 25)
      tmp.movePieceWhitePenalty(m.start, m.end);
    else
      tmp.movePieceWhite(m.start, m.end);

    min = std::min(min, heuristicsEvaluation(tmp));
  }
  return min;
}

double aiPlayer::getRandomnessAvg(gameBoard &backgammon) {
  double avg = 0.0;
  for (int i = 1; i <= 3; i++) {
    avg += findMin(backgammon, i);
  }
  return avg / 3.0;
}

bool aiPlayer::findMax(gameBoard &backgammon, std::string p1, std::string p2) {
  dice d1;
  int movement = d1.rollDice();
  std::cout << p2 << ", you are Black. Rolling dice for your turn.\n";
  std::cout << "You rolled a " << movement << "\n";

  std::vector<Movement> candidateMovments;
  if (backgammon.checkPenaltyBlack()) {
    int start = 0;
    int end = start + movement;
    gameBoard tmp = backgammon;
    if (tmp.movePieceBlackPenalty(start, end) == 0)
      candidateMovments.push_back({start, end});
  } else {
    for (int i = 1; i <= 24; i++) {
      if (backgammon.numOfBlacks(i - 1) > 0) {
        Movement cur = {i, i + movement};
        gameBoard tmp = backgammon;
        if (tmp.movePieceBlack(cur.start, cur.end) == 0)
          candidateMovments.push_back(cur);
      }
    }
  }
  if (candidateMovments.empty()) {
    std::cout << "AI Player has no possible moves. Turn is over.\n";
    system("pause");
    return false;
  }
  Movement max = candidateMovments[0];
  double maxHeuristic = -std::numeric_limits<double>::infinity();

  for (Movement m : candidateMovments) {
    gameBoard tmp = backgammon;
    if (m.start == 0)
      tmp.movePieceBlackPenalty(m.start, m.end);
    else
      tmp.movePieceBlack(m.start, m.end);

    double curRandAvg = getRandomnessAvg(tmp);
    if (curRandAvg > maxHeuristic) {
      maxHeuristic = curRandAvg;
      max = m;
    }
  }
  std::string startStr = std::to_string(max.start);
  std::string endStr = std::to_string(max.end);
  std::cout << "AI Player moves from " << startStr << "to " << endStr << ".\n";

  if (max.start == 0)
    backgammon.movePieceBlackPenalty(max.start, max.end);
  else
    backgammon.movePieceBlack(max.start, max.end);

  system("pause");
  backgammon.printBoard();
  return backgammon.checkBlackWin();
}
