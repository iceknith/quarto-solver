#ifndef QUATRO_SOLVER_C___QUARTOSOLVER_H
#define QUATRO_SOLVER_C___QUARTOSOLVER_H

#include "QuartoBoard.h"
#include "HashMap.h"
#include <iostream>

long int finalPosExplored;
long int posExplored;
long int prunedPos;
long int lookedUpPos;

double timer;
HashMap *hashMap;

int bestMovePick(const QuartoBoard *b);
int bestMovePlay(const QuartoBoard *b, u_int8_t  stone);

int bestMovePick(const QuartoBoard *b, int explorationDepth);
int bestMovePlay(const QuartoBoard *b, u_int8_t stone, int explorationDepth);
int negamaxPickEvaluation(const QuartoBoard& b, int explorationDepth, int alpha, int beta);
int negamaxPlayEvaluation(const QuartoBoard& b, u_int8_t stone, int explorationDepth, int alpha, int beta);


#endif