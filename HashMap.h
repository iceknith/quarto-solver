#ifndef QUATRO_SOLVER_C___HASHMAP_H
#define QUATRO_SOLVER_C___HASHMAP_H

#include <iostream>

typedef struct key {
    u_int8_t value[10];
} key;

typedef struct cell {
    key k;
    u_int8_t value;
} cell;

key empty_key = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
cell empty_cell = {empty_key, 0};
bool equal(key k1, key k2);

class HashMap {
    int size;
    cell* data;

public:
    HashMap(int size);

    void empty();

    void put(key k, u_int8_t value);
    bool get(key k, u_int8_t *value);
};


#endif
