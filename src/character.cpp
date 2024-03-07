#include<character.h>

Character::Character(){
    frame = 0;
    position = {0,0};
    velocity = {0,0};
    frame_size = {0,0};
    face_right = true;
    input.right = false;
    input.left = false;
    input.jump = false;

}

Character::~Character(){}

SDL_Texture* Character::load_texture(SDL_Renderer* &renderer, std::string filename){
    frame_size = {45,45}; 
    return Entity::load_texture(renderer,filename); 
}
void Character::set_frame(){
    if(frame_size.x > 0 && frame_size.y > 0){
        for(int i = 0; i < 4; i++){
            frames[i].x = i*frame_size.x;
            frames[i].y = 0;
            frames[i].w = frame_size.x;
            frames[i].h = frame_size.y;
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

    // body.set_position(position);

    SDL_Rect* curr_frame = &frames[frame];
    SDL_Rect dest = {position.x, position.y, frame_size.x, frame_size.y}; 

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
    }
    else if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_RIGHT){
            input.right = false;
        }
        if(event.key.keysym.sym == SDLK_LEFT){
            input.left = false;
        }
    }
}
void Character::update(Stage &stage){
    velocity.x = 0;
    velocity.y += GRAVITY;

    if(velocity.y >= MAX_FALL_SPEED){
        velocity.y = MAX_FALL_SPEED;
    }

    if(input.right){
        velocity.x += SPEED;
    }
    else if(input.left){
        velocity.x -= SPEED;
    }
}
void Character::check_collision(Stage &stage){
    Vector2i left = {0,0}, right = {0,0};

    //check horizontal
    int height_min = std::min(frame_size.y, TILE_SIZE);

    left.x = (position.x + velocity.x)/TILE_SIZE;
    right.x = (position.x + velocity.x + frame_size.x - 1)/TILE_SIZE;
    
    left.y = (position.y)/TILE_SIZE;
    right.y = (position.y + height_min - 1)/TILE_SIZE;

    if(left.x >= 0 && right.x < MAP_WIDTH && left.y >= 0 &&  right.y < MAP_HEIGHT){
        //check right collision
        if(velocity.x > 0){
            if(stage.map_data[left.y][right.x] != Tile::Empty || stage.map_data[right.y][right.x] != Tile::Empty){
                velocity.x = right.x*TILE_SIZE - frame_size.x + 1;
                velocity.x = 0;
            }
        }
    }  
}

