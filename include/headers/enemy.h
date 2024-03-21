#ifndef ENEMY_H
#define ENEMY_H

#include<entity.h>
#include<map.h>

#define ENEMY_FRAMES 2
#define ENEMY_SPEED 0.1

class Enemy: public Entity{
public:
    Enemy();
    ~Enemy();

    void get_camera(const Stage &stage);

protected:
    Vector2i render_pos;
    Vector2f velocity;
    SDL_Rect frames[ENEMY_FRAMES];
    int frame;
    bool face_left;
    int spawn_time;
    bool on_ground = false;
    bool is_dead = false;

    int map_x, map_y;
};

#endif