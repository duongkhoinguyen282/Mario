#ifndef MAP_H
#define MAP_H

#include<structs.h>
#include<entity.h>
#include<render_window.h>
#include<fstream>

class Map{
public:
    Map();
    ~Map();
    void load_map(std::string filename);
    void load_tiles(SDL_Renderer* &renderer);
    void draw_map(SDL_Renderer* &renderer);
    Stage get_stage();
private:
    Stage stage;
    Entity tiles[MAX_TILES];
};

#endif