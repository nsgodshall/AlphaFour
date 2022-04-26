#include "Clock.h"

void Clock::start()
{
    m_start = std::chrono::high_resolution_clock::now(); // START DEBUG TIMER
}

int Clock::timeNow(){
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - m_start);
    return duration.count();
}