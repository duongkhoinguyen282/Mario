#include<enemy.h>

Enemy::Enemy(){

}

Enemy::~Enemy(){}


void Enemy::get_camera(const Stage &stage){
    map_x = stage.start.x;
    map_y = stage.start.y;
}

