#include<game.h>

Game::Game(){}

Game::~Game(){}

void Game::run(SDL_Window* &window, SDL_Renderer* &renderer){
    this->window = window;
    this->renderer = renderer;

    //set map
    set_map();

	//init player
	Character player;

    //spawn goombas
    goombas = goombas->spawn();

	//set theme music
    set_music();

    //set font
    font = TTF_OpenFont("fonts/joystix monospace.otf",28);

    //set name and score
    set_name_and_score();

    //set "WORLD" and "TIME"
    set_world_and_time();
    
    //set world level
    set_world_level();

    //set coin counter
    coin_counter();

    //set lives counter
    lives_counter();

    //set time counter
    time_counter();

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
			if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN && menu.game_run){ 
				menu.is_paused = true;
            }

			if(!menu.game_run || menu.is_paused){
				menu.handle_input(event);
			}
			else{
				player.handle_input(event);
			}
		}

		//clear and render
		SDL_RenderClear(renderer);
		
		if(!menu.game_run || menu.is_paused){
            count_down.pause();
            set_menu(player);
            if(menu.play_again) {
                play_again = true;
                menu.play_again = false;
                is_open = false;
                delete [] goombas;
            }
		}

		else{
            game_loop(player);
            menu.free();
            if(player.get_position().y >= 1500) {
                menu.game_run = false;
                menu.game_over = true;
            }
            else if(flag.is_spawned()){
                int bonus = time_left_val*100 + player.coin*50;
                menu.player_score = player.score + bonus;
                menu.set_high_score();
                switch_won_scr++;
                if(switch_won_scr >= 6*FPS){
                    menu.game_run = false;
                    menu.won_game = true;
                }
            }
		}

        SDL_RenderPresent(renderer);

        fps_manager();
	}
	Mix_HaltMusic();
	TTF_CloseFont(font);
}

void Game::game_loop(Character &player){
    time_count_down(player);

    flag.update(stage0, player); flag.draw(renderer);

    if(mushroom.get_spawning() || starman.get_spawning() || coin.get_spawning()){
        mushroom.update(stage0, player); mushroom.draw(renderer);
        starman.update(stage0, player); starman.draw(renderer);
        coin.update(stage0, player); coin.draw(renderer);
        map0.draw_map(renderer,stage0);
    }
    else{
        map0.draw_map(renderer,stage0);
        mushroom.update(stage0, player); mushroom.draw(renderer);
        starman.update(stage0, player); starman.draw(renderer);
        coin.update(stage0, player); coin.draw(renderer);
    }
    
    goombas->update_and_draw(renderer, stage0, goombas, player);
    
    player.update(stage0); player.draw(renderer);

    player.sco_mana.item_score.render(renderer);

    //render texts
    //render name and tags
    name.render(renderer);
    wo_ti.render(renderer);
    level.render(renderer);
    
    //render score
    render_score(player);

    //render num of coins
    render_coin_counter(player);

    //render num of lives
    render_lives_counter(player);

    //render time left
    render_time_counter(player);
}

void Game::set_menu(Character &player){
    menu.update(player);	menu.render(renderer);
    if(menu.exit) is_open = false;
    // std::cout<<menu.option<<std::endl;
}

void Game::set_map(){
    map0.load_map("res/map/map.dat"); map0.load_tiles(renderer);
    stage0 = map0.get_stage();
}

void Game::set_music(){
    music = Mix_LoadMUS("res/sound/theme_song.wav");
	Mix_PlayMusic(music, -1);
}

void Game::set_name_and_score(){
    name.set_text("MARIO"); name.set_position({67,20});
	name.write_text(renderer,font,color);

    score.set_position({67,45}); 
}

void Game::render_score(Character &player){
    std::string score_val;
	(player.score == 0) ? (score_val = "000000") : (score_val = std::string(5-(int)log10(player.score), '0') + std::to_string(player.score));
	score.set_text(score_val); 
	score.write_text(renderer,font,color);
	score.render(renderer);    
}

void Game::set_world_and_time(){
	wo_ti.set_text("              WORLD  TIME"); wo_ti.set_position({67,20});
	wo_ti.write_text(renderer,font,color);
}

void Game::set_world_level(){
	level.set_text("               1-1"); level.set_position({67,45});
	level.write_text(renderer,font,color);
}

void Game::coin_counter(){
    coin_num.set_position({263,45});
	coin_sym = Entity({231,50}, {25,25}, coin_sym.load_texture(renderer, "res/image/coin.png"));
}

void Game::render_coin_counter(Character &player){
	std::string coin_val;
	(player.coin == 0) ? (coin_val = "00") : (coin_val = std::string(1-(int)log10(player.coin), '0') + std::to_string(player.coin));
	coin_num.set_text("x" + coin_val); 
	coin_num.write_text(renderer,font,color);
	coin_num.render(renderer); 
	coin_sym.draw(renderer);
}

void Game::lives_counter(){
    lives_num.set_position({263,20}); 
	lives_sym = Entity({230,22}, {26,26}, lives_sym.load_texture(renderer, "res/image/mario_idle.png"));
}

void Game::render_lives_counter(Character &player){
    std::string lives_val;
    (player.lives == 0) ? (lives_val = "00") : (lives_val = std::string(1-(int)log10(player.lives), '0') + std::to_string(player.lives));
    lives_num.set_text("x" + lives_val); 
    lives_num.write_text(renderer,font,color);
    lives_num.render(renderer); 
    lives_sym.draw(renderer);
}

void Game::time_counter(){
    count_down.start();
    time_left.set_position({572,45}); time_left.write_text(renderer,font,color);
    count_down.pause();
}

void Game::time_count_down(Character &player){
    if(!player.get_death() && !player.is_won() && menu.game_run && !menu.is_paused){
        count_down.unpause();
        time_left_val = MAX_TIME - (count_down.get_ticks()/1000);
        if(time_left_val <= 0){
            time_left_val = 0;
            Mix_HaltMusic();
            Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/running_oot.wav"), 0);
            player.die();
        }
    }
    else{
        count_down.stop();
    }
}

void Game::render_time_counter(Character &player){
	time_left.set_text(std::to_string(time_left_val));
	time_left.write_text(renderer,font,color);
	time_left.render(renderer); 
}

void Game::fps_manager(){
    elapsed_time = timer.get_ticks();
	time_per_frame = 1000/FPS;
    
	if(elapsed_time < time_per_frame){
		int delay_time = time_per_frame - elapsed_time;
		if(delay_time > 0) SDL_Delay(delay_time);
	}
}
