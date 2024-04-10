#include<main.h>

bool is_open = true;
int lives = 0;
int score = -1;

int main(int argc, char *argv[]){
	srand(time(0));

	Timer timer;
	int elapsed_time = 0;
	int time_per_frame = 0;

	//init window
	SDL_Window* window; SDL_Renderer* renderer;
    init_SDL(window, renderer);

	//init map
	Map map0; map0.load_map("res/map/map.dat"); map0.load_tiles(renderer);
	Stage stage0 = map0.get_stage();

	//init player
	Character mario;

	//init goombas
	Goomba* goombas = goombas->spawn();

	//init mushroom
	Mushroom mushroom;

	// animation loop
	while (is_open) {
		timer.start();
		// Events management
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if((event.key.keysym.sym == SDLK_LALT && event.key.keysym.sym == SDLK_F4 && event.type == SDL_KEYDOWN) 
            || event.type == SDL_QUIT){ 
                is_open = false;
                break;
            }
			else if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN){ 
                system("PAUSE");
            }
			mario.handle_input(event);
		}

		// clear and render
		SDL_RenderClear(renderer);

		if(mushroom.get_spawning()){
			mushroom.update(stage0, mario); mushroom.draw(renderer);
			map0.draw_map(renderer,stage0);
		}
		else{
			map0.draw_map(renderer,stage0);
			mushroom.update(stage0, mario); mushroom.draw(renderer);
		}
		
		goombas->update_and_draw(renderer, stage0, goombas, mario);
		
		mario.update(stage0); mario.draw(renderer);
		if(lives != mario.lives){
			std::cout<<"Lives: "<<mario.lives<<std::endl;
			lives = mario.lives;
		}
		if(score != mario.score){
			std::cout<<"Score: "<<mario.score<<std::endl;
			score = mario.score;
		}
			
		SDL_RenderPresent(renderer);

		elapsed_time = timer.get_ticks();
		time_per_frame = 1000/FPS;

		if(elapsed_time < time_per_frame){
			int delay_time = time_per_frame - elapsed_time;
			if(delay_time > 0) SDL_Delay(delay_time);
		}
	}

	//destroy and quit
	quit_SDL(window,renderer);

	return 0;
}
