#include<timer.h>

Timer::Timer(){
    start_tick = 0;
    paused_tick = 0;
    is_pause = false;
    is_start = false;
}

Timer::~Timer(){}

void Timer::start(){
    is_start = true;
    is_pause = false;
    start_tick = SDL_GetTicks();
}

void Timer::stop(){
    is_pause = false;
    is_start = false;
}

void Timer::pause(){
    if(is_start && !is_pause){
        is_pause = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}

void Timer::unpause(){
    if(is_pause){
        is_pause = false;
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int Timer::get_ticks(){
    if(is_start){
        if(is_pause){
            return paused_tick;
        }
    }
    else{
        return SDL_GetTicks() - start_tick;
    }

    return 0;
}

bool Timer::is_started(){
    return is_start;
}

bool Timer::is_paused(){
    return is_pause;
}
