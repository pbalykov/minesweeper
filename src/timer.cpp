#include "../headers/timer.hpp"

Timer::Timer() : _run_timer(false), _start_time(0), _pause_time(0) {
    return ;
}

void Timer::start() {
    if ( !this->_run_timer ) {
        this->_run_timer = true;
        this->_start_time = Timer::time();       
    }
    return ;
} 

void Timer::stop() {
    this->_run_timer = false;
    this->_pause_time = Timer::time() - this->_start_time;
    this->_start_time = 0;
    return ;
}

void Timer::reset() {
    this->_run_timer = false;
    this->_pause_time = 0;
    this->_start_time = 0;
    return ;
}

time_t Timer::get_time() const {
    if ( this->_start_time == 0 ) {
        return 0;
    }
    return this->_pause_time + Timer::time() - this->_start_time;
}

time_t Timer::time(time_t* value_time) {
    return std::time(value_time);
}
