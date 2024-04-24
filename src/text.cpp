#include<text.h>

Text::Text(){
    content = " ";
    texture = nullptr;
	size.x = 0;
	size.y = 0;
}

Text::~Text(){}

void Text::write_text(SDL_Renderer* &renderer, TTF_Font* font, SDL_Color color){
    free();
    SDL_Surface* surface = TTF_RenderText_Solid(font, content.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    size.x = surface->w;
    size.y = surface->h;

    SDL_FreeSurface(surface);
}

void Text::render(SDL_Renderer* &renderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip){
    SDL_Rect render_quad = {position.x, position.y, size.x, size.y};
    if( clip != NULL )
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &render_quad, angle, center, flip );
}
