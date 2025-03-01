#ifndef QUATRO_SOLVER_C___QUARTO_BOARD_H
#define QUATRO_SOLVER_C___QUARTO_BOARD_H

#include <iostream>
#include "HashMap.h"

#define width 5
#define height 4

std::string stoneToCharTable[16] = {
        "□sh","○sh","■sh","●sh",
        "□bh","○bh","■bh","●bh",
        "□sf","○sf","■sf","●sf",
        "□bf","○bf","■bf","●bf"
};

class QuartoBoard {

    u_int32_t occupation;
    u_int32_t circle;
    u_int32_t white;
    u_int32_t tall;
    u_int32_t full;

    static bool isFree(u_int32_t bitBoard, u_int8_t x, u_int8_t y);
    static bool has4Streak(u_int32_t bitBoard);
    static u_int8_t bitboardTransposition(u_int32_t bitBoard, bool high_bits);

public:
    u_int8_t availableStoneCount;
    bool availableStones[16];

    QuartoBoard();
    QuartoBoard(QuartoBoard const &b);

    bool isFree(u_int8_t x, u_int8_t y) const;
    bool isFree(u_int8_t offset) const;
    void place(u_int8_t stone, u_int8_t x, u_int8_t y);
    void place(u_int8_t stone, u_int8_t offset);
    bool hasWin();
    key getKey() const;

    void print();
};


#endif
