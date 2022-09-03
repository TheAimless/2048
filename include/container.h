#ifndef CONTAINER_h_
#define CONTAINER_h_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace container{
    class Container;
} 

class container::Container{
    public:
    Container(SDL_Rect, std::string, SDL_Color, SDL_Color, int);
    ~Container();

    void displayContainer(SDL_Renderer*);
    SDL_Rect box() const;

    private:
    SDL_Rect box_, textBox_;
    std::string text_;
    SDL_Color boxColor_, textColor_;
    TTF_Font *textFont_;
};

#endif