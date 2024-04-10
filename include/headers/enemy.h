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

    void get_camera(const Stage &stage){
        map_x = stage.start.x;
        map_y = stage.start.y;
    }

protected:
    Vector2i render_pos;
    Vector2f velocity;
    SDL_Rect frames[ENEMY_FRAMES];
    int frame;
    bool face_left;
    bool is_dead = false;

    int map_x, map_y;
};

#endif