#ifndef TITLE_h_
#define TITLE_h_
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace title{
    class Title;
} // namespace title

class title::Title{
    public:
    Title(std::string&);
    ~Title();

    private:
    std::string gameTitle_;
    SDL_Rect playBut_, quitBut_;
    TTF_Font *titleFont_, *buttonFont_;
};

#endif