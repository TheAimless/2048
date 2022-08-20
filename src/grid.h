#ifndef GRID_h_
#define GRID_h_
#include <array>
#include <random>
#include "tile.h"


/* To be included:
   RNG on grid (i.e. generate 1 or 2 random numbers on grid)
*/

static const int width = 4, height = 4;

namespace grid{
    class Grid;
}

class grid::Grid{
    public:
    Grid ();

    friend std::ostream& operator<<(std::ostream&, const Grid&);

    friend std::array<tile::Tile*, width> get_row(const Grid&, int);
    friend void set_row(Grid&, std::array<tile::Tile*, width>, int);

    friend std::array<tile::Tile*, height> get_column(const Grid&, int);
    friend void set_column(Grid&, std::array<tile::Tile*, height>, int);

    void add_right(std::array<tile::Tile*, width>&);
    void move_right(std::array<tile::Tile*, width>&);

    void add_left(std::array<tile::Tile*, width>&);
    void move_left(std::array<tile::Tile*, width>&);

    friend std::mt19937* get_gen(const Grid&);
    friend std::uniform_int_distribution<>* get_randNum(const Grid&);
    friend void gen_num(Grid&);
    friend std::array<std::array<tile::Tile*, width>, height> getBoard(Grid&);

    private:
    std::array<std::array<tile::Tile*, width>, height> Board; 
    std::random_device *rd;
    std::mt19937 *gen;
    std::uniform_int_distribution<> *rand_num;
};
namespace grid{
    std::ostream& operator<<(std::ostream&, const Grid&);

    std::array<tile::Tile*, width> get_row(const Grid&, int);
    void set_row(Grid&, std::array<tile::Tile*, width>, int);

    std::array<tile::Tile*, height> get_column(const Grid&, int);
    void set_column(Grid&, std::array<tile::Tile*, height>, int);

    std::mt19937* get_gen(const Grid&);
    std::uniform_int_distribution<>* get_randNum(const Grid&);
    void gen_num(Grid&);
    std::array<std::array<tile::Tile*, width>, height> getBoard(Grid&);
}
#endif