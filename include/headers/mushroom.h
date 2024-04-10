#ifndef MUSHROOM_H
#define MUSHROOM_H

#include<structs.h>
#include<character.h>
#include<map.h>

#define MUSHROOM_SPEED 10

class Mushroom: public Entity{  
public:
    Mushroom();
    ~Mushroom();

    void draw(SDL_Renderer* &renderer);
    void update(Stage &stage, Character &player);
    void check_collision(Stage &stage, Character &player);
    bool is_hit(int &map_element);
    bool is_hit(Character &player);
    void get_camera(const Stage &stage){
        map_x = stage.start.x;
        map_y = stage.start.y;
    }
    bool get_spawning(){return spawning;}

private:
    Vector2f velocity;
    Vector2i render_pos;
    bool is_eaten = false;
    bool spawned = false;
    bool spawning = false;
    int spawn_speed = 0;
    std::string type;

    int map_x, map_y;
};

#endif