#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "tileProperties.h"

void text::textProperties::draw(SDL_Renderer* renderer){
    this->setTextColor(renderer);
    
}

void text::textProperties::setTextColor(SDL_Renderer* renderer){
    if (this->value < 8){
        this->textColor = {0x77, 0x6e, 0x65, 0xff};
    }
    else{
        this->textColor = {0xf9, 0xf6, 0xf2, 0xff};
    }
}