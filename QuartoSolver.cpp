#include "QuartoSolver.h"
#include "QuartoBoard.cpp"

#include <chrono>

int bestMovePick(const QuartoBoard *b) {
    return bestMovePick(b, b->number_of_turns());
}
int bestMovePlay(const QuartoBoard *b, u_int8_t stone) {
    return bestMovePlay(b, stone, b->number_of_turns());
}

int bestMovePick(const QuartoBoard *b, int explorationDepth) {
    if (explorationDepth <= 0) return -1;

    int alpha = -explorationDepth - 1;
    int beta = explorationDepth + 1;
    int bestMove = -1;
    u_int16_t availableStonesIte = b->availableStones;


    for (int stone = 0; stone < 16; stone++) {
        if (!(availableStonesIte & 1)) {
            int eval = -negamaxPlayEvaluation(*b, stone, explorationDepth, -beta, -alpha);

            if (eval > alpha) {
                alpha = eval;
                bestMove = stone;
            }
        }
        availableStonesIte >>= 1;
    }

    std::cout << "pick evaluation :" << alpha << "\n";
    return bestMove;
}

int bestMovePlay(const QuartoBoard *b, u_int8_t stone, int explorationDepth) {
    if (explorationDepth <= 0) return -1;

    u_int8_t offset = 0;
    QuartoBoard new_board;

    int alpha = -explorationDepth;
    int beta = explorationDepth;
    int bestMove = -1;

    for (u_int8_t y = 0; y < height; y++) {
        for (u_int8_t x = 0; x < width - 1; x++) {

            if (b->isFree(offset)) {

                new_board = QuartoBoard(*b);
                new_board.place(stone, offset);
                if (new_board.hasWin()) {
                    std::cout << "play evaluation : " << explorationDepth << "\n";
                    return offset;
                }

                int eval = negamaxPickEvaluation(new_board, explorationDepth-1, alpha, beta);

                if (eval > alpha) {
                    alpha = eval;
                    bestMove = offset;
                }

            }

            offset++;
        }
        // Jump a line
        offset++;
    }

    std::cout << "play evaluation : " << alpha << "\n";
    return bestMove;
}

int negamaxPickEvaluation(const QuartoBoard& b, int explorationDepth, int alpha, int beta) {
    if (explorationDepth <= 0) return 0;
    u_int16_t availableStonesIte = b.availableStones;

    for (int stone = 0; stone < 16; stone++) {
        if (!(availableStonesIte & 1)) {
            int eval = -negamaxPlayEvaluation(b, stone, explorationDepth, -beta, -alpha);

            if (eval > alpha) {
                alpha = eval;

                if (alpha >= beta) {
                    // Alpha-Beta pruning
                    return alpha;
                }
            }
        }
        availableStonesIte >>= 1;
    }

    return alpha;
}

int negamaxPlayEvaluation(const QuartoBoard& b, u_int8_t stone, int explorationDepth, int alpha, int beta) {
    posExplored++;
    if (explorationDepth <= 0) {
        finalPosExplored++;
        return 0;
    }

    u_int8_t offset = 0;
    QuartoBoard new_board;
    uint32_t k = b.getKey();

    int max = explorationDepth;
    auto *hash_map_val = (u_int8_t *) malloc(sizeof(u_int8_t));

    if (hashMap->get(k, b, hash_map_val)) {
        max = *hash_map_val;
        lookedUpPos++;
    }

    free(hash_map_val);

    if (beta > max) {
        beta = max;
        if (alpha >= beta) {
            prunedPos++;
            return alpha;
        }
    }


    for (u_int8_t y = 0; y < height; y++) {
        for (u_int8_t x = 0; x < width - 1; x++) {

            if (b.isFree(offset)) {

                new_board = QuartoBoard(b);
                new_board.place(stone, offset);
                if (new_board.hasWin()) {
                    finalPosExplored++;
                    return explorationDepth;
                }

                int eval = negamaxPickEvaluation(new_board, explorationDepth-1, alpha, beta);

                if (eval > alpha) {
                    alpha = eval;

                    if (alpha >= beta) {
                        // Alpha-Beta pruning
                        prunedPos++;
                        return alpha;
                    }
                }

            }

            offset++;
        }
        // Jump a line
        offset++;
    }

    hashMap->put(k, b, alpha);
    return alpha;
}