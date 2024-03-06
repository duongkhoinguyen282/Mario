#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include<iostream>
#include<defs.h>
#include<entity.h>

void log_SDL_error(std::ostream &os, const std::string &msg, bool fatal = false);
void init_SDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quit_SDL(SDL_Window* &window, SDL_Renderer* &renderer);
void SDL_RenderEntity(SDL_Renderer* &renderer, Entity &entity);

#endif