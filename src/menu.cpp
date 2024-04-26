#include<menu.h>

Menu::Menu(){
    title_screen.free();
    pause_screen.free();
    op_2p_screen.free();
    play_again_screen.free();
    cursor.free();

    title_screen = Entity({0,0}, {720,720}, nullptr);
    pause_screen = Entity({0,0}, {720,720}, nullptr);
    op_2p_screen = Entity({0,0}, {720,720}, nullptr);
    play_again_screen = Entity({0,0}, {720,720}, nullptr);

    cursor = Entity({200,450}, {25,25}, nullptr);

    //set font
    font = TTF_OpenFont("fonts/joystix monospace.otf",30);

    get_high_score();
}

Menu::~Menu(){}

void Menu::get_high_score(){
    std::ifstream r_file("src/high_score.txt");
    r_file >> hi_score;
}

void Menu::set_high_score(){
    std::ofstream w_file("src/high_score.txt");
    if(player_score > hi_score) w_file << player_score;
}

void Menu::render_tit_scr(SDL_Renderer *&renderer){
    title_screen.free();
    
    title_screen.set_texture(title_screen.load_texture(renderer, "res/image/title_screen.png"));
    title_screen.draw(renderer);

    std::string score_val;
	(hi_score == 0) ? (score_val = "000000") : (score_val = std::string(5-(int)log10(hi_score), '0') + std::to_string(hi_score));
    high_score.set_text(score_val); high_score.set_position({380,552});
	high_score.write_text(renderer,font,color);
    high_score.render(renderer);
}

void Menu::render_pau_scr(SDL_Renderer* &renderer){
    pause_screen.free();

    pause_screen.set_texture(pause_screen.load_texture(renderer, "res/image/pause_screen.png"));
    pause_screen.draw(renderer);
}

void Menu::render_op2p_scr(SDL_Renderer* &renderer){
    op_2p_screen.free();

    op_2p_screen.set_texture(op_2p_screen.load_texture(renderer, "res/image/n_a_feature.png"));
    op_2p_screen.draw(renderer);
}

void Menu::render_play_again_scr(SDL_Renderer *&renderer){
    play_again_screen.free();

    if(game_over){
        play_again_screen.set_texture(play_again_screen.load_texture(renderer, "res/image/game_over_screen.png"));
    }
    else if(won_game){
        play_again_screen.set_texture(play_again_screen.load_texture(renderer, "res/image/you_won_screen.png"));
    }
    play_again_screen.draw(renderer);

    if(won_game){
        std::string score_val;
	    (player_score == 0) ? (score_val = "000000") : (score_val = std::string(5-(int)log10(player_score), '0') + std::to_string(player_score));
        total_score.set_text(score_val); total_score.set_position({400,325});
    	total_score.write_text(renderer,font,color);
        total_score.render(renderer);
    }
}

void Menu::render(SDL_Renderer* &renderer){
    cursor.free();

    if(op_2p){
        render_op2p_scr(renderer);
    }

    else{
        if(is_paused && !game_run && !won_game && !game_over){
            render_pau_scr(renderer);
        }
        else if(!game_run && !is_paused && !won_game && !game_over){
            render_tit_scr(renderer);
        }
        else if(won_game || game_over){
            render_play_again_scr(renderer);
        }
        cursor.set_texture(cursor.load_texture(renderer, "res/image/title_cursor.png"));
        cursor.draw(renderer);
    }
}

void Menu::handle_input(SDL_Event event){
    if(game_run){
        return;
    }

    if(!op_2p){      
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_UP){
                cursor_move.up = true;
            }
            else if(event.key.keysym.sym == SDLK_DOWN){
                cursor_move.down = true;
            }
    
            if(event.key.keysym.sym == SDLK_RETURN){
                cursor_move.enter = true;
            }
    
        }
        else if(event.type == SDL_KEYUP){
            if(event.key.keysym.sym == SDLK_UP){
                cursor_move.up = false;
            }
            else if(event.key.keysym.sym == SDLK_DOWN){
                cursor_move.down = false;
            }
    
            if(event.key.keysym.sym == SDLK_RETURN){
                cursor_move.enter = false;
            }
        }
    }
    else{
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_ESCAPE){
                Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/choose_option.wav"), 0);
                op_2p = false;
            }
        }
    }
}

void Menu::update(Character &player){
    if(cursor_move.down && option == 0 && up){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/move_cursor.wav"), 0);
        up = false;
        cursor.set_position({cursor.get_position().x, cursor.get_position().y + 45});
    }
    else if(cursor_move.up && option == 0 && !up){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/move_cursor.wav"), 0);
        up = true;
        cursor.set_position({cursor.get_position().x, cursor.get_position().y - 45});
    }

    if(cursor_move.enter){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/choose_option.wav"), 0);
        // std::cout<<option<<std::endl;
        
        up ? (option = 1) : (option = 2);

        cursor_move.enter = false;
        
        if(option == 1){
            is_paused = false;
            if(won_game || game_over){
                play_again = true;
                free();
            }
            else{
                game_run = true;
            }
        }
        else if(option == 2){
            if(!game_run && !is_paused && !won_game && !game_over){
                op_2p = true;
                // std::cout<<"This feature has not been updated, please follow us to get further details up to date!"<<std::endl;
            }
            else if(is_paused || won_game || game_over){
                exit = true;
                is_paused = false;
                // std::cout<<"Exit"<<std::endl;
            }
        }
    }
    else{
        option = 0;
    }

    if(is_paused && game_run){
        Mix_PlayChannel(-1, Mix_LoadWAV("res/sound/pause.wav"), 0);
        player.pause_action();
        game_run = false;
    }

    // if(player.is_won()) won_game = true;
    // else if(player.get_death()) game_over = true;
}

void Menu::free(){
    title_screen.free();
    pause_screen.free();
    op_2p_screen.free();
    play_again_screen.free();
    cursor.free();
}
