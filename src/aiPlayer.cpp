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
    rowsToWinBlack += backgammon.numOfBlacks(i) * distToEndB;
    rowsToWinWhite += backgammon.numOfWhites(i) * distToEndW;
  }
  heuristicsTotal -= (rowsToWinBlack - rowsToWinWhite);
  heuristicsTotal -= cntBarBlack * 50;
  heuristicsTotal += cntBarWhite * 50;
  heuristicsTotal += blackOut * 100;
  heuristicsTotal -= whiteOut * 100;
  return heuristicsTotal;
}

std::vector<aiPlayer::Movement> aiPlayer::findAllMovesW(gameBoard &backgammon,
                                                        int diceScore) {
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
  return candidateMovments;
}

std::vector<aiPlayer::Movement> aiPlayer::findAllMovesB(gameBoard &backgammon,
                                                        int diceScore) {
  std::vector<Movement> candidateMovments;
  if (backgammon.checkPenaltyBlack()) {
    int start = 0;
    int end = start + diceScore;
    gameBoard tmp = backgammon;
    if (tmp.movePieceBlackPenalty(start, end) == 0)
      candidateMovments.push_back({start, end});
  } else {
    for (int i = 1; i <= 24; i++) {
      if (backgammon.numOfBlacks(i - 1) > 0) {
        Movement actual = {i, i + diceScore};
        gameBoard tmp = backgammon;
        if (tmp.movePieceBlack(actual.start, actual.end) == 0)
          candidateMovments.push_back(actual);
      }
    }
  }
  return candidateMovments;
}

void aiPlayer::doMove(gameBoard &backgammon, Movement move, bool isBlack) {
  if (isBlack) {
    if (move.start == 0)
      backgammon.movePieceBlackPenalty(move.start, move.end);
    else
      backgammon.movePieceBlack(move.start, move.end);
  } else {
    if (move.start == 25)
      backgammon.movePieceWhitePenalty(move.start, move.end);
    else
      backgammon.movePieceWhite(move.start, move.end);
  }
}

double aiPlayer::minMax(gameBoard &backgammon, int depth, bool isMaxi) {
  if (depth == 0)
    return heuristicsEvaluation(backgammon);

  double e = 0.0;
  for (int i = 1; i <= 3; i++) {
    std::vector<Movement> candidateMovments;
    if (isMaxi)
      candidateMovments = findAllMovesB(backgammon, i);
    else
      candidateMovments = findAllMovesW(backgammon, i);

    double best;
    if (candidateMovments.empty())
      best = heuristicsEvaluation(backgammon);
    else {
      if (isMaxi) {
        best = -std::numeric_limits<double>::infinity();
        for (const Movement &m : candidateMovments) {
          gameBoard tmp = backgammon;
          doMove(tmp, m, true);
          double cur = minMax(tmp, depth - 1, false);
          best = std::max(best, cur);
        }
      } else {
        best = std::numeric_limits<double>::infinity();
        for (const Movement &m : candidateMovments) {
          gameBoard tmp = backgammon;
          doMove(tmp, m, false);
          double cur = minMax(tmp, depth - 1, true);
          best = std::min(best, cur);
        }
      }
    }
    e += best;
  }
  return e / 3.0;
}

bool aiPlayer::findMax(gameBoard &backgammon, std::string p1, std::string p2) {
  dice d1;
  int movement = d1.rollDice();
  std::cout << p2 << ", you are Black. Rolling dice for your turn.\n";
  std::cout << "You rolled a " << movement << "\n";

  std::vector<Movement> candidateMovments = findAllMovesB(backgammon, movement);
  if (candidateMovments.empty()) {
    std::cout << "AI Player has no possible moves. Turn is over.\n";
    system("pause");
    return false;
  }

  Movement max = candidateMovments[0];
  double maxHeuristic = -std::numeric_limits<double>::infinity();

  for (const Movement &m : candidateMovments) {
    gameBoard tmp = backgammon;
    doMove(tmp, m, true);
    double cur = minMax(tmp, 1, false);
    if (cur > maxHeuristic) {
      maxHeuristic = cur;
      max = m;
    }
  }
  std::string startStr = std::to_string(max.start);
  std::string endStr = std::to_string(max.end);
  std::cout << "AI Player moves from " << startStr << "to " << endStr << ".\n";

  doMove(backgammon, max, true);

  system("pause");
  backgammon.printBoard();
  return backgammon.checkBlackWin();
}
