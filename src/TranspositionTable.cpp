#include "TranspositionTable.h"

TranspositionTable::TranspositionTable(unsigned int size): T(size) {
    assert(T.size() > 0);
}

void TranspositionTable::put(uint64_t key, uint8_t val){
    unsigned int i = getIndex(key);

    T[i].key = key;
    T[i].val = val;
    return;
}

uint8_t TranspositionTable::get(uint64_t key) const {
    unsigned int i = getIndex(key);
    if (T[i].key == key)
        return T[i].val;
    return 0; 
}