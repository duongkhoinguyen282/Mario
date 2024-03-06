#ifndef ENTITY_H
#define ENTITY_H

#include<SDL.h>
#include<SDL_image.h>
#include<structs.h>
#include<SDL_timer.h>

class Entity{
public:
    Entity();
    ~Entity();
    Entity(Vector2i position, SDL_Texture* texture);
    Entity(Vector2i position,Vector2i size, SDL_Texture* texture);
    void set_position(Vector2i position);
    Vector2i get_position();
    Vector2i get_size();
    SDL_Texture* get_texture();
    virtual SDL_Texture* load_texture(SDL_Renderer* &renderer, std::string filename);
    void free();

protected:
    Vector2i position;
    Vector2i size;
    SDL_Texture* texture;
};

#endif