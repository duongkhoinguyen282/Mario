#include<coin.h>

Coin::Coin(){
    position = {0,0};
    velocity = {0,0};
    size = {30,30};
    map_x = 0;
    map_y = 0;
}

Coin::~Coin(){}

void Coin::draw(SDL_Renderer *&renderer){
    free();
    //load coin texture
    texture = load_texture(renderer, "res/image/coin.png");
    
    //set center of the coin
    center = {(position.x+size.x)/2, (position.y+size.y)/2};
    
    if(spawning || spawned){
        if(blink == 0) blink = 1;
        else blink = 0;

        SDL_SetTextureColorMod(texture,255 + blink*208,255 + blink*155,255 + blink*22);

        render_pos.x = position.x - map_x;
        render_pos.y = position.y - map_y;

        SDL_Rect dest = {render_pos.x, render_pos.y, size.x, size.y}; 

        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, &center, flip);
    }
}

void Coin::update(Stage &stage, Character &player){
    if(player.hit_item == 6){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/coin.wav"), 0);
        player.sco_mana.score_increase = 100;
        player.coin += 1;
        velocity = {0,0};
        spawned = false;
        is_eaten = false;
        position.x = player.item_spawn_pos.x*TILE_SIZE + 12;
        position.y = player.item_spawn_pos.y*TILE_SIZE;
        player.hit_item = false;
        spawning = true;
    }

    //rotate animation
    if(size.x == 30) {
        mod_size = -6;
        mod_pos = 3;
    }
    else if(size.x == 6) {
        if(flip == SDL_FLIP_NONE) flip = SDL_FLIP_HORIZONTAL;
        else if(flip == SDL_FLIP_HORIZONTAL) flip = SDL_FLIP_NONE;
        mod_size = 6;
        mod_pos = -3;
    }

    position.x += mod_pos;
    size.x += mod_size;
        
    if(spawning){
        spawn_speed += 10;
        position.y -= spawn_speed;
        if(spawn_speed >= 50){
            spawned = true;
            spawning = false;
            spawn_speed = 0;
        }
    }

    if(spawned){
        velocity.y += GRAVITY;
        position.y += velocity.y;
        if(position.y + velocity.y >= player.item_spawn_pos.y*TILE_SIZE){
            spawned = false;
            free();
            return;
        }
    }

    get_camera(stage);
}