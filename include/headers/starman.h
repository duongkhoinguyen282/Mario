#ifndef STARMAN_H
#define STARMAN_H

#include<items.h>

class Starman: public Items{  
public:
    Starman();
    ~Starman();

    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Character &player);
    bool get_spawning(){return spawning;}
    
private:
    int blink = 1;
};

#endif