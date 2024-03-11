#include<character.h>

Character::Character(){
    frame = 0;
    position = {0,0};
    velocity = {0,0};
    size = {0,0};
    face_right = true;
    input.right = false;
    input.left = false;
    input.jump = false;

}

Character::~Character(){}

SDL_Texture* Character::load_texture(SDL_Renderer* &renderer, std::string filename){
    size = {45,45}; 
    return Entity::load_texture(renderer,filename); 
}
void Character::set_frame(){
    if(size.x > 0 && size.y > 0){
        for(int i = 0; i < 4; i++){
            frames[i].x = i*size.x;
            frames[i].y = 0;
            frames[i].w = size.x;
            frames[i].h = size.y;
        }
    }
}
void Character::draw(SDL_Renderer* &renderer){
    if(face_right){
        texture = load_texture(renderer,"res/image/mario_right.png");
    }
    else{
        texture = load_texture(renderer,"res/image/mario_left.png");
    }
    if(input.left == true || input.right == true){
        frame++;
    }
    else{
        frame = 0;
    }
    if(frame >= 4) frame = 1;

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
void Character::update(Map &map){
    velocity.x = 0;
    velocity.y += GRAVITY;

    if(velocity.y >= MAX_FALL_SPEED) velocity.y = MAX_FALL_SPEED;
    
    if(input.right){
        velocity.x += SPEED;
    }
    if(input.left){
        velocity.x -= SPEED;
    }
    if(input.jump && can_jump){
        can_jump = false;
        velocity.y = -sqrtf(2.0f*GRAVITY*(TILE_SIZE));
    }

    check_collision(map);

}
void Character::check_collision(Map &map){
    //setup corners' coordinates    
    int x1(0), x2(0);
    int y1(0), y2(0);

    x1 = (position.x + velocity.x)/TILE_SIZE;
    x2 = (position.x + velocity.x + size.x-1)/TILE_SIZE;

    y1 = (position.y)/TILE_SIZE;
    y2 = (position.y + size.y - 1)/TILE_SIZE;

    //check horizontal
    //check right collision
    if(velocity.x > 0){
        if(is_hit(map.get_stage().map_data[y1][x2]) || is_hit(map.get_stage().map_data[y2][x2])){
            position.x = x1*TILE_SIZE;
            velocity.x = 0;
        }
    }
    //check left collision
    else if(velocity.x < 0){
        if(is_hit(map.get_stage().map_data[y1][x1]) || is_hit(map.get_stage().map_data[y2][x1])){
            position.x = (x1+1)*TILE_SIZE;
            velocity.x = 0;
        }
    }

    x1 = (position.x)/TILE_SIZE;
    x2 = (position.x + size.x - 1)/TILE_SIZE;

    y1 = (position.y + velocity.y)/TILE_SIZE;
    y2 = (position.y + size.y + velocity.y-1)/TILE_SIZE;

    //check vertical
    //check bottom collision
    if(velocity.y > 0){
        if(is_hit(map.get_stage().map_data[y2][x1]) || is_hit(map.get_stage().map_data[y2][x2])){
            position.y = y1*TILE_SIZE;
            velocity.y = 0;
            can_jump = true;
        }
    }
    //check top collision
    else if(velocity.y < 0){
        if(is_hit(map.get_stage().map_data[y1][x1]) || is_hit(map.get_stage().map_data[y1][x2])){
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
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::B_Mountain && map_element != Tile::S_Mountain){
        return true;
    }
    return false;
}
void Character::follow(const int map_x, const int map_y){
    this->map_x = map_x;
    this->map_y = map_y;
}