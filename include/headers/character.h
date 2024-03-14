#ifndef CHARACTER_H
#define CHARACTER_H

#include<entity.h>
#include<map.h>

class Character: public Entity
{
public:
    Character();
    ~Character();

    void set_frame();
    void draw(SDL_Renderer* &renderer);
    void handle_input(SDL_Event event);
    void update(Stage &stage);
    void check_collision(Stage &stage);
    bool is_hit(int &map_element);
    void set_camera(int &map_x, int &map_y);
    void follow(Stage &stage);
    void power_up(Stage &stage, int y1, int x1, int x2);

private:
    Vector2f velocity;
    Vector2i real_pos;
    SDL_Rect frames[CHAR_FRAMES];
    int frame;
    bool face_right;
    Input input;
    bool on_ground = false;

    int map_x, map_y;
};

#endif