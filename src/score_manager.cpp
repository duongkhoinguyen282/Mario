#include<score_manager.h>

Score_Manager::Score_Manager(){
    font = TTF_OpenFont("fonts/joystix monospace.otf",20);
	color = {255,255,255};
    item_score.set_text(" ");
    score_increase = 0;
}

Score_Manager::~Score_Manager(){}

void Score_Manager::update(SDL_Renderer *&renderer){
    if(score_increase > 0) {
        appear = true;
        item_score.set_text(std::to_string(score_increase));
    }

    if(appear){
        appear_time -= 0.1f;
    }

    if(appear_time <= 0.1f){
        item_score.set_text(" ");
        appear = false;
        appear_time = 1.5f;
    }
    item_score.write_text(renderer,font,color);
    score_increase = 0;
}
