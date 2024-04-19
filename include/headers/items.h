#ifndef ITEMS_H
#define ITEMS_H

#include<structs.h>
#include<character.h>
#include<map.h>

class Items: public Entity{  
public:
    Items();
    ~Items();

    bool is_hit(int &map_element);
    bool is_hit(Character &player);
    void get_camera(const Stage &stage){
        map_x = stage.start.x;
        map_y = stage.start.y;
    }

protected:
    Vector2f velocity;
    Vector2i render_pos;
    bool is_eaten = false;
    bool spawned = false;
    bool spawning = false;
    int spawn_speed = 0;

    int map_x, map_y;
};

#endif