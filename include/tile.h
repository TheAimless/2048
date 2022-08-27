#ifndef TILE_h_
#define TILE_h_
#include <random>
#include <SDL2/SDL.h>

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
    Tile(int value, int posX, int posY);

    ~Tile();

    friend Tile operator+(Tile, const Tile&);
    Tile& operator+=(const Tile&);

    friend bool operator==(const Tile&, const Tile&);
    friend bool operator==(const Tile&, const int&);
    friend bool operator!=(const Tile&, const int&);

    int value() const;
    void value(int value);

    //Generates a random number for the tile
    friend void set_random(Tile&);
    friend void draw(SDL_Renderer*, Tile&);
    
    private:
    int value_;
    int posX_, posY_;
    SDL_Rect rect_{};
    
};
namespace tile{
    Tile operator+(Tile, const Tile&);
    bool operator==(const Tile&, const Tile&);
    bool operator==(const Tile&, const int&);
    bool operator!=(const Tile&, const int&);

    void set_random(Tile&);
    void draw(SDL_Renderer*, Tile&);
}
#endif