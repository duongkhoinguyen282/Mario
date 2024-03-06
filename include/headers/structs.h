#ifndef STRUCTS_H
#define STRUCTS_H

#include<defs.h>

struct Vector2f{
    Vector2f(){
        x=0; y =0;
    }
    Vector2f(float x, float y){
        this->x = x; this->y = y;
    }
    float x,y;
};

struct Vector2i{
    Vector2i(){
        x=0; y =0;
    }
    Vector2i(int x, int y){
        this->x = x; this->y = y;
    }
    int x,y;
};

struct Stage{
    Vector2i start = {0,0};
    Vector2i max = {0,0};
    int map_data[MAP_HEIGHT][MAP_WIDTH];
    std::string filename;
};

struct Input{
    bool left = false;
    bool right = false;
    bool jump = false;
};

#endif