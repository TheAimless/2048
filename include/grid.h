#ifndef GRID_h_
#define GRID_h_
#include <array>
#include <random>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "tile.h"

namespace grid{
    static const int GRID_WIDTH = 4, GRID_HEIGHT = 4;
    static const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
    static const int GAP = 9;
    static const int X0 = WINDOW_WIDTH / 2 - (3 * GAP) / 2 - tile::TILE_WIDTH * 2;
    static const int Y0 = WINDOW_HEIGHT / 2 - (3 * GAP ) / 2 - tile::TILE_HEIGHT * 2;

    class Grid;
    extern std::random_device rd;
    extern std::mt19937 gen;
    extern std::uniform_int_distribution<> rand_num;
}

class grid::Grid{
    public:
    Grid(SDL_Renderer*);
    ~Grid();

    friend std::ostream& operator<<(std::ostream&, const Grid&);

    std::array<tile::Tile*, GRID_WIDTH> row(int) const;
    void row(std::array<tile::Tile*, GRID_WIDTH>&, int);
    std::array<tile::Tile*, GRID_HEIGHT> col(int) const;
    void col(std::array<tile::Tile*, GRID_HEIGHT>&, int);

    void add_right(std::array<tile::Tile*, GRID_WIDTH>&);
    void move_right(std::array<tile::Tile*, GRID_WIDTH>&);

    void add_left(std::array<tile::Tile*, GRID_WIDTH>&);
    void move_left(std::array<tile::Tile*, GRID_WIDTH>&);

    void move_board_right();
    void move_board_left();
    void move_board_up();
    void move_board_down();

    bool check_unmove();

    void draw_grid(SDL_Renderer*, SDL_Rect&);
    void updateFont();
    void reset(SDL_Renderer* renderer);

    // Score handling
    int getHighScore();
    void updateHighScore();
    int score() const;
    void score(int); 

    // Gets fonts
    TTF_Font* numFont() const;
    TTF_Font* bigNumFont() const;

    std::array<std::array<tile::Tile*, GRID_WIDTH>, GRID_HEIGHT> Board() const;
    std::array<std::array<tile::Tile, GRID_WIDTH>, GRID_HEIGHT> derefGrid() const;

    friend void gen_num(Grid&);
    friend bool grid_comp(std::array<std::array<tile::Tile, GRID_WIDTH>, GRID_HEIGHT>&, std::array<std::array<tile::Tile, GRID_WIDTH>, GRID_HEIGHT>&);

    private:
    std::array<std::array<tile::Tile*, GRID_WIDTH>, GRID_HEIGHT> Board_; 
    int score_, highScore_;
    int posX_, posY_;
    TTF_Font *bigNumFont_, *numFont_;

};
namespace grid{
    std::ostream& operator<<(std::ostream&, const Grid&);
    void gen_num(Grid&);
    bool grid_comp(std::array<std::array<tile::Tile, GRID_WIDTH>, GRID_HEIGHT>&, std::array<std::array<tile::Tile, GRID_WIDTH>, GRID_HEIGHT>&);
}
#endif