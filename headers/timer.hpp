#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer {
public:
    Timer();
    
    void start();
    void stop();
    void resume();

    time_t get_time() const;

    static time_t time(time_t* value_time = nullptr);

private:
    bool _run_timer;
    time_t _start_time;
    time_t _pause_time;
};

#endif
