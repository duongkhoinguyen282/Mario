#include<main.h>

bool is_open = true;

int main(int argc, char *argv[]){
	srand(time(0));

	//init window
	SDL_Window* window; SDL_Renderer* renderer;
    init_SDL(window, renderer);

	// SDL_Texture* mario = IMG_LoadTexture(renderer, "res/image/mario_right.png");
	// Animation ani(mario, {3,1}, 0.3f);

	// float delta_time = 0;

	//init map
	Map map0; map0.load_map("res/map/map.dat"); map0.load_tiles(renderer);
	// std::cout<<map0.get_stage().map_data[0][0]<<std::endl;
	// std::cout<<"abc";

	//init player
	Character mario;
	mario.load_texture(renderer, "res/image/mario_right.png");
	mario.set_frame();

	// animation loop
	while (is_open) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			if((event.key.keysym.sym == SDLK_LALT && event.key.keysym.sym == SDLK_F4 && event.type == SDL_KEYDOWN) 
            || event.type == SDL_QUIT){ 
                is_open=false;
                break;
            }
			mario.handle_input(renderer, event);
		}

		// clear and render
		SDL_RenderClear(renderer);
		map0.draw_map(renderer);
		mario.update(map0);
		mario.draw(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 25);
	}

	//destroy and quit
	quit_SDL(window,renderer);

	return 0;
}
