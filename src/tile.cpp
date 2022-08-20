#include "tile.h"
#include <random>
using namespace tile;

Tile::Tile() : value(0){}

Tile::Tile(int value, int posX, int posY) :
    value(value), posX(posX), posY(posY){
        rd = new std::random_device();
        gen = new std::mt19937((*rd)());
        rand_num = new std::uniform_int_distribution<>(0, 7);
    }

namespace tile{
    Tile operator+(Tile lhs, const Tile& rhs){
        if (lhs == rhs){
            lhs.value += rhs.value;
        }
        return lhs;
    }

    bool operator==(const Tile& lhs, const Tile& rhs){
        return lhs.value == rhs.value;
    }

    bool operator==(const Tile& lhs, const int& rhs){
        return lhs.value == rhs;
    }

    bool operator!=(const Tile& lhs, const int& rhs){
        return !(lhs == rhs);
    }
}

Tile& Tile::operator+=(const Tile& rhs){
    *this = *this + rhs;
    return *this;
}

namespace tile{
    int get_value(const Tile& lhs){
        return lhs.value;
    }

    void set_value(Tile& lhs, int value){
        lhs.value = value;
    } 

    std::uniform_int_distribution<>* get_randNum(const Tile& lhs){
        return lhs.rand_num;
    }

    std::mt19937* get_generator(const Tile& lhs){
        return lhs.gen;
    }

    void set_random(Tile& lhs){
        set_value(lhs, ((*get_randNum(lhs))(*(get_generator(lhs))) < 2 ? 4 : 2));
    }
}