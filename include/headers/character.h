#ifndef CHARACTER_H
#define CHARACTER_H

#include<entity.h>
#include<map.h>

class Character: public Entity
{
public:
    Character();
    ~Character();

    SDL_Texture* load_texture(SDL_Renderer* &renderer, std::string filename);
    void set_frame();
    void draw(SDL_Renderer* &renderer);
    void handle_input(SDL_Renderer* &renderer, SDL_Event event);
    void update(Map &map);
    void check_collision(Map &map);
    bool is_hit(int map_data);
    void follow(const int map_x, const int map_y);

private:
    Vector2f velocity;
    SDL_Rect frames[4];
    int frame;
    bool face_right;
    Input input;
    bool can_jump = false;

    int map_x, map_y;
};

#endif