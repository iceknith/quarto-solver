#include "HashMap.h"


HashMap::HashMap(int size) : size(size) {
    data = static_cast<cell *>(malloc(size*sizeof(cell)));

    empty();
}

void HashMap::empty() {
    for (int i = 0; i < size; i++) data[i] = empty_cell;
}

void HashMap::put(u_int32_t k, const QuartoBoard& b, u_int8_t value) {
    data[k%size] = {b, value};
}

bool HashMap::get(u_int32_t k, const QuartoBoard& b, u_int8_t *value) {
    cell c = data[k%size];

    if (b.equals(c.board)){
        *value = c.value;
        return true;
    }
    return false;
}