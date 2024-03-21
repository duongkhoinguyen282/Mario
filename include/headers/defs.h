#ifndef DEFS_H
#define DEFS_H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_timer.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Non-super Mario Bros"
const int BG_COLOR[3] {92,148,252};

#define MAX_TILES    20

#define TILE_SIZE    45

#define MAP_WIDTH    224
#define MAP_HEIGHT   16

#define MAP_RENDER_WIDTH    16
#define MAP_RENDER_HEIGHT   16

#define FPS 30

#define GRAVITY 9.8
#define MAX_FALL_SPEED 45

enum Tile {Empty, Ground, Wall, Question, Block, Cloud, Grass, Mountain, Pipe, SP_Block,
            Castle = 19, Ques_Aft_Hit = 13};

#endif