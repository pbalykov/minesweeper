#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer {
public:
    Timer();
    
    ttime_t start();
    ttime_t stop();
    ttime_t pause();

    ttime_t get_time() const;

    static ttime_t time(time_t* time = nullptr);

private:
    bool _job_timer;
    ttime_t _start_time;
    ttime_t _pause_time;
};

#endif
