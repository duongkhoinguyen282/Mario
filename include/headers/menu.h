#ifndef MENU_H
#define MENU_H

#include<defs.h>
#include<entity.h>
#include<character.h>

class Menu{

public:
    Menu();
    ~Menu();

    void get_high_score();
    void set_high_score();
    void render_tit_scr(SDL_Renderer* &renderer);
    void render_pau_scr(SDL_Renderer* &renderer);
    void render_op2p_scr(SDL_Renderer* &renderer);
    void render_play_again_scr(SDL_Renderer* &renderer);
    void render(SDL_Renderer* &renderer);
    void handle_input(SDL_Event event);
    void update(Character &player);
    void free();

public:
    bool game_run = false;
    bool is_paused = false;
    bool won_game = false;
    int player_score = 0;
    bool game_over = false;
    bool play_again = false;
    int option = 0;
    bool exit = false;

private:
    Entity title_screen;
    Entity pause_screen;
    Entity op_2p_screen;
    Entity play_again_screen;

    //init texts
	TTF_Font* font;
	SDL_Color color = {255,255,255};
    Text high_score;
    Text total_score;

    Entity cursor;
    Input cursor_move;
    bool up = true;
    bool op_2p = false;

    int hi_score = 0;
};

#endif