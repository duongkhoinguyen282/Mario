#ifndef MAIN_H
#define MAIN_H

#include<render_window.h>
#include<ctime>
#include<timer.h>
#include<goomba.h>
#include<mushroom.h>
#include<starman.h>
#include<coin.h>
#include<flag.h>
#include<menu.h>
#include<text.h>

bool is_open = true;

void run_game(){
    srand(time(0));

	//init timer
	Timer timer;
	int elapsed_time = 0;
	int time_per_frame = 0;

	//init window
	SDL_Window* window; SDL_Renderer* renderer;
    init_SDL(window, renderer);

	//init menu
	Menu menu;

	//init map
	Map map0; map0.load_map("res/map/map.dat"); map0.load_tiles(renderer);
	Stage stage0 = map0.get_stage();

	//init player
	Character mario;

	//init goombas
	Goomba* goombas = goombas->spawn();

	//init items
	Mushroom mushroom;
	Starman starman;
	Coin coin;
	Flag flag;

	//init theme music
	Mix_Music* music;
    music = Mix_LoadMUS("res/sound/theme_song.wav");
	Mix_PlayMusic(music, -1);

	//init texts
	TTF_Font* font = TTF_OpenFont("fonts/joystix monospace.otf",28);
	SDL_Color color = {255,255,255};
    Text name;
	name.set_text("MARIO         WORLD  TIME"); name.set_position({67,20});
	name.write_text(renderer,font,color);

    Text score;	score.set_position({67,45}); 
    
	Text coin_num; coin_num.set_position({263,45});
	Entity coin_sym({231,50}, {25,25}, coin_sym.load_texture(renderer, "res/image/coin.png"));

	Text lives_num; lives_num.set_position({263,20}); 
	Entity mario_sym({230,22}, {26,26}, mario_sym.load_texture(renderer, "res/image/mario_idle.png"));

	Text time_left;
    time_left.set_position({572,45}); time_left.write_text(renderer,font,color);

	//animation loop
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
			// if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN){ 
            //     event.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
			// 	SDL_GL_SwapWindow(window);
            // }
			
			mario.handle_input(event);
		}

		//clear and render
		SDL_RenderClear(renderer);
		// mario.invincible = true;

		// flag.update(stage0, mario); flag.draw(renderer);

		// if(mushroom.get_spawning() || starman.get_spawning() || coin.get_spawning()){
		// 	mushroom.update(stage0, mario); mushroom.draw(renderer);
		// 	starman.update(stage0, mario); starman.draw(renderer);
		// 	coin.update(stage0, mario); coin.draw(renderer);
		// 	map0.draw_map(renderer,stage0);
		// }
		// else{
		// 	map0.draw_map(renderer,stage0);
		// 	mushroom.update(stage0, mario); mushroom.draw(renderer);
		// 	starman.update(stage0, mario); starman.draw(renderer);
		// 	coin.update(stage0, mario); coin.draw(renderer);
		// }
		
		// goombas->update_and_draw(renderer, stage0, goombas, mario);
		
		// mario.update(stage0); mario.draw(renderer);

		// mario.sco_mana.item_score.render(renderer);

        // //render texts
		// //render name and num of score
		// name.render(renderer);
        // std::string score_val;
        // (mario.score == 0) ? (score_val = "000000") : (score_val = std::string(5-(int)log10(mario.score), '0') + std::to_string(mario.score));
        // score.set_text(score_val + "         1-1"); 
        // score.write_text(renderer,font,color);
        // score.render(renderer);
		// mario_sym.draw(renderer); 

		// //render num of coins
		// std::string coin_val;
        // (mario.coin == 0) ? (coin_val = "00") : (coin_val = std::string(1-(int)log10(mario.coin), '0') + std::to_string(mario.coin));
        // coin_num.set_text("x" + coin_val); 
        // coin_num.write_text(renderer,font,color);
        // coin_num.render(renderer); 
		// coin_sym.draw(renderer);

		// //render num of lives
		// std::string lives_val;
        // (mario.lives == 0) ? (lives_val = "00") : (lives_val = std::string(1-(int)log10(mario.lives), '0') + std::to_string(mario.lives));
        // lives_num.set_text("x" + lives_val); 
        // lives_num.write_text(renderer,font,color);
        // lives_num.render(renderer); 
		// mario_sym.draw(renderer);

		// //render time left
		// time_left.set_text(std::to_string(mario.time_left));
        // time_left.write_text(renderer,font,color);
        // time_left.render(renderer); 

		menu.render(renderer);

        SDL_RenderPresent(renderer);

		elapsed_time = timer.get_ticks();
		time_per_frame = 1000/FPS;

		if(elapsed_time < time_per_frame){
			int delay_time = time_per_frame - elapsed_time;
			if(delay_time > 0) SDL_Delay(delay_time);
		}
	}
	Mix_HaltMusic();
	TTF_CloseFont(font);

	//destroy and quit
	quit_SDL(window,renderer);
}

#endif