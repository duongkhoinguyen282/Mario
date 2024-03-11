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
    void handle_input(SDL_Renderer* &renderer, SDL_Event event);
    void update(Map &map);
    void check_collision(Map &map);
    bool is_hit(int map_element);
    void set_camera(const int map_x, const int map_y);
    void follow(Map &map);

private:
    Vector2f velocity;
    SDL_Rect frames[CHAR_FRAMES];
    int frame;
    bool face_right;
    Input input;
    bool on_ground = false;

    int map_x, map_y;
};

#endif