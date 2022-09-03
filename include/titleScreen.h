#ifndef TITLE_h_
#define TITLE_h_
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace title{
    class Title;
    static const int BUTTON_WIDTH = 100, BUTTON_HEIGHT = 20;
    static const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
} // namespace title

class title::Title{
    public:
    Title(std::string&);
    ~Title();

    void renderPlayButton(SDL_Renderer*);
    void renderQuitButton(SDL_Renderer*);
    void renderText(SDL_Renderer*);
    void renderAll(SDL_Renderer*);

    bool playClicked(int, int);
    bool quitClicked(int, int);

    private:
    std::string gameTitle_;
    SDL_Rect playBut_, quitBut_;
    SDL_Rect playText_, quitText_, titleText_;
    TTF_Font *titleFont_, *buttonFont_;
};

#endif