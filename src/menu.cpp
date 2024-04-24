#include<menu.h>

Menu::Menu(){
    title_screen = Entity({0,0}, {720,720}, nullptr);
    cursor = Entity({200,450}, {25,25}, nullptr);
}

Menu::~Menu(){}

void Menu::render(SDL_Renderer *&renderer){
    title_screen.free();
    cursor.free();

    title_screen.set_texture(title_screen.load_texture(renderer, "res/image/title_screen.png"));
    title_screen.draw(renderer);

    cursor.set_texture(cursor.load_texture(renderer, "res/image/title_cursor.png"));
    cursor.draw(renderer);
}

void Menu::handle_input(SDL_Event event){
}
