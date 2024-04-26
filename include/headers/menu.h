#ifndef MENU_H
#define MENU_H

#include<defs.h>
#include<entity.h>
#include<character.h>

class Menu{

public:
    Menu();
    ~Menu();

    void render_tit_scr(SDL_Renderer* &renderer);
    void render_pau_scr(SDL_Renderer* &renderer);
    void render_op2p_scr(SDL_Renderer* &renderer);
    void render(SDL_Renderer* &renderer);
    void handle_input(SDL_Event event);
    void update(Character &player);

public:
    bool game_run = false;
    bool is_paused = false;
    int option = 0;
    bool exit = false;

private:
    Entity screen;
    Entity title_screen;
    Entity pause_screen;
    Entity op_2p_screen;
    Entity cursor;
    Input cursor_move;
    bool up = true;
    bool op_2p = false;
};

#endif