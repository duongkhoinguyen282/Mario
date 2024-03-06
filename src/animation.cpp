#include<animation.h>

Animation::Animation(SDL_Texture* textuxe, Vector2i img_count, float switch_time){
    this->img_count = img_count;
    this->switch_time = switch_time;
    total_time = 0.0f;
    curr_image.x = 0;

    SDL_QueryTexture(textuxe,nullptr,nullptr,&rect.w,&rect.h);
    rect.w /= float(img_count.x);
    rect.h /= float(img_count.y); 

}

Animation::~Animation(){}

void Animation::update(int row, float delta_time){
    curr_image.y = row;
    total_time += delta_time;
    
    if(total_time >= switch_time){
        total_time -= switch_time;
        curr_image.x++;

        if(curr_image.x >= img_count.x){
            curr_image.x = 0;
        }
    }

    rect.x = curr_image.x*rect.w;
    rect.y = curr_image.y*rect.h;
    
}