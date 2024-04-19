#include<items.h>

Items::Items(){}

Items::~Items(){}

bool Items::is_hit(int &map_element){
    if(map_element != Tile::Empty && map_element != Tile::Cloud && map_element != Tile::Grass
    && map_element != Tile::Mountain && map_element != Tile::Castle){
        return true;
    }
    return false;
}

bool Items::is_hit(Character &player){
    if((((position.x + size.x >= player.get_position().x + map_x) && (position.x < player.get_position().x + map_x)) 
    || ((position.x <= player.get_position().x + map_x + player.get_size().x) && (position.x > player.get_position().x + map_x)))
    && ((position.y < player.get_position().y + player.get_size().y) && (position.y >= player.get_position().y))) {
        return true;
    }
    return false;
}