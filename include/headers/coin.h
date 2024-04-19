#ifndef COIN_H
#define COIN_H

#include<items.h>

class Coin: public Items{  
public:
    Coin();
    ~Coin();

    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Character &player);
    bool get_spawning(){return spawning;}
    
private:
    int blink = 1;
    int mod_size = 6;
    int mod_pos = 3;
    SDL_Point center;
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
};

#endif