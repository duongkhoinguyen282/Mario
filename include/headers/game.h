#ifndef GAME_H
#define GAME_H

#include<render_window.h>
#include<ctime>
#include<timer.h>
#include<goomba.h>
#include<mushroom.h>
#include<starman.h>
#include<coin.h>
#include<flag.h>
#include<text.h>
#include<menu.h>

class Game{
public:
    Game(/* args */);
    ~Game();

    void run();
    void game_loop(Character &player);
    void set_menu(Character &player);
    void set_map();
    void set_music();
    void set_name_and_score();
    void render_score(Character &player);
    void set_world_and_time();
    void set_world_level();
    void coin_counter();
    void render_coin_counter(Character &player);
    void lives_counter();
    void render_lives_counter(Character &player);
    void time_counter();
    void time_count_down(Character &player);
    void render_time_counter(Character &player);
    void fps_manager();

public:
    bool play_again;

private:
    bool is_open = true;

    Uint32 time_left_val = MAX_TIME;
    // bool game_run = false;
    // bool is_paused = false;
    // int option = 0;

    //init timer
	Timer timer;
	int elapsed_time = 0;
	int time_per_frame = 0;

    //init window
	SDL_Window* window; SDL_Renderer* renderer;

    //init menu
	Menu menu;

    //init map
	Map map0; 
	Stage stage0;

	//init goombas
	Goomba* goombas;

	//init items
	Mushroom mushroom;
	Starman starman;
	Coin coin;
	Flag flag;

	//init theme music
	Mix_Music* music;

	//init texts
	TTF_Font* font;
	SDL_Color color = {255,255,255};
    
    Text name;
    Text wo_ti;
    Text level;
    Text score;

    Text coin_num; 
    Entity coin_sym;

    Text lives_num; 
    Entity lives_sym;

    Text time_left;
    Timer count_down;
};




#endif