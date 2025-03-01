#ifndef QUATRO_SOLVER_C___HASHMAP_H
#define QUATRO_SOLVER_C___HASHMAP_H

#include <iostream>
#include "QuartoBoard.h"


typedef struct cell {
    QuartoBoard board;
    u_int8_t value;
} cell;

cell empty_cell = {QuartoBoard(), 0};

class HashMap {
    int size;
    cell* data;

public:
    HashMap(int size);

    void empty();

    void put(u_int32_t k, const QuartoBoard& b, u_int8_t value);
    bool get(u_int32_t k, const QuartoBoard& b, u_int8_t *value);
};


#endif
