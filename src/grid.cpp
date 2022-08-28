#include "grid.h"
#include "tile.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace grid;

namespace grid{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_num(0, 7);
}

Grid::Grid(TTF_Font* numFont, SDL_Renderer* renderer){
    for (int j = 0; j < GRID_HEIGHT; ++j){
        for (int i = 0; i < GRID_WIDTH; ++i){
            this->Board_[i][j] = new tile::Tile(
                0, X0 + GAP * j + tile::TILE_WIDTH * j
                , Y0 + GAP * i + tile::TILE_HEIGHT * i, numFont, renderer);
            auto curTile = this->Board_[i][j];
            curTile->value(0);
        }
    }
    gen_num(*this);
    gen_num(*this);
}

Grid::~Grid(){
    for (int i = 0; i < GRID_HEIGHT; ++i){
        for (int j = 0; j < GRID_WIDTH; ++j){
            delete this->Board_[i][j];
        }
    }
}

std::array<tile::Tile*, GRID_WIDTH> Grid::row(int rowNum) const{
    return Board_[rowNum];
}

void Grid::row(std::array<tile::Tile*, GRID_WIDTH>& row, int rowNum){
    Board_[rowNum] = std::move(row);
}

std::array<tile::Tile*, GRID_HEIGHT> Grid::col(int colNum) const{
    std::array<tile::Tile*, GRID_HEIGHT> col;
    for (int i = 0; i < GRID_HEIGHT; ++i){
        col[i] = Board_[i][colNum];
    }
    return col;
}

void Grid::col(std::array<tile::Tile*, GRID_HEIGHT>& col, int colNum){
    for (int i = 0; i < GRID_HEIGHT; ++i){
        Board_[i][colNum] = std::move(col[i]);
    }
}

void Grid::add_right(std::array<tile::Tile*, GRID_WIDTH>& row){
    if (*row[3] != 0){
        if (*row[2] == *row[3]){
            *row[3] += *row[2];
            row[2]->value(0);
        }
        else if (*row[2] == 0 && *row[1] == *row[3]){
            *row[3] += *row[1];
            row[1]->value(0);
        }
        else if (*row[2] == 0 && *row[1] == 0 && *row[0] == *row[3]){
            *row[3] += *row[0];
            row[0]->value(0);
        }
    }
    if (*row[2] != 0){
        if (*row[2] == *row[1]){
            *row[2] += *row[1];
            row[1]->value(0);
        }
        else if (*row[1] == 0 && *row[0] == *row[2]){
            *row[2] += *row[0];
            row[0]->value(0);
        }
    }
    if (*row[1] != 0){
        if (*row[1] == *row[0]){
            *row[1] += *row[0];
            row[0]->value(0);
        }
    }
}

void Grid::move_right(std::array<tile::Tile*, GRID_WIDTH>& row){
    for (int i = GRID_WIDTH - 1; i >= 0; --i){
        if (*row[i] == 0) continue;
        else{
            for (int j = 3; j > i; --j){
                if (*row[j] == 0){
                    row[j]->value(row[i]->value());
                    row[i]->value(0);
                }
            }
        }
    }
}

void Grid::add_left(std::array<tile::Tile*, GRID_WIDTH>& row){
    std::reverse(row.begin(), row.end());
    Grid::add_right(row);
    std::reverse(row.begin(), row.end());
}

void Grid::move_left(std::array<tile::Tile*, GRID_WIDTH>& row){
    std::reverse(row.begin(), row.end());
    Grid::move_right(row);
    std::reverse(row.begin(), row.end());
}

namespace grid{
    std::ostream& operator<<(std::ostream& os, const Grid& gameGrid){
        for (int i = 0; i < GRID_HEIGHT; ++i){
            for (int j = 0; j < GRID_WIDTH; ++j){
                os << gameGrid.Board_[i][j]->value() << ' ';
            }
            os << '\n'; 
        }
        return os;
    }

    void gen_num(Grid& gameGrid){
        std::vector<int> idx;
        for (int i = 0; i < GRID_HEIGHT; ++i){
            for (int j = 0; j < GRID_WIDTH; ++j){
                int value = gameGrid.Board()[i][j]->value(); 
                if (value == 0){
                    idx.push_back(i * 4 + j);
                }
            }
        }
        auto rand_num_ = std::uniform_int_distribution<>(0, (int) idx.size() - 1);
        int pos = idx[rand_num_(gen)];
        tile::set_random(*gameGrid.Board_[pos / 4][pos % 4]);
    }
}

std::array<std::array<tile::Tile*, GRID_WIDTH>, GRID_HEIGHT> Grid::Board() const{
    return Board_;
}

void Grid::move_board_right(){
    for (int i = 0; i < GRID_HEIGHT; ++i){
        add_right(this->Board_[i]);
        move_right(this->Board_[i]);
    }
}

void Grid::move_board_left(){
    for (int i = 0; i < GRID_HEIGHT; ++i){
        add_left(this->Board_[i]);
        move_left(this->Board_[i]);
    }
}

void Grid::move_board_down(){
    for (int i = 0; i < GRID_WIDTH; ++i){
        auto col = this->col(i);
        add_right(col);
        move_right(col);
        this->col(col, i);
    }
}

void Grid::move_board_up(){
    for (int i = 0; i < GRID_WIDTH; ++i){
        auto col = this->col(i);
        add_left(col);
        move_left(col);
        this->col(col, i);
    }
}

bool Grid::check_unmove(){
    for (int i = 0; i < GRID_HEIGHT; ++i){
        for (int j = 0; j < GRID_WIDTH; ++j){
            int val = this->Board_[i][j]->value();
            if (val == 0){
                return false;
            }
        }
    }

    for (int i = 0; i < GRID_HEIGHT; ++i){
        for (int j = 0; j < GRID_WIDTH - 1; ++j){
            int cur = this->Board_[i][j]->value();
            int nex = this->Board_[i][j + 1]->value();
            if (cur == nex){
                return false;
            }
        }
    }

    for (int j = 0; j < GRID_WIDTH; ++j){
        for (int i = 0; i < GRID_HEIGHT - 1; ++i){
            int cur = this->Board_[i][j]->value();
            int nex = this->Board_[i + 1][j]->value();
            if (cur == nex){
                return false;
            }
        }   
    }
    return true;
}

void Grid::draw_grid(SDL_Renderer *renderer, SDL_Color &tileColor, SDL_Color &textColor){
    for (int i = 0; i < GRID_WIDTH; ++i){
        for (int j = 0; j < GRID_HEIGHT; ++j){
            auto tile = *this->Board_[i][j];
            SDL_SetRenderDrawColor(renderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);
            tile::draw(tile);
            SDL_SetRenderDrawColor(renderer, textColor.r, textColor.g, textColor.b, textColor.a);
            tile.display();
            tile::drawVal(tile);
        }
    }
}