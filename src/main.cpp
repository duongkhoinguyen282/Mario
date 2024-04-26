#include<main.h>

int main(int argc, char *argv[]){
	srand(time(0));

	//init window
	SDL_Window* window; SDL_Renderer* renderer;
    init_SDL(window, renderer);

	bool play_again = false;

	do{
		Game game;
		play_again = false;
		game.run(window, renderer);
		play_again = game.play_again;
		game.play_again = false;
	}while(play_again);

	//destroy and quit
	quit_SDL(window,renderer);

	return 0;
}
