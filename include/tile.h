#ifndef TILE_h_
#define TILE_h_
#include <random>

namespace tile{
    class Tile;
}

class tile::Tile{
    public:
    Tile();
    Tile(int value, int posX, int posY);

    friend Tile operator+(Tile, const Tile&);
    Tile& operator+=(const Tile&);

    friend bool operator==(const Tile&, const Tile&);
    friend bool operator==(const Tile&, const int&);
    friend bool operator!=(const Tile&, const int&);

    friend int get_value(const Tile&);
    friend void set_value(Tile&, int);
    friend std::uniform_int_distribution<>* get_randNum(const Tile&);
    friend std::mt19937* get_generator(const Tile&);

    //Generates a random number for the tile
    friend void set_random(Tile&);
    
    private:
    int value;
    int posX, posY;
    std::random_device *rd;
    std::mt19937 *gen;
    std::uniform_int_distribution<> *rand_num;
    
};
namespace tile{
    Tile operator+(Tile, const Tile&);
    bool operator==(const Tile&, const Tile&);
    bool operator==(const Tile&, const int&);
    bool operator!=(const Tile&, const int&);

    int get_value(const Tile&);
    void set_value(Tile&, int);
    void set_random(Tile&);

    std::uniform_int_distribution<>* get_randNum(const Tile&);
    std::mt19937* get_generator(const Tile&);
}
#endif