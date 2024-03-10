#ifndef DEFS_H
#define DEFS_H

#include<bits/stdc++.h>

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

#define SPEED 15;
#define GRAVITY 9.8
#define MAX_FALL_SPEED 50

enum Tile {Empty, Ground, Wall, Question, Block, Cloud, Grass, B_Mountain, S_Mountain, Castle};

#endif