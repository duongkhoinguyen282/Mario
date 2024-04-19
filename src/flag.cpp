#include<flag.h>

Flag::Flag(){
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    map_x = 0;
    map_y = 0;
}

Flag::~Flag(){}

void Flag::draw(SDL_Renderer *&renderer){
    free();
    //load flag texture
    texture = load_texture(renderer, "res/image/clear_flag.png");

    if(spawning || spawned){
        render_pos.x = position.x - map_x;
        render_pos.y = position.y - map_y;

        SDL_Rect dest = {render_pos.x, render_pos.y, size.x, size.y}; 

        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }
}

void Flag::update(Stage &stage, Character &player){
    if(player.get_position().x + map_x >= 9450 && !player.clear_stage){
        player.clear_stage = true;
        Mix_HaltMusic();
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/stage_clear.wav"), 0);
        velocity = {0,0};
        spawned = false;
        is_eaten = false;
        position.x = 9450;
        position.y = 410;
        spawning = true;
    }
        
    if(spawning){
        spawn_speed += 1;
        position.y -= spawn_speed;
        if(spawn_speed >= 9){
            spawned = true;
            spawning = false;
            spawn_speed = 0;
        }
    }

    get_camera(stage);
}