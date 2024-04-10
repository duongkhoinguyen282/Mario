#include<mushroom.h>

Mushroom::Mushroom(){
    position = {0,0};
    velocity = {0,0};
    size = {45,45};
    map_x = 0;
    map_y = 0;
}

Mushroom::~Mushroom(){}

void Mushroom::draw(SDL_Renderer *&renderer){
    free();
    //load mushroom texture
    texture = load_texture(renderer, "res/image/" + type +"_mushroom.png");

    //mario ate mushroom
    if(is_eaten) {
        free();
    }

    if(spawning || spawned){
        render_pos.x = position.x - map_x;
        render_pos.y = position.y - map_y;

        SDL_Rect dest = {render_pos.x, render_pos.y, size.x, size.y}; 

        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }
}

void Mushroom::update(Stage &stage, Character &player){
    if(player.hit_mushroom > 0){
        switch (player.hit_mushroom){
        case 1:
        case 2:
        case 3:
            type = "magic";
            break;
        case 4:
            type = "1_up";
            break;
        default:
            break;
        }
        velocity = {0,0};
        spawned = false;
        // std::cout<<stage.tile_coord.y<<" "<<stage.tile_coord.x<<std::endl;
        is_eaten = false;
        position.x = player.mushroom_spawn_pos.x*TILE_SIZE;
        position.y = player.mushroom_spawn_pos.y*TILE_SIZE;
        player.hit_mushroom = false;
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

    //always go right after being spawned
    if(!is_eaten && velocity.x == 0 && spawned) velocity.x = MUSHROOM_SPEED;
    if(is_eaten) {
        velocity = {0,0};
        spawned = false;
        spawning = false;
        position = {0,0};
    }

    //free fall
    if(spawned){
        velocity.y += GRAVITY;
        if(velocity.y >= MAX_FALL_SPEED) velocity.y = MAX_FALL_SPEED;
    }

    check_collision(stage, player);
    get_camera(stage);
}

void Mushroom::check_collision(Stage &stage, Character &player){
    //setup corners' coordinates    
    int x1(0), x2(0);
    int y1(0), y2(0);
    
    x1 = (position.x + velocity.x)/TILE_SIZE;
    x2 = (position.x + velocity.x + size.x-1)/TILE_SIZE;

    y1 = (position.y)/TILE_SIZE;
    y2 = (position.y + size.y - 1)/TILE_SIZE;

    //check horizontal
    if(is_hit(player)){
        is_eaten = true;
        player.invincible = true;
        if(type == "magic"){
            player.power_up();
            player.score += 1000;
        }
        else if(type == "1_up"){
            player.lives++;
        }
    }
    //check right collision
    else if(velocity.x > 0){
        if(is_hit(stage.map_data[y1][x2]) || is_hit(stage.map_data[y2][x2]) || position.x + size.x >= MAP_WIDTH*TILE_SIZE){
            velocity.x *= -1;
        }
    }
    //check left collision
    else if(velocity.x < 0){
        if(is_hit(stage.map_data[y1][x1]) || is_hit(stage.map_data[y2][x1]) || position.x <= 0){
            velocity.x *= -1;
        }
    }

    x1 = (position.x)/TILE_SIZE;
    x2 = (position.x + size.x-1)/TILE_SIZE;

    y1 = (position.y + velocity.y)/TILE_SIZE;
    y2 = (position.y + size.y + velocity.y-1)/TILE_SIZE;

    //check vertical
    //check bottom collision
    if(velocity.y > 0 && !is_eaten && spawned){
        if(is_hit(stage.map_data[y2][x1]) || is_hit(stage.map_data[y2][x2])){
            position.y = y1*TILE_SIZE;
            velocity.y = 0;
        }
        if(position.y >= (13.5)*TILE_SIZE) {
            is_eaten = true;
        }
    }

    position.x += velocity.x;
    position.y += velocity.y;
}

bool Mushroom::is_hit(int &map_element){
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::Mountain && map_element != Tile::Castle){
        return true;
    }
    return false;
}

bool Mushroom::is_hit(Character &player){
    if((((position.x + size.x >= player.get_position().x + map_x) && (position.x < player.get_position().x + map_x)) 
    || ((position.x <= player.get_position().x + map_x + player.get_size().x) && (position.x > player.get_position().x + map_x)))
    && ((position.y < player.get_position().y + player.get_size().y) && (position.y >= player.get_position().y))) {
        return true;
    }
    return false;
}