#ifndef CHARACTER_H
#define CHARACTER_H

#include<entity.h>
#include<map.h>
#include<score_manager.h>

#define ACCELERATION 15;
#define CHAR_FRAMES 7
#define JUMP_HEIGHT (TILE_SIZE*4)
#define INVINCIBLE_TIME 2*FPS

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
    void power_up();
    void normalize();
    Vector2f get_velocity(){return velocity;};
    void set_velocity(Vector2f velocity);
    std::string get_status(){return status;};
    // Text get_item_score(){return item_score;}

public:
    int invincible_time = INVINCIBLE_TIME;
    int acceleration = ACCELERATION;
    bool invincible = false;
    int hit_item = false;
    Vector2i item_spawn_pos;
    bool clear_stage = false;
    int score = 0;
    int lives = 1;
    int coin = 0;
    Uint32 time_left = 10;
    Score_Manager sco_mana;

private:
    Vector2f velocity;
    SDL_Rect frames[CHAR_FRAMES];
    int frame;
    bool face_right;
    Input input;
    bool on_ground = false;
    bool is_dead = false;
    bool can_crouch = true;
    std::string status = "normal";
};

#endif