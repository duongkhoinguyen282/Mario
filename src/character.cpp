#include<character.h>

Character::Character(){
    frame = 0;
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    face_right = true;
    input.right = false;
    input.left = false;
    input.jump = false;
    set_frame();
}

Character::~Character(){}

void Character::set_frame(){
    if(size.x > 0 && size.y > 0){
        for(int i = 0; i < CHAR_FRAMES; i++){
            frames[i].x = i*size.x;
            frames[i].y = 0;
            frames[i].w = size.x;
            frames[i].h = size.y;
        }
    }
}

void Character::draw(SDL_Renderer* &renderer){
    free();
    // std::string m = "mario";
    //load mario texture
    if(face_right){
        texture = load_texture(renderer,"res/image/"+ status +"/mario_right.png");
    }
    else{
        texture = load_texture(renderer,"res/image/"+ status +"/mario_left.png");
    }

    //mario crouch
    if(on_ground && input.crouch && status == "big"){
        frame = 6;
    }

    //mario jump
    else if(input.jump && !input.crouch){
        frame = 4;
    }

    //mario walk
    else if((input.left && !input.right) || (input.right && !input.left) && !is_dead){
        face_right = input.right & ~input.left;
        frame++;
        if(frame >= 4) frame = 1;
    }

    //mario brake
    else if(input.left && input.right){
        frame = 5;
    }

    //idle mario
    else{
        frame = 0;
    }

    //invincible mario
    if(invincible){
        SDL_SetTextureAlphaMod(texture,255*(invincible_time%2));
    }

    //mario die
    if(is_dead) {
        free();
        texture = load_texture(renderer, "res/image/mario_die.png");
    }

    SDL_Rect* curr_frame = &frames[frame];
    SDL_Rect dest = {position.x, position.y, size.x, size.y}; 

    SDL_RenderCopy(renderer, texture, curr_frame, &dest);

    sco_mana.update(renderer);
}

void Character::handle_input(SDL_Event event){
    if(is_dead){
        return;
    }
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_RIGHT){
            face_right = true;
            input.right = true;
        }
        if(event.key.keysym.sym == SDLK_LEFT){
            face_right = false;
            input.left = true;
        }

        if(event.key.keysym.sym == SDLK_UP){
            input.jump = true;
        }
        if(event.key.keysym.sym == SDLK_DOWN && on_ground && status == "big"){
            input.crouch = true;
        }
        if(event.key.keysym.sym == SDLK_k){
            die();
        }
        // if(event.key.keysym.sym == SDLK_b && status == "normal"){
        //     power_up();
        // }
        // if(event.key.keysym.sym == SDLK_s){
        //     normalize();
        // }
    }
    else if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_RIGHT){
            input.right = false;
        }
        if(event.key.keysym.sym == SDLK_LEFT){
            input.left = false;
        }
        if(event.key.keysym.sym == SDLK_UP){
            input.jump = false;
        }
        if(event.key.keysym.sym == SDLK_DOWN && status == "big" && !can_crouch){
            input.crouch = false;
            size = {TILE_SIZE,TILE_SIZE*2};
            position.y -= TILE_SIZE; 
            can_crouch = true;

        }
    }
}

void Character::update(Stage &stage){
    if(!is_dead && !clear_stage){
        time_left = MAX_TIME - (SDL_GetTicks()/1000);
        if(time_left <= 0){
            time_left = 0;
            Mix_HaltMusic();
            Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/running_oot.wav"), 0);
            die();
        }
    }
    velocity.x = 0;
    velocity.y += GRAVITY;

    //free fall
    if(velocity.y >= MAX_FALL_SPEED) velocity.y = MAX_FALL_SPEED;
    
    //go right
    if(input.right && !is_dead){
        velocity.x += acceleration;
    }

    //go left
    if(input.left && !is_dead){
        velocity.x -= acceleration;
    }

    //jump
    if(input.jump && on_ground && !input.crouch && !is_dead){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/jump.wav"), 0);
        on_ground = false;
        velocity.y = -sqrtf(2.0f*GRAVITY*(JUMP_HEIGHT));
    }

    else if(input.crouch && can_crouch){
        size = {TILE_SIZE,TILE_SIZE};
        position.y += TILE_SIZE; 
    }

    //being invincible
    if(invincible){
        invincible_time--;
        if(invincible_time == 0){
            invincible_time = INVINCIBLE_TIME;
            acceleration = ACCELERATION;
            invincible = false;
        }
        // std::cout<<invincible_time<<std::endl;
    }

    check_collision(stage);
    follow(stage);
}

