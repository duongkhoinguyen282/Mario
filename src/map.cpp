#include<map.h>

Map::Map(){}
Map::~Map(){}

void Map::load_map(std::string filename){
    std::ifstream r_file(filename);
    if(!r_file){
        std::cout<<"Error!";
        return;
    }

    stage.max.x = 0;
    stage.max.y = 0;

    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j< MAP_WIDTH; j++){
            r_file>>stage.map_data[i][j];
            int value = stage.map_data[i][j];
            if(value>0){
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
    Entity ques_aft_hit = Entity({0,0}, ques_aft_hit.load_texture(renderer, "res/image/ques_aft_hit.png"));
    Entity block = Entity({0,0}, block.load_texture(renderer, "res/image/block.png"));
    Entity cloud = Entity({0,0}, {90,90}, cloud.load_texture(renderer, "res/image/cloud.png"));
    Entity grass = Entity({0,0}, {90,90}, grass.load_texture(renderer, "res/image/grass.png"));
    Entity mountain = Entity({0,0}, {225,135}, mountain.load_texture(renderer, "res/image/mountain.png"));
    Entity pipe = Entity({0,0}, {90,180}, pipe.load_texture(renderer, "res/image/pipe.png"));
    Entity castle = Entity({0,0}, {225,225}, castle.load_texture(renderer, "res/image/castle.png"));
    
    tiles[Tile::Empty] = Entity();
    tiles[Tile::Ground] = ground;
    tiles[Tile::Wall] = wall;
    tiles[Tile::Question] = question;
    tiles[Tile::Ques_Aft_Hit] = ques_aft_hit;
    tiles[Tile::Block] = block;
    tiles[Tile::Cloud] = cloud;
    tiles[Tile::Grass] = grass;
    tiles[Tile::Mountain] = mountain;
    tiles[Tile::Pipe] = pipe;
    tiles[Tile::Castle] = castle;

}

void Map::draw_map(SDL_Renderer* &renderer, Stage &stage){
    this -> stage = stage;
    int x1(0), x2(0);
    int y1(0), y2(0);

    int mx(0), my(0);

    mx = stage.start.x/TILE_SIZE;
    x1 = (stage.start.x %TILE_SIZE)*(-1);
    x2 = x1 + WINDOW_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    my = stage.start.y/TILE_SIZE;
    y1 = (stage.start.y %TILE_SIZE)*(-1);
    y2 = y1 + WINDOW_WIDTH + (y1 == 0 ? 0 : TILE_SIZE);
    
    for(int i = y1; i < y2; i+=TILE_SIZE){
        mx = stage.start.x/TILE_SIZE;
        for(int j = x1; j < x2; j+=TILE_SIZE){
            int value = stage.map_data[my][mx];
            if(value > 0){
                if(my == stage.tile_coord.y && mx == stage.tile_coord.x && value == stage.tile_value){
                    stage.hit = true;
                    stage.tile_coord = {-1,-1};   
                }
                tiles[value].set_position({j,i - stage.hit*20});
                tiles[value].draw(renderer);
                stage.hit = false;    
            }
            mx++;
        }
        my++;
    }
}

Stage Map::get_stage(){
    return stage;
}

void Map::set_stage(Stage &stage){
    this -> stage = stage;
}

void Map::set_element(int &map_data, int new_data){
    map_data = new_data;
}
