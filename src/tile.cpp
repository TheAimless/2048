#include "tile.h"
#include <random>
using namespace tile;

Tile::Tile() : value_(0){
    rd_ = new std::random_device();
    gen_ = new std::mt19937((*rd_)());
    rand_num_ = new std::uniform_int_distribution<>(0, 7);
}

Tile::Tile(int value, int posX, int posY) :
    value_(value), posX_(posX), posY_(posY){
        rd_ = new std::random_device();
        gen_ = new std::mt19937((*rd_)());
        rand_num_ = new std::uniform_int_distribution<>(0, 7);
    }

Tile::~Tile(){
    delete this->rd_;
    delete this->gen_;
    delete this->rand_num_;
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
        return lhs.value_ == rhs;
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

std::mt19937* Tile::gen() const{
    return gen_;
}

std::uniform_int_distribution<>* Tile::rand_num() const{
    return rand_num_;
}

namespace tile{
    void set_random(Tile& lhs){
        lhs.value(((*(lhs.rand_num()))(*(lhs.gen())) < 2 ? 4 : 2));
    }
}