void Character::check_collision(Stage &stage){
    //setup corners' tile_coordinates    
    int x1(0), x2(0);
    int y1(0), y2(0);

    x1 = (position.x + velocity.x + stage.start.x)/TILE_SIZE;
    x2 = (position.x + velocity.x + size.x-1 + stage.start.x)/TILE_SIZE;

    y1 = (position.y)/TILE_SIZE;
    y2 = (position.y + size.y - 1)/TILE_SIZE;

    //check horizontal
    //check right collision
    if(velocity.x > 0){
        if(is_hit(stage.map_data[y1][x2]) || is_hit(stage.map_data[y2][x2]) || is_hit(stage.map_data[(y2+y1)/2][x2])){
            position.x = (x1)*TILE_SIZE-stage.start.x;
            velocity.x = 0;
        }
        if(x1 == 202){
            for(int i = 0; i < 4; i++){
                stage.map_data[14][x1+i] = 0;
                stage.map_data[15][x1+i] = 0;
            }
        }
    }
    //check left collision
    else if(velocity.x < 0){
        if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y2][x1]) || is_hit(stage.map_data[(y2+y1)/2][x1])){
            position.x = (x1+1)*TILE_SIZE-stage.start.x;
            velocity.x = 0;
        }
    }

    x1 = (position.x + stage.start.x)/TILE_SIZE;
    x2 = (position.x + size.x-1 + stage.start.x)/TILE_SIZE;

    y1 = (position.y + velocity.y)/TILE_SIZE;
    y2 = (position.y + size.y + velocity.y-1)/TILE_SIZE;

    //check vertical
    //check bottom collision
    if(velocity.y > 0 && !is_dead){
        if(is_hit(stage.map_data[y2][x1]) || is_hit(stage.map_data[y2][x2])){
            position.y = y1*TILE_SIZE;
            velocity.y = 0;
            on_ground = true;
            can_crouch = ~input.crouch & on_ground;
        }
        if(position.y > (13.5)*TILE_SIZE) {
            die();
        }
    }
    //check top collision
    else if(velocity.y < 0 && !is_dead){
        if(position.y + size.y < 0) {
            die();
        }
        else if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y1][x2])){
            position.y = (y1+1)*TILE_SIZE;
            velocity.y = 0;
            stage.tile_coord.x = is_hit(stage.map_data[y1][x1])? x1 : x2; 
            stage.tile_coord.y = y1;
            if(stage.map_data[stage.tile_coord.y][stage.tile_coord.x] == Tile::Question){
                stage.map_data[stage.tile_coord.y][stage.tile_coord.x] = Tile::Ques_Aft_Hit;
                hit_item = std::max(rand()%12-5, 0);
                if((hit_item == 1 || hit_item == 2 || hit_item == 3) && status == "big"){
                    hit_item = 6;
                }
                item_spawn_pos = stage.tile_coord; 
            }
            if(stage.map_data[stage.tile_coord.y][stage.tile_coord.x] == Tile::Wall){
                hit_item = rand()%7;
                if(hit_item != 6){
                    hit_item = 0;
                }
                item_spawn_pos = stage.tile_coord; 
            }
            if(status == "big" && stage.map_data[stage.tile_coord.y][stage.tile_coord.x] == Tile::Wall){
                stage.map_data[stage.tile_coord.y][stage.tile_coord.x] = Tile::Empty;
                Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/brick_smash.wav"), 0);
                sco_mana.score_increase = 200 + 50*(rand()%5);
            }

            stage.tile_value = stage.map_data[stage.tile_coord.y][stage.tile_coord.x];
        }
    }

    score += sco_mana.score_increase;

    if(sco_mana.score_increase > 0){
        sco_mana.item_score.set_position({position.x + 45, position.y - 45});
    }

    position.x += velocity.x;
    position.y += velocity.y;

    //check window borders
    if(position.x + velocity.x <= 0){
        velocity.x = 0;
        position.x = 0;
    }
    if(position.x + size.x + velocity.x >= WINDOW_WIDTH){
        velocity.x = 0;
        position.x = WINDOW_WIDTH - size.x; 
    }
}

bool Character::is_hit(int &map_element){
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::Mountain && map_element != Tile::Castle){
        return true;
    }
    return false;
}

void Character::follow(Stage &stage){
    if(stage.start.x != (stage.max.x - WINDOW_WIDTH) && position.x >= (WINDOW_WIDTH/4) && input.right){
        position.x = WINDOW_WIDTH/4;
        stage.start.x += velocity.x;
        // std::cout<<stage.start.x<<std::endl;
    }
    else if(stage.start.x != 0 && position.x <= (WINDOW_WIDTH/4) && input.left){
        position.x = WINDOW_WIDTH/4;
        stage.start.x += velocity.x;
        // std::cout<<stage.start.x<<std::endl;
    }
    if(stage.start.x <= 0){
        stage.start.x = 0;
    }
    else if(stage.start.x + WINDOW_WIDTH >= stage.max.x){
        stage.start.x = stage.max.x - WINDOW_WIDTH;
    }
}

void Character::die(){
    is_dead = true;
    input.right = false;
    input.left = false;
    input.jump = false;       
    size.y = 45;
    velocity.x = 0;
    velocity.y = -sqrtf(2.0f*GRAVITY*JUMP_HEIGHT);
    Mix_PlayChannel(-1,Mix_LoadWAV("res/sound/mario_die.wav"),0);
    Mix_HaltMusic();
    free();
}

void Character::power_up(){
    position.y -= 45;
    size.y = 90;
    status = "big";
    set_frame();
}

void Character::normalize(){
    Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/power_down.wav"), 0);
    position.y += 45;
    size.y = 45;
    status = "normal";
    set_frame();
}

void Character::set_velocity(Vector2f velocity){
    this->velocity = velocity;
}
