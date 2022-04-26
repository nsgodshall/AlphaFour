#ifndef CLOCK_INCLUDED
#define CLOCK_INCLUDED

#include <chrono>

class Clock{
public:
    void start();

    int timeNow();

private:
    std::chrono::_V2::system_clock::time_point m_start;
};

#endif // CLOCK_INCLUDED