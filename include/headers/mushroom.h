#ifndef MUSHROOM_H
#define MUSHROOM_H

#include<items.h>

#define MUSHROOM_SPEED 10

class Mushroom: public Items{  
public:
    Mushroom();
    ~Mushroom();

    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Character &player);
    void check_collision(Stage &stage, Character &player);
    bool get_spawning(){return spawning;}

private:
    std::string type;

};

#endif