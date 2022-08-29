#ifndef TILE_h_
#define TILE_h_
#include <random>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "tileProperties.h"

namespace tile{
    class Tile;
    extern std::random_device rd;
    extern std::mt19937 gen;
    extern std::uniform_int_distribution<> rand_num;

    static const int TILE_WIDTH = 106, TILE_HEIGHT = 106;
}

class tile::Tile{
    public:
    Tile();
    Tile(int, int, int, TTF_Font*, SDL_Renderer*);

    ~Tile();

    friend Tile operator+(Tile, const Tile&);
    Tile& operator+=(const Tile&);

    friend bool operator==(const Tile&, const Tile&);
    friend bool operator==(const Tile&, const int&);
    friend bool operator!=(const Tile&, const int&);
    friend bool operator!=(const Tile&, const Tile&);

    int value() const;
    void value(int);
    SDL_Renderer* renderer() const;
    void renderer(SDL_Renderer*);

    int x() const;
    void x(int);
    int y() const;
    void y(int);

    // Displays text
    void display();
    void cleanup();

    //Generates a random number for the tile
    friend void set_random(Tile&);
    friend void draw(Tile&);
    friend void drawVal(Tile&);
    
    private:
    int value_;
    int posX_, posY_;
    TTF_Font* numFont_;
    SDL_Renderer *renderer_;
    SDL_Rect tileRect_{}, textRect_{};
    SDL_Surface *surface_{};
    SDL_Texture *texture_{};

};
namespace tile{
    Tile operator+(Tile, const Tile&);
    bool operator==(const Tile&, const Tile&);
    bool operator==(const Tile&, const int&);
    bool operator!=(const Tile&, const int&);

    void set_random(Tile&);
    void draw(Tile&);
    void drawVal(Tile&);
}
#endif