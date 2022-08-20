#include "grid.h"
#include "tile.h"
#include <iostream>
#include <algorithm>
#include <vector>
//#include <SDL2/SDL.h>

grid::Grid::Grid(){
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            this->Board[i][j] = new tile::Tile(0, i, j);
            auto curTile = this->Board[i][j];
            tile::set_value(*curTile, 0);
        }
    }
    rd = new std::random_device();
    gen = new std::mt19937((*rd)());
    grid::gen_num(*this);
    grid::gen_num(*this);
}

namespace grid{
    std::array<tile::Tile*, width> get_row(const Grid& gameGrid, int rowNum){
        return gameGrid.Board[rowNum];
    }

    void set_row(Grid& gameGrid, std::array<tile::Tile*, width> row, int rowNum){
        gameGrid.Board[rowNum] = row;
    }

    std::array<tile::Tile*, height> get_column(const Grid& gameGrid, int colNum){
        std::array<tile::Tile*, height> col;
        for (int i = 0; i < height; ++i){
            col[i] = gameGrid.Board[i][colNum];
        }
        return col;
    }

    void set_column(Grid& gameGrid, std::array<tile::Tile*, height> col, int colNum){
        for (int i = 0; i < height; ++i){
            gameGrid.Board[i][colNum] = col[i];
        }
    }
}

void grid::Grid::add_right(std::array<tile::Tile*, width>& row){
    if (*row[3] != 0){
        if (*row[2] == *row[3]){
            *row[3] += *row[2];
            tile::set_value(*row[2], 0);
        }
        else if (*row[2] == 0 && *row[1] == *row[3]){
            *row[3] += *row[1];
            tile::set_value(*row[1], 0);
        }
        else if (*row[2] == 0 && *row[1] == 0 && *row[0] == *row[3]){
            *row[3] += *row[0];
            tile::set_value(*row[0], 0);
        }
    }
    if (*row[2] != 0){
        if (*row[2] == *row[1]){
            *row[2] += *row[1];
            tile::set_value(*row[1], 0);
        }
        else if (*row[1] == 0 && *row[0] == *row[2]){
            *row[2] += *row[0];
            tile::set_value(*row[0], 0);
        }
    }
    if (*row[1] != 0){
        if (*row[1] == *row[0]){
            *row[1] += *row[0];
            tile::set_value(*row[0], 0);
        }
    }
}

void grid::Grid::move_right(std::array<tile::Tile*, width>& row){
    for (int i = 3; i >= 0; --i){
        if (*row[i] == 0) continue;
        else{
            for (int j = 3; j > i; --j){
                if (*row[j] == 0){
                    *row[j] = *row[i];
                    tile::set_value(*row[i], 0);
                }
            }
        }
    }
}

void grid::Grid::add_left(std::array<tile::Tile*, width>& row){
    //Temporary
    std::reverse(row.begin(), row.end());
    grid::Grid::add_right(row);
    std::reverse(row.begin(), row.end());
}

void grid::Grid::move_left(std::array<tile::Tile*, width>& row){
    //Temporary
    std::reverse(row.begin(), row.end());
    grid::Grid::move_left(row);
    std::reverse(row.begin(), row.end());
}

namespace grid{
    std::ostream& operator<<(std::ostream& os, const Grid& gameGrid){
        for (int i = 0; i < height; ++i){
            for (int j = 0; j < width; ++j){
                os << tile::get_value(*gameGrid.Board[i][j]) << ' ';
            }
            os << '\n'; 
        }
        return os;
    }

    std::mt19937* get_gen(const Grid& lhs){
        return lhs.gen;
    }

    std::uniform_int_distribution<>* get_randNum(const Grid& lhs){
        return lhs.rand_num;
    }

    void gen_num(Grid& gameGrid){
        std::vector<int> idx;
        for (int i = 0; i < height; ++i){
            for (int j = 0; j < width; ++j){
                int value = tile::get_value(*gameGrid.Board[i][j]); 
                if (value == 0){
                    idx.push_back(i * 4 + j);
                }
            }
        }
        gameGrid.rand_num = new std::uniform_int_distribution<>(0, (int) idx.size() - 1);
        int pos = idx[(*get_randNum(gameGrid))(*(get_gen(gameGrid)))];
        tile::set_random(*gameGrid.Board[pos / 4][pos % 4]);
    }
    std::array<std::array<tile::Tile*, width>, height> getBoard(Grid& gameGrid){
        return gameGrid.Board;
    }
}