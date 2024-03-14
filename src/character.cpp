#include<character.h>

Character::Character(){
    frame = 0;
    real_pos = {0,0};
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    face_right = true;
    input.right = false;
    input.left = false;
    input.jump = false;
    map_x = 0;
    map_y = 0;
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
    //load mario texture
    if(face_right){
        texture = load_texture(renderer,"res/image/mario_right.png");
    }
    else{
        texture = load_texture(renderer,"res/image/mario_left.png");
    }
    //mario jump
    if(input.jump){
        frame = 4;
    }
    //mario walk
    else if((input.left && !input.right) || (input.right && !input.left)){
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

    SDL_Rect* curr_frame = &frames[frame];
    SDL_Rect dest = {position.x, position.y, size.x, size.y}; 

    SDL_RenderCopy(renderer, texture, curr_frame, &dest);
}
void Character::handle_input(SDL_Renderer* &renderer, SDL_Event event){
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
    }
}
void Character::update(Stage &stage){
    velocity.x = 0;
    velocity.y += GRAVITY;

    if(velocity.y >= MAX_FALL_SPEED) velocity.y = MAX_FALL_SPEED;
    
    if(input.right){
        velocity.x += ACCELERATION;
    }
    if(input.left){
        velocity.x -= ACCELERATION;
    }
    if(input.jump && on_ground){
        on_ground = false;
        velocity.y = -sqrtf(2.0f*GRAVITY*(JUMP_HEIGHT));
    }

    check_collision(stage);
    follow(stage);
}
void Character::check_collision(Stage &stage){
    //setup corners' coordinates    
    int x1(0), x2(0);
    int y1(0), y2(0);

    x1 = (position.x + velocity.x + stage.start.x)/TILE_SIZE;
    x2 = (position.x + velocity.x + size.x-1 + stage.start.x)/TILE_SIZE;

    y1 = (position.y)/TILE_SIZE;
    y2 = (position.y + size.y - 1)/TILE_SIZE;

    //check horizontal
    //check right collision
    if(velocity.x > 0){
        if(is_hit(stage.map_data[y1][x2]) || is_hit(stage.map_data[y2][x2])){
            // position.x = (x1-stage.start.x)*TILE_SIZE;
            velocity.x = 0;
        }
    }
    //check left collision
    else if(velocity.x < 0){
        if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y2][x1])){
            // position.x = (x1+1-stage.start.x)*TILE_SIZE;
            velocity.x = 0;
        }
    }

    x1 = (position.x + stage.start.x)/TILE_SIZE;
    x2 = (position.x + size.x-1 + stage.start.x)/TILE_SIZE;

    y1 = (position.y + velocity.y)/TILE_SIZE;
    y2 = (position.y + size.y + velocity.y-1)/TILE_SIZE;

    //check vertical
    //check bottom collision
    if(velocity.y > 0){
        if(is_hit(stage.map_data[y2][x1]) || is_hit(stage.map_data[y2][x2])){
            position.y = y1*TILE_SIZE;
            velocity.y = 0;
            on_ground = true;
            std::cout<<"y2: "<<y2+1<<" x1: "<<x1+1<<std::endl;
            std::cout<<"y2: "<<y2+1<<" x2: "<<x2+1<<std::endl;
        }
    }
    //check top collision
    else if(velocity.y < 0){
        if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y1][x2])){
            position.y = (y1+1)*TILE_SIZE;
            velocity.y = 0;
        }
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
bool Character::is_hit(int map_element){
    if(map_element == Tile::Question){
        map_element = 0;
        return true;
    }
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::B_Mountain && map_element != Tile::S_Mountain){
        return true;
    }
    return false;
}
void Character::set_camera(int &map_x, int &map_y){
    this->map_x = map_x;
    this->map_y = map_y;

}
void Character::follow(Stage &stage){
    if(stage.start.x != (stage.max.x - WINDOW_WIDTH) && position.x >= (WINDOW_WIDTH/2) && input.right){
        position.x = WINDOW_WIDTH/2;
        stage.start.x += velocity.x;
        // std::cout<<stage.start.x<<std::endl;
    }
    else if(stage.start.x != 0 && position.x <= (WINDOW_WIDTH/2) && input.left){
        position.x = WINDOW_WIDTH/2;
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
void Character::power_up(Stage &stage, int y1, int x1, int x2){
    if(stage.map_data[y1][x1] == Tile::Wall || stage.map_data[y1][x2] == Tile::Wall){
        stage.set_element(y1,x1,0);
        stage.set_element(y1,x2,0);
    }
}