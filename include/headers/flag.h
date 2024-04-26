#ifndef FLAG_H
#define FLAG_H

#include<items.h>

class Flag: public Items{  
public:
    Flag();
    ~Flag();

    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Character &player);
    bool get_spawning(){return spawning;}
    bool is_spawned(){return spawned;}
    
private:

};

#endif