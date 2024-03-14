#include<render_window.h>

void log_SDL_error(std::ostream &os, const std::string &msg, bool fatal){
    os<<msg<<"Error: "<<SDL_GetError()<<std::endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}
void init_SDL(SDL_Window* &window, SDL_Renderer* &renderer){
    if(SDL_Init(SDL_INIT_EVERYTHING)!= 0) {
        log_SDL_error(std::cout,"SDL init failed!",true);
    }
    
    window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if(window == nullptr) log_SDL_error(std::cout, "Creating window failed!", true);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) log_SDL_error(std::cout, "Creating renderer failed!", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderDrawColor(renderer, BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], 255);
}   
void quit_SDL(SDL_Window* &window, SDL_Renderer* &renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void SDL_RenderEntity(SDL_Renderer* &renderer, Entity &entity){
    SDL_Rect block;
    block.w = entity.get_size().x*TILE_SIZE; block.h = entity.get_size().y*TILE_SIZE;
    block.x = entity.get_position().x; block.y = entity.get_position().y;
    SDL_RenderCopy(renderer, entity.get_texture(), nullptr, &block);
}
