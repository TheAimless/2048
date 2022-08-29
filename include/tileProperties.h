#ifndef TPROP_h_
#define TPROP_h_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>

namespace text{
    class textProperties;
    std::map<int, SDL_Color> mp = {
        {0, {}},
        {2, {}},
        {4, {}},
        {8, {}},
        {16, {}},
        {32, {}},
        {64, {}},
        {128, {}},
        {256, {}},
        {512, {}},
        {1024, {}},
        {2048, {}},
        {4096, {}},
        {8192, {}},
        {16384, {}},
    };
}

class text::textProperties{
    public:
    textProperties();
    ~textProperties();

    virtual void draw(SDL_Renderer*);
    void setTextColor(SDL_Renderer*);
    void cleanup();

    private:
    int value;
    SDL_Color textColor;
    SDL_Rect* textRect{};
    TTF_Font* numFont;
    SDL_Surface *surface_{};
    SDL_Texture *texture_{};
};

#endif