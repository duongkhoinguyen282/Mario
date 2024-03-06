#ifndef ANIMATION_H
#define ANIMATION_H

#include<render_window.h>

class Animation{
public:
    Animation(SDL_Texture* textuxe, Vector2i img_count, float switch_time);
    ~Animation();

    void update(int row, float delta_time);

public:
    SDL_Rect rect;

private:
    Vector2i img_count;
    Vector2i curr_image;

    float total_time;
    float switch_time;
};

#endif