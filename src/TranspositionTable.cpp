#include "TranspositionTable.h"


TranspositionTable::TranspositionTable(unsigned int size): T(size) {
    assert(T.size() > 0);
    m_size = size;
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

void TranspositionTable::load(){
    ;
}

void TranspositionTable::dump(){
    std::ofstream ofile("dump.csv");    
    for (int i = 0; i < size(); i++){
        ofile << T.at(i).key << ", " << uint64_t(T.at(i).val) << std::endl;
    }
    ofile.close();
}