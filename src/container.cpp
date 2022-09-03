#include "container.h"
using namespace container;

Container::Container(
    SDL_Rect box, std::string text, SDL_Color boxColor, SDL_Color textColor,
    int ft) : 
    text_(text), boxColor_(boxColor), textColor_(textColor), box_(box)
{
    textFont_ = TTF_OpenFont("res/fonts/helvetica-bold.ttf", ft);
}

Container::~Container(){
    TTF_CloseFont(textFont_);
}

void Container::displayContainer(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, boxColor_.r, boxColor_.g, boxColor_.b, boxColor_.a);
    SDL_RenderFillRect(renderer, &(this->box_));

    auto surface = TTF_RenderText_Solid(
        this->textFont_,
        text_.c_str(),
        textColor_
    );
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->textBox_.w = width;
    this->textBox_.h = height;
    this->textBox_.x = static_cast<int>(box_.x + box_.w / 2 - width / 2);
    this->textBox_.y = static_cast<int>(box_.y + box_.h / 2 - height / 2 - 20);
    SDL_RenderCopy(renderer, texture, nullptr, &(this->textBox_));

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

SDL_Rect Container::box() const{
    return box_;
}