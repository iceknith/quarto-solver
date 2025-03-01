#include "HashMap.h"


HashMap::HashMap(int size) : size(size) {
    data = static_cast<cell *>(malloc(size*sizeof(cell)));

    empty();
}

void HashMap::empty() {
    for (int i = 0; i < size; i++) data[i] = empty_cell;
}

void HashMap::put(key k, u_int8_t value) {
    auto *usable_key = (u_int64_t *) k.value;
    cell c = {k, value};
    data[(*usable_key)%size] = c;
}

bool HashMap::get(key k, u_int8_t *value) {
    auto *usable_key = (u_int64_t *) k.value;
    cell c = data[(*usable_key)%size];

    if (equal(c.k, k)){
        *value = c.value;
        return true;
    }
    return false;
}

bool equal(key k1, key k2) {
    for (int i = 0; i < 10; i++) {
        if (k1.value[i] != k2.value[i]) return false;
    }
    return true;
}