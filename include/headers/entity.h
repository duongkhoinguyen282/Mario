#ifndef ENTITY_H
#define ENTITY_H

#include<structs.h>

class Entity{
public:
    Entity();
    ~Entity();
    Entity(Vector2i position, SDL_Texture* texture);
    Entity(Vector2i position,Vector2i size, SDL_Texture* texture);
    void set_position(Vector2i position);
    Vector2i get_position();
    Vector2i get_size();
    void set_texture(SDL_Texture* texture);
    SDL_Texture* get_texture();
    SDL_Texture* load_texture(SDL_Renderer* &renderer, std::string filename);
    void draw(SDL_Renderer* &renderer);
    void free();

protected:
    Vector2i position;
    Vector2i size;
    SDL_Texture* texture;
};

#endif