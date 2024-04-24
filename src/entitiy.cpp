#include<entity.h>

Entity::Entity(){
    position = {0,0};
    texture = nullptr;
    size = {0,0};
}
Entity::~Entity(){}

Entity::Entity(Vector2i position, SDL_Texture* texture){
    this->position = position;
    this->texture = texture;
    this->size = Vector2i(45,45);
}

Entity::Entity(Vector2i position,Vector2i size, SDL_Texture* texture){
    this->position = position;
    this->texture = texture;
    this->size = size;
}

void Entity::set_position(Vector2i position){
    this->position = position;
}

Vector2i Entity::get_position(){
    return position;
}

Vector2i Entity::get_size(){
    return size;
}

void Entity::set_texture(SDL_Texture* texture){
    this->texture = texture;
}

SDL_Texture* Entity::get_texture(){
    return texture;
}

SDL_Texture* Entity::load_texture(SDL_Renderer* &renderer, std::string filename){
    return IMG_LoadTexture(renderer,filename.c_str());
}

void Entity::draw(SDL_Renderer* &renderer){
    SDL_Rect dest = {position.x, position.y, size.x, size.y}; 
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void Entity::free(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}