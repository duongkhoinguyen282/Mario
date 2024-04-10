#ifndef GOOMBA_H
#define GOOMBA_H

#include<enemy.h>
#include<map.h>
#include<character.h>

#define GOOMBA_FRAMES 2
#define GOOMBA_SPEED 3
#define NUM_OF_GOOMBAS 10

class Goomba: public Enemy{
public:
    Goomba();
    ~Goomba();

    void set_frame();
    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Goomba* &goombas, Character &player);
    void check_collision(Stage &stage, Goomba* &goombas, Character &player);
    bool is_hit(int &map_element);
    bool horiz_hit(Character &player);
    bool verti_hit(Character &player);
    bool is_hit_right(Goomba* &goombas);
    bool is_hit_left(Goomba* &goombas);
    Goomba* spawn();
    void update_and_draw(SDL_Renderer *&renderer, Stage &stage, Goomba *goombas, Character &player);
    void die();

private:
    SDL_Rect frames[GOOMBA_FRAMES];
};

#endif