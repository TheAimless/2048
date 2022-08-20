#include <iostream>
#include "grid.h"
#include "tile.h"

int main(){
    grid::Grid* x = new grid::Grid();
    auto board = grid::getBoard(*x);
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            std::cout << tile::get_value(*board[i][j]) << ' ';
        }
        std::cout << '\n';
    }
}