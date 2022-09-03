#ifndef SCORE_h_
#define SCORE_h_
#include "container.h"

namespace score{
    class Score;
}

class score::Score : container::Container{
    public:
    Score(SDL_Rect, std::string, SDL_Color, SDL_Color, int, int, SDL_Color);
    ~Score();

    void displayScore(SDL_Renderer*);
    void updateScore(int);
    
    int getScore() const;

    private:
    int score_;
    SDL_Color scoreColor_;
    SDL_Rect scoreBox_;
    TTF_Font *scoreFont_;
};

#endif