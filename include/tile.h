#ifndef TILE_h_
#define TILE_h_
#include <random>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace tile{
    class Tile;
    extern std::random_device rd;
    extern std::mt19937 gen;
    extern std::uniform_int_distribution<> rand_num;

    static const int TILE_WIDTH = 106, TILE_HEIGHT = 106;
    static const std::map<int, SDL_Color> tileColor = {
        {0, {0xcd, 0xc1, 0xb4, 0xff}},
        {2, {0xee, 0xe4, 0xda, 0xff}},
        {4, {0xed, 0xe0, 0xc8, 0xff}},
        {8, {0xf2, 0xb1, 0x79, 0xff}},
        {16, {0xf5, 0x95, 0x63, 0xff}},
        {32, {0xf6, 0x7c, 0x5f, 0xff}},
        {64, {0xf6, 0x5e, 0x3b, 0xff}},
        {128, {0xed, 0xcf, 0x72, 0xff}},
        {256, {0xed, 0xcc, 0x61, 0xff}},
        {512, {0xed, 0xc8, 0x50, 0xff}},
        {1024, {0xed, 0xc5, 0x3f, 0xff}},
        {2048, {0xed, 0xc5, 0x3f, 0xff}},
        {4096, {0x3c, 0x3a, 0x32, 0xff}},
        {8192, {0x3c, 0x3a, 0x32, 0xff}},
        {16384, {0x3c, 0x3a, 0x32, 0xff}},
        {32768, {0x3c, 0x3a, 0x32, 0xff}},

    };
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