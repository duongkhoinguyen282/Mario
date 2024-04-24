#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include<defs.h>
#include<text.h>
#include<timer.h>

class Score_Manager{
public:
    Score_Manager();
    ~Score_Manager();

    void update(SDL_Renderer* &renderer);

public:
    Text item_score;
    int score_increase;

private:
    TTF_Font* font;
    SDL_Color color;
    bool appear = false;
    double appear_time = 1.5f;
};

#endif