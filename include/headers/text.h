#ifndef TEXT_H
#define TEXT_H

#include<defs.h>
#include<entity.h>

class Text: public Entity{
public:
    Text();
    ~Text();

    void set_text(const std::string& text) {
        content = text;
    };
    void set_color(Uint8 r, Uint8 g, Uint8 b){
	    SDL_SetTextureColorMod(texture, r, g, b);
    };
    void set_blending(SDL_BlendMode blend_mode){
        SDL_SetTextureBlendMode(texture, blend_mode);
    }
    void write_text(SDL_Renderer* &renderer, TTF_Font* font, SDL_Color color);
    void render(SDL_Renderer* &renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    std::string content;
};

#endif