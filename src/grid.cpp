#include "grid.h"
#include "tile.h"
#include <iostream>
#include <algorithm>
#include <vector>
//#include <SDL2/SDL.h>
using namespace grid;

Grid::Grid(){
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            this->Board_[i][j] = new tile::Tile(0, i, j);
            auto curTile = this->Board_[i][j];
            curTile->value(0);
        }
    }
    rd_ = new std::random_device();
    gen_ = new std::mt19937((*rd_)());
    gen_num(*this);
    gen_num(*this);
}

Grid::~Grid(){
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            delete this->Board_[i][j];
        }
    }
    delete this->rd_;
    delete this->gen_;
    delete this->rand_num_;
}

std::array<tile::Tile*, width> Grid::row(int rowNum) const{
    return Board_[rowNum];
}

void Grid::row(std::array<tile::Tile*, width>& row, int rowNum){
    Board_[rowNum] = std::move(row);
}

std::array<tile::Tile*, height> Grid::col(int colNum) const{
    std::array<tile::Tile*, height> col;
    for (int i = 0; i < height; ++i){
        col[i] = Board_[i][colNum];
    }
    return col;
}

void Grid::col(std::array<tile::Tile*, height>& col, int colNum){
    for (int i = 0; i < height; ++i){
        Board_[i][colNum] = std::move(col[i]);
    }
}

void Grid::add_right(std::array<tile::Tile*, width>& row){
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

void Grid::move_right(std::array<tile::Tile*, width>& row){
    for (int i = width; i >= 0; --i){
        if (*row[i] == 0) continue;
        else{
            for (int j = 3; j > i; --j){
                if (*row[j] == 0){
                    *row[j] = *row[i];
                    row[i]->value(i);
                }
            }
        }
    }
}

void Grid::add_left(std::array<tile::Tile*, width>& row){
    //Temporary
    std::reverse(row.begin(), row.end());
    Grid::add_right(row);
    std::reverse(row.begin(), row.end());
}

void Grid::move_left(std::array<tile::Tile*, width>& row){
    //Temporary
    std::reverse(row.begin(), row.end());
    Grid::move_right(row);
    std::reverse(row.begin(), row.end());
}

namespace grid{
    std::ostream& operator<<(std::ostream& os, const Grid& gameGrid){
        for (int i = 0; i < height; ++i){
            for (int j = 0; j < width; ++j){
                //os << tile::value(*gameGrid.Board_[i][j]) << ' ';
                os << gameGrid.Board_[i][j]->value() << ' ';
            }
            os << '\n'; 
        }
        return os;
    }

    void gen_num(Grid& gameGrid){
        std::vector<int> idx;
        for (int i = 0; i < height; ++i){
            for (int j = 0; j < width; ++j){
                int value = gameGrid.Board_[i][j]->value(); 
                if (value == 0){
                    idx.push_back(i * 4 + j);
                }
            }
        }
        gameGrid.rand_num_ = new std::uniform_int_distribution<>(0, (int) idx.size() - 1);
        int pos = idx[(*(gameGrid.rand_num()))(*(gameGrid.gen()))];
        tile::set_random(*gameGrid.Board_[pos / 4][pos % 4]);
    }
}

std::mt19937* Grid::gen() const{
    return gen_;
}

std::uniform_int_distribution<>* Grid::rand_num() const{
    return rand_num_;
}

std::array<std::array<tile::Tile*, width>, height> Grid::Board() const{
    return Board_;
}

void Grid::move_board_right(){
    for (int i = 0; i < height; ++i){
        add_right(this->Board_[i]);
        move_right(this->Board_[i]);
    }
}

void Grid::move_board_left(){
    for (int i = 0; i < height; ++i){
        add_left(this->Board_[i]);
        move_left(this->Board_[i]);
    }
}

void Grid::move_board_down(){
    for (int i = 0; i < width; ++i){
        auto col = this->col(i);
        add_right(col);
        move_right(col);
        this->col(col, i);
    }
}

void Grid::move_board_up(){
    for (int i = 0; i < width; ++i){
        auto col = this->col(i);
        add_left(col);
        move_left(col);
        this->col(col, i);
    }
}

bool Grid::check_unmove(){
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            int val = this->Board_[i][j]->value();
            if (val == 0){
                return false;
            }
        }
    }

    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width - 1; ++j){
            int cur = this->Board_[i][j]->value();
            int nex = this->Board_[i][j + 1]->value();
            if (cur == nex){
                return false;
            }
        }
    }

    for (int j = 0; j < width; ++j){
        for (int i = 0; i < height - 1; ++i){
            int cur = this->Board_[i][j]->value();
            int nex = this->Board_[i + 1][j]->value();
            if (cur == nex){
                return false;
            }
        }   
    }
    return true;
}