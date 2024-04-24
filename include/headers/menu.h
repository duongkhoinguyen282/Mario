#ifndef MENU_H
#define MENU_H

#include<defs.h>
#include<entity.h>

class Menu{

public:
    Menu();
    ~Menu();

    void render(SDL_Renderer* &renderer);
    void handle_input(SDL_Event event);

private:
    Entity title_screen;
    Entity cursor;
};

#endif