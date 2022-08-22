#include "tile.h"
#include <random>
using namespace tile;

namespace tile{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_num(0, 7);
}

Tile::Tile() : value_(0){
}

Tile::Tile(int value, int posX, int posY) :
    value_(value), posX_(posX), posY_(posY){
    }

Tile::~Tile(){
}

namespace tile{
    Tile operator+(Tile lhs, const Tile& rhs){
        if (lhs == rhs){
            lhs.value(lhs.value_ + rhs.value_);
        }
        return lhs;
    }

    bool operator==(const Tile& lhs, const Tile& rhs){
        return lhs.value_ == rhs.value_;
    }

    bool operator==(const Tile& lhs, const int& rhs){
        return lhs.value() == rhs;
    }

    bool operator!=(const Tile& lhs, const int& rhs){
        return !(lhs == rhs);
    }
}

Tile& Tile::operator+=(const Tile& rhs){
    *this = *this + rhs;
    return *this;
}

int Tile::value() const{
    return value_;
}

void Tile::value(int value){
    value_ = std::move(value);
}

namespace tile{
    void set_random(Tile& lhs){
        lhs.value(rand_num(gen) < 2 ? 4 : 2);
    }
}