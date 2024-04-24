//this piece of code is stolen Phat trien phan mem 123A-Z
#ifndef TIMER_H
#define TIMER_H

#include<defs.h>

class Timer{
public:
    Timer();
    ~Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;

    bool is_start;
    bool is_pause;
};

#endif