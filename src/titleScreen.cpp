#include "titleScreen.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

title::Title::Title(
    std::string& gameTitle) :
    gameTitle_(gameTitle)
{
    titleFont_ = TTF_OpenFont("res/fonts/helvetica-bold.ttf", 100);
    buttonFont_ = TTF_OpenFont("res/fonts/helvetica-bold.ttf", 60);
    playBut_ = {WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2,
                BUTTON_WIDTH, BUTTON_HEIGHT};
    quitBut_ = {WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 100,
                BUTTON_WIDTH, BUTTON_HEIGHT};
}

title::Title::~Title(){
    TTF_CloseFont(titleFont_);
    TTF_CloseFont(buttonFont_);
}

void title::Title::renderPlayButton(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0xbb, 0xad, 0xa0, 0xff);
    SDL_RenderFillRect(renderer, &(this->playBut_));
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    std::string text = "Play";
    SDL_Color textColor{0x77, 0x6e, 0x65, 0xff};
    auto surface = TTF_RenderText_Solid(
        this->buttonFont_,
        text.c_str(),
        textColor
    );
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->playText_.w = width;
    this->playText_.h = height;
    this->playText_.x = static_cast<int>(this->playBut_.x + BUTTON_WIDTH / 2 - width / 2);
    this->playText_.y = static_cast<int>(this->playBut_.y + BUTTON_HEIGHT / 2 - height / 2);
    SDL_RenderCopy(renderer, texture, nullptr, &(this->playText_));

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void title::Title::renderQuitButton(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0xbb, 0xad, 0xa0, 0xff);
    SDL_RenderFillRect(renderer, &(this->quitBut_));
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    std::string text = "Quit";
    SDL_Color textColor{0x77, 0x6e, 0x65, 0xff};
    auto surface = TTF_RenderText_Solid(
        this->buttonFont_,
        text.c_str(),
        textColor
    );
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->playText_.w = width;
    this->playText_.h = height;
    this->playText_.x = static_cast<int>(this->quitBut_.x + BUTTON_WIDTH / 2 - width / 2);
    this->playText_.y = static_cast<int>(this->quitBut_.y + BUTTON_HEIGHT / 2 - height / 2);
    SDL_RenderCopy(renderer, texture, nullptr, &(this->quitText_));

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void title::Title::renderText(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Color textColor{0x77, 0x6e, 0x65, 0xff};
    auto surface = TTF_RenderText_Solid(
        this->titleFont_,
        this->gameTitle_.c_str(),
        textColor
    );
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->titleText_.w = width;
    this->titleText_.h = height;
    this->playText_.x = static_cast<int>(WINDOW_WIDTH / 2 - width / 2);
    this->playText_.y = static_cast<int>(WINDOW_HEIGHT / 2 - height / 2 - 200);
    SDL_RenderCopy(renderer, texture, nullptr, &(this->titleText_));

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void title::Title::renderAll(SDL_Renderer* renderer){
    this->renderPlayButton(renderer);
    this->renderQuitButton(renderer);
    this->renderText(renderer);
}

bool title::Title::playClicked(int x, int y){
    return true;
}

bool title::Title::quitClicked(int x, int y){
    return true;
}