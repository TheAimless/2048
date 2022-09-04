#include "container.h"
#include "score.h"
using namespace score;

Score::Score(
    SDL_Rect box, std::string text, SDL_Color boxColor, SDL_Color textColor,
    int ft, int score, SDL_Color scoreColor, int scoreFt): 
    container::Container::Container(box, text, boxColor, textColor, ft),
    score_(score), scoreColor_(scoreColor)
{
    scoreFont_ = TTF_OpenFont("res/fonts/Helvetica-Bold.ttf", scoreFt);
}

Score::~Score(){
    TTF_CloseFont(scoreFont_);
}

void Score::displayScore(SDL_Renderer* renderer){
    this->displayContainer(renderer);

    auto surface = TTF_RenderText_Solid(
        this->scoreFont_,
        std::to_string(score_).c_str(),
        scoreColor_
    );
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->scoreBox_.w = width;
    this->scoreBox_.h = height;
    this->scoreBox_.x = static_cast<int>(box().x + box().w / 2 - width / 2);
    this->scoreBox_.y = static_cast<int>(box().y + box().h / 2 - height / 2 + 10);
    SDL_RenderCopy(renderer, texture, nullptr, &(this->scoreBox_));

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Score::updateScore(int score){
    this->score_ = score;
}

int Score::getScore() const{
    return score_;
}