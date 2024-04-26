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
    int px1 = player.get_position().x + map_x;
    int px2 = player.get_position().x + player.get_size().x + map_x; 
    int py1 = player.get_position().y;
    int py2 = player.get_position().y + player.get_size().y; 

    int ix1 = position.x;
    int ix2 = position.x + size.x; 
    int iy1 = position.y;
    int iy2 = position.y + size.y; 

    // if(((px2 >= ix1 && px2 <= ix2) || (px1 >= ix1 && px1 <= ix2))
    // && ((py2 >= iy1 && py2 <= iy2) || (py1 >= iy1 && py1 <= iy2))) {
    //     return true;
    // }

    if((((ix2 >= px1) && (ix1 <= px1)) || ((ix1 <= px2) && (ix1 >= px1)))
    && (((iy1 <= py2) && (iy1 >= py1)) || ((iy2 >= py1) && (iy1 <= py1)))) {
        return true;
    }

    return false;
}