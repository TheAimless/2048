#ifndef GRID_h_
#define GRID_h_
#include <array>
#include <random>
#include "tile.h"

namespace grid{
    static const int width = 4, height = 4;
    class Grid;
    extern std::random_device rd;
    extern std::mt19937 gen;
    extern std::uniform_int_distribution<> rand_num;
}

class grid::Grid{
    public:
    Grid();
    ~Grid();

    friend std::ostream& operator<<(std::ostream&, const Grid&);

    std::array<tile::Tile*, width> row(int) const;
    void row(std::array<tile::Tile*, width>&, int);
    std::array<tile::Tile*, height> col(int) const;
    void col(std::array<tile::Tile*, height>&, int);

    void add_right(std::array<tile::Tile*, width>&);
    void move_right(std::array<tile::Tile*, width>&);

    void add_left(std::array<tile::Tile*, width>&);
    void move_left(std::array<tile::Tile*, width>&);

    void move_board_right();
    void move_board_left();
    void move_board_up();
    void move_board_down();
    
    bool check_unmove();

    std::array<std::array<tile::Tile*, width>, height> Board() const;

    friend void gen_num(Grid&);

    private:
    std::array<std::array<tile::Tile*, width>, height> Board_; 
};
namespace grid{
    std::ostream& operator<<(std::ostream&, const Grid&);
    void gen_num(Grid&);
}
#endif