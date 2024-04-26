#include<menu.h>

Menu::Menu(){
    title_screen = Entity({0,0}, {720,720}, nullptr);
    pause_screen = Entity({0,0}, {720,720}, nullptr);
    op_2p_screen = Entity({0,0}, {720,720}, nullptr);
    cursor = Entity({200,450}, {25,25}, nullptr);
}

Menu::~Menu(){}

void Menu::render_tit_scr(SDL_Renderer *&renderer){
    title_screen.free();

    title_screen.set_texture(title_screen.load_texture(renderer, "res/image/title_screen.png"));
    title_screen.draw(renderer);
}

void Menu::render_pau_scr(SDL_Renderer* &renderer){
    pause_screen.free();

    pause_screen.set_texture(pause_screen.load_texture(renderer, "res/image/pause_screen.png"));
    pause_screen.draw(renderer);
}

void Menu::render_op2p_scr(SDL_Renderer* &renderer){
    op_2p_screen.free();

    op_2p_screen.set_texture(op_2p_screen.load_texture(renderer, "res/image/op_2p_screen.png"));
    op_2p_screen.draw(renderer);
}

void Menu::render(SDL_Renderer* &renderer){
    cursor.free();

    if(is_paused && !game_run){
        render_pau_scr(renderer);
    }
    else if(!game_run && !is_paused){
        render_tit_scr(renderer);
    }

    cursor.set_texture(cursor.load_texture(renderer, "res/image/title_cursor.png"));
    cursor.draw(renderer);
}

void Menu::handle_input(SDL_Event event){
    if(game_run){
        return;
    }
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
            game_run = true;
        }
        else if(option == 2){
            if(!game_run && !is_paused){
                std::cout<<"This feature has not been updated, please follow us to get further details up to date!"<<std::endl;
            }
            else if(is_paused){
                exit = true;
                is_paused = false;
                std::cout<<"Exit"<<std::endl;
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
}
