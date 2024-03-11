#include<main.h>

bool is_open = true;

int main(int argc, char *argv[]){
	srand(time(0));

	//init window
	SDL_Window* window; SDL_Renderer* renderer;
    init_SDL(window, renderer);

	//init map
	Map map0; map0.load_map("res/map/map.dat"); map0.load_tiles(renderer);

	//init player
	Character mario;	mario.set_frame();

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
			else if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN){ 
                system("PAUSE");
            }
			mario.handle_input(renderer, event);
		}

		// clear and render
		SDL_RenderClear(renderer);
		map0.draw_map(renderer);
		mario.update(map0);
		mario.draw(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 30);
	}

	//destroy and quit
	quit_SDL(window,renderer);

	return 0;
}
