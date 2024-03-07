#include<map.h>

Map::Map(){}
Map::~Map(){}

void Map::load_map(std::string filename){
    std::ifstream r_file(filename);
    if(!r_file){
        std::cout<<"Error!";
        return;
    }

    stage.max = {0,0};

    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j< MAP_WIDTH; j++){
            r_file>>stage.map_data[i][j];
            int val = stage.map_data[i][j];
            if(val>0){
                if(j>stage.max.x){
                    stage.max.x = j;
                }
                if(i>stage.max.y){
                    stage.max.y = i;
                }
            }
        }
    }
    stage.max.x = (stage.max.x+1)*TILE_SIZE;
    stage.max.y = (stage.max.y+1)*TILE_SIZE;
    stage.start.x = 0; stage.start.y = 0;
    stage.filename = filename;
}
void Map::load_tiles(SDL_Renderer* &renderer){
    Entity ground = Entity({0,0}, ground.load_texture(renderer, "res/image/ground.png"));
    Entity wall = Entity({0,0}, wall.load_texture(renderer, "res/image/wall.png"));
    Entity question = Entity({0,0}, question.load_texture(renderer, "res/image/question.png"));
    Entity block = Entity({0,0}, block.load_texture(renderer, "res/image/block.png"));
    Entity cloud = Entity({0,0}, {90,90}, cloud.load_texture(renderer, "res/image/cloud.png"));
    Entity grass = Entity({0,0}, {90,90}, grass.load_texture(renderer, "res/image/grass.png"));
    Entity b_mount = Entity({0,0}, {225,135}, b_mount.load_texture(renderer, "res/image/b_mountain.png"));
    Entity s_mount = Entity({0,0}, {135,90}, s_mount.load_texture(renderer, "res/image/s_mountain.png"));
    Entity castle = Entity({0,0}, {225,225}, castle.load_texture(renderer, "res/image/castle.png"));
    
    tiles[Tile::Empty] = Entity();
    tiles[Tile::Ground] = ground;
    tiles[Tile::Wall] = wall;
    tiles[Tile::Question] = question;
    tiles[Tile::Block] = block;
    tiles[Tile::Cloud] = cloud;
    tiles[Tile::Grass] = grass;
    tiles[Tile::B_Mountain] = b_mount;
    tiles[Tile::S_Mountain] = s_mount;    
    tiles[Tile::Castle] = castle;

}
void Map::draw_map(SDL_Renderer* &renderer){
    int x1(0), x2(0);
    int y1(0), y2(0);

    int map_x(0), map_y(0);

    map_x = stage.start.x/TILE_SIZE;
    x1 = (stage.start.x %TILE_SIZE)*(-1);
    x2 = x1 + WINDOW_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = stage.start.y/TILE_SIZE;
    y1 = (stage.start.y %TILE_SIZE)*(-1);
    y2 = y1 + WINDOW_WIDTH + (y1 == 0 ? 0 : TILE_SIZE);
    
    for(int i = y1; i < y2; i+=TILE_SIZE){
        map_x = stage.start.x/TILE_SIZE;
        for(int j = x1; j < x2; j+=TILE_SIZE){
            int val = stage.map_data[map_y][map_x];
            if(val > 0){
                tiles[val].set_position({j,i});
                SDL_RenderEntity(renderer, tiles[val]);
            }
            map_x++;
        }
        map_y++;
    }
}
Stage Map::get_stage(){
    return stage;
}