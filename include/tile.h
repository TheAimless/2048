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

    ~Tile();

    friend Tile operator+(Tile, const Tile&);
    Tile& operator+=(const Tile&);

    friend bool operator==(const Tile&, const Tile&);
    friend bool operator==(const Tile&, const int&);
    friend bool operator!=(const Tile&, const int&);

    int value() const;
    void value(int value);
    std::mt19937* gen() const;
    std::uniform_int_distribution<>* rand_num() const;


    //Generates a random number for the tile
    friend void set_random(Tile&);
    
    private:
    int value_;
    int posX_, posY_;
    std::random_device *rd_;
    std::mt19937 *gen_;
    std::uniform_int_distribution<> *rand_num_;
    
};
namespace tile{
    Tile operator+(Tile, const Tile&);
    bool operator==(const Tile&, const Tile&);
    bool operator==(const Tile&, const int&);
    bool operator!=(const Tile&, const int&);

    void set_random(Tile&);
}
#endif