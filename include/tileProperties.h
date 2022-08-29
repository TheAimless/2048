#ifndef TPROP_h_
#define TPROP_h_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace text{
    class textProperties;
}

class text::textProperties{
    public:
    textProperties();
    ~textProperties();

    virtual void draw(SDL_Renderer*);
    void setTextColor(SDL_Renderer*);
    void cleanup();

    private:
    SDL_Color textColor;
    SDL_Rect* textRect{};
    TTF_Font* numFont;
    SDL_Surface *surface_{};
    SDL_Texture *texture_{};
};

#endif