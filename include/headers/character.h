#ifndef CHARACTER_H
#define CHARACTER_H

#include<entity.h>
#include<map.h>

#define ACCELERATION 15;
#define CHAR_FRAMES 7
#define JUMP_HEIGHT (TILE_SIZE*4)

class Character: public Entity{
public:
    Character();
    ~Character();

    void set_frame();
    void draw(SDL_Renderer* &renderer);
    void handle_input(SDL_Event event);
    void update(Stage &stage);
    void check_collision(Stage &stage);
    bool is_hit(int &map_element);
    void follow(Stage &stage);
    void die();
    bool get_death(){return is_dead;};
    void power_up(Stage &stage, int y1, int x1, int x2);

private:
    Vector2f velocity;
    SDL_Rect frames[CHAR_FRAMES];
    int frame;
    bool face_right;
    Input input;
    bool on_ground = false;
    bool is_dead = false;
};

#endif