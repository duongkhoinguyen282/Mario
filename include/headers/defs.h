#ifndef DEFS_H
#define DEFS_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_timer.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Super Mario Bros."
const int BG_COLOR[3] {146,144,255};

#define MAX_TILES    20

#define TILE_SIZE    45

#define MAP_WIDTH    224
#define MAP_HEIGHT   16

#define MAP_RENDER_WIDTH    16
#define MAP_RENDER_HEIGHT   16

#define FPS 25

#define GRAVITY 9.8
#define MAX_FALL_SPEED 45
#define MAX_TIME 300

enum Tile {Empty, Ground, Wall, Question, Block, Cloud, Grass, Mountain, Pipe, SP_Block,
            Castle = 19, Ques_Aft_Hit = 13};

enum Item {_Empty, _Magic, _1_up, _Starman, _Coin};

#endif