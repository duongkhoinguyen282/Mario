#include<starman.h>

Starman::Starman(){
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    map_x = 0;
    map_y = 0;
    is_eaten = true;
}

Starman::~Starman(){}

void Starman::draw(SDL_Renderer *&renderer){
    free();
    //load starman texture
    texture = load_texture(renderer, "res/image/starman.png");

    //mario hit starman
    if(is_eaten) {
        free();
    }

    if(spawning || spawned){
        if(blink == 0) blink = 1;
        else blink = 0;

        SDL_SetTextureColorMod(texture,255 + blink*208,255 + blink*155,255 + blink*22);

        render_pos.x = position.x - map_x;
        render_pos.y = position.y - map_y;

        SDL_Rect dest = {render_pos.x, render_pos.y, size.x, size.y}; 

        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }
}

void Starman::update(Stage &stage, Character &player){
    if(player.hit_item == Item::_Starman){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/power_up_appears.wav"), 0);
        velocity = {0,0};
        spawned = false;
        // std::cout<<stage.tile_coord.y<<" "<<stage.tile_coord.x<<std::endl;
        is_eaten = false;
        position.x = player.item_spawn_pos.x*TILE_SIZE;
        position.y = player.item_spawn_pos.y*TILE_SIZE;
        player.hit_item = false;
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

    //if mario hit starman will disappear
    if(is_eaten) {
        velocity = {0,0};
        spawned = false;
        spawning = false;
        position = {0,0};
    }

    if(is_hit(player) && !is_eaten){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/power_up.wav"), 0);
        is_eaten = true;
        player.invincible = true;
        player.invincible_time = INVINCIBLE_TIME*2;
        player.acceleration = 25;
        player.sco_mana.score_increase = 1000;
    }

    get_camera(stage);
}