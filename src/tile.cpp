#include "tile.h"
#include <random>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace tile;

namespace tile{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_num(0, 7);
}

Tile::Tile() :
value_(0), posX_(0), posY_(0), numFont_(nullptr), renderer_(nullptr){
    tileRect_.x = static_cast<int>(posX_);
    tileRect_.y = static_cast<int>(posY_);
    tileRect_.w = TILE_WIDTH;
    tileRect_.h = TILE_HEIGHT;
    numRect_.x = tileRect_.x;
    numRect_.y = tileRect_.y;
}

Tile::Tile(int value, int posX, int posY, TTF_Font *numFont, SDL_Renderer* renderer) :
    value_(value), posX_(posX), posY_(posY), numFont_(numFont), renderer_(renderer)
{
    tileRect_.x = static_cast<int>(posX_);
    tileRect_.y = static_cast<int>(posY_);
    tileRect_.w = TILE_WIDTH;
    tileRect_.h = TILE_HEIGHT;
    numRect_.x = tileRect_.x;
    numRect_.y = tileRect_.y;
    display();
}

Tile::~Tile(){
    //cleanup();
}

void Tile::cleanup(){
    SDL_FreeSurface(surface_);
    SDL_DestroyTexture(texture_);
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
    value_ = value;
}

SDL_Renderer* Tile::renderer() const{
    return renderer_;
}

void Tile::renderer(SDL_Renderer* renderer){
    renderer_ = renderer;
}

int Tile::x() const{
    return posX_;
}

void Tile::x(int x){
    posX_ = x;
}

int Tile::y() const{
    return posY_;
}

void Tile::y(int y){
    posY_ = y;
}

void Tile::display(){
    std::string num = std::to_string(value_);
    surface_ = TTF_RenderText_Solid(numFont_, num.c_str(), {0x00, 0x00, 0x00});
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
    int width, height;
    SDL_QueryTexture(texture_, nullptr, nullptr, &width, &height);

    numRect_.w = width;
    numRect_.h = height;
}

namespace tile{
    void set_random(Tile& lhs){
        lhs.value(rand_num(gen) < 2 ? 4 : 2);
    }

    void draw(Tile& tile){
        tile.tileRect_.x = static_cast<int>(tile.posX_);
        tile.tileRect_.y = static_cast<int>(tile.posY_);

        SDL_RenderFillRect(tile.renderer_, &tile.tileRect_);
    }

    void drawVal(Tile& tile){
        tile.numRect_.x = static_cast<int>(tile.posX_);
        tile.numRect_.y = static_cast<int>(tile.posY_);
        SDL_RenderCopy(tile.renderer_, tile.texture_, nullptr, &tile.numRect_);
    }
}