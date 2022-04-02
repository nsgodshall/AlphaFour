#ifndef TRANSPOSITIONTABLE_DEFINED
#define TRANSPOSITIONTABLE_DEFINED

#include <vector>
#include <functional>
#include <cstring>
#include <cassert>

class TranspositionTable    {
public: 
    TranspositionTable(unsigned int size);

    void put(uint64_t key, uint8_t val);

    // Placeholder
    uint8_t get(uint64_t key) const; 

    // TODO: MAKE PRIVATE
    inline unsigned int getIndex(uint64_t key) const { return key%T.size(); }

    inline void reset() { memset(&T[0], 0, T.size()*sizeof(Entry)); }

private:

    struct Entry {
      uint64_t key: 56;
      uint8_t val;   
    };

    std::vector<Entry> T;
};

#endif // TRANSPOSITIONTABLE_DEFINED