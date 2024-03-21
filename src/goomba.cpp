#include<goomba.h>

Goomba::Goomba(){
    frame = 0;
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    face_left = true;
    spawn_time = 0;
    map_x = 0;
    map_y = 0;
    set_frame();
}

Goomba::~Goomba(){}

void Goomba::set_frame(){
    if(size.x > 0 && size.y > 0){
        for(int i = 0; i < GOOMBA_FRAMES; i++){
            frames[i].x = i*size.x;
            frames[i].y = 0;
            frames[i].w = size.x;
            frames[i].h = size.y;
        }
    }
}
void Goomba::draw(SDL_Renderer* &renderer) {
    //load goomba texture
    free();
    texture = load_texture(renderer, "res/image/goomba.png");
    //normal goomba
    if(!is_dead){
        frame++;
        if(frame >= 2) frame = 0;
    }
    //goomba die
    else {
        free();
        texture = load_texture(renderer, "res/image/goomba_die.png");
    }

    render_pos.x = position.x - map_x;
    render_pos.y = position.y - map_y;

    SDL_Rect* curr_frame = &frames[frame];
    SDL_Rect dest = {render_pos.x, render_pos.y, size.x, size.y}; 

    SDL_RenderCopy(renderer, texture, curr_frame, &dest);
}
void Goomba::update(Stage &stage, Goomba *&goombas, Character &player){
    if(is_dead) velocity.x = 0;
    else if(face_left) {
        velocity.x = -GOOMBA_SPEED;
    }
    else {
        velocity.x = GOOMBA_SPEED;
    }

    velocity.y += GRAVITY;
    if(velocity.y >= MAX_FALL_SPEED) velocity.y = MAX_FALL_SPEED;
    check_collision(stage, goombas, player);
    get_camera(stage);
}
void Goomba::check_collision(Stage &stage, Goomba* &goombas, Character &player){
    //setup corners' coordinates    
    int x1(0), x2(0);
    int y1(0), y2(0);
    //mario die
    if(horiz_hit(player) && !is_dead){
        player.die();
    }
    //goomba die
    else if(verti_hit(player) && !is_dead && !player.get_death()){
        die();
    }
    
    x1 = (position.x + velocity.x)/TILE_SIZE;
    x2 = (position.x + velocity.x + size.x-1)/TILE_SIZE;

    y1 = (position.y)/TILE_SIZE;
    y2 = (position.y + size.y - 1)/TILE_SIZE;

    //check horizontal
    //check right collision
    if(velocity.x > 0){
        if(is_hit(stage.map_data[y1][x2]) || is_hit(stage.map_data[y2][x2]) || position.x + size.x >= MAP_WIDTH*TILE_SIZE){
            velocity.x = 0;
            face_left = true;
        }
    }
    //check left collision
    else if(velocity.x < 0){
        if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y2][x1]) || position.x <= 0){
            velocity.x = 0;
            face_left = false;
        }
    }

    x1 = (position.x)/TILE_SIZE;
    x2 = (position.x + size.x-1)/TILE_SIZE;

    y1 = (position.y + velocity.y)/TILE_SIZE;
    y2 = (position.y + size.y + velocity.y-1)/TILE_SIZE;

    //check vertical
    //check bottom collision
    if(velocity.y > 0 && !is_dead){
        if(is_hit(stage.map_data[y2][x1]) || is_hit(stage.map_data[y2][x2])){
            position.y = y1*TILE_SIZE;
            velocity.y = 0;
            on_ground = true;
        }
        if(position.y >= (13.5)*TILE_SIZE) {
            die();
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
    if(position.y >= 721) position.y = 721;
}
bool Goomba::is_hit(int &map_element){
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::Mountain && map_element != Tile::Castle){
        return true;
    }
    return false;
}
bool Goomba::horiz_hit(Character &player){
    if(((position.x + size.x == player.get_position().x + map_x) || (position.x == player.get_position().x + map_x + player.get_size().x))
    && ((position.y < player.get_position().y + player.get_size().y) && (position.y >= player.get_position().y))) {
        return true;
    }
    return false;
}
bool Goomba::verti_hit(Character &player){
    if((player.get_position().y + player.get_size().y > position.y) && 
        (((player.get_position().x + map_x < position.x + size.x) && (player.get_position().x + map_x > position.x))
        || ((player.get_position().x + map_x + player.get_size().x < position.x + size.x) && (player.get_position().x + map_x + player.get_size().x > position.x)))){
        return true;
    }
    return false;
}
bool Goomba::is_hit_right(Goomba* &goombas){
    for(int i = 1; i < NUM_OF_GOOMBAS; i++){
        if(position.x + velocity.x + size.x == goombas[i].position.x + goombas[i].velocity.x){
            goombas[i].face_left = false;
            // std::cout<<position.x<<" "<<goombas[i].position.x<<std::endl<<std::endl;
            // std::cout<<"hit";
            return true;
        }
        else return false;
    }
    return false;
}
bool Goomba::is_hit_left(Goomba* &goombas){
    for(int i = 0; i < NUM_OF_GOOMBAS-1; i++){
        if(position.x + velocity.x == goombas[i].position.x + goombas[i].velocity.x + goombas[i].size.x){
            // std::cout<<"hit";
            return true;
        }
        else return false;
    }
    return false;
}
Goomba* Goomba::spawn(){
    int spawn_pos = 765;
    Goomba* goombas = new Goomba[NUM_OF_GOOMBAS];
    for(int i = 0; i < NUM_OF_GOOMBAS; i++){
		goombas[i] = Goomba();
		goombas[i].set_position({spawn_pos,0});
        spawn_pos += 720 + TILE_SIZE*(rand()%3); 
        if(spawn_pos >= 8730) spawn_pos = 8730;
	}
    return goombas;
}
void Goomba::update_and_draw(SDL_Renderer *&renderer, Stage &stage, Goomba *goombas, Character &player){
    for(int i = 0; i < NUM_OF_GOOMBAS; i++){
		goombas[i].update(stage, goombas, player);
		goombas[i].draw(renderer);
	}
}
void Goomba::die(){
    is_dead = true;
    velocity.x = 0;
    velocity.y = -sqrtf(2.0f*GRAVITY*(TILE_SIZE/2));
}
