#include <iostream>
#include "grid.h"
#include "tile.h"

int main(){
    //grid::Grid* x = new grid::Grid();
    //auto board = x->Board();
    bool running = false;
    /*while (running){
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j){
                std::cout << board[i][j]->value() << ' ';
            }
            std::cout << '\n';
        }
        if (x->check_unmove()){
            running = false;
            break;
        }
        std::cout << "Input: ";
        char input;
        std::cin >> input;
        if (input == 'd'){
            x->move_board_right();
        }
        else if (input == 'a'){
            x->move_board_left();
        }
        else if (input == 's'){
            x->move_board_down();
        }
        else if (input == 'w'){
            x->move_board_up();
        }
        grid::gen_num(*x);
    }*/
    tile::Tile arr[4];
    for (int i = 0; i < width; ++i){
        arr[i] = tile::Tile(0, 0, 0);
    }

    for (int i = 0; i < width; ++i){
        std::cout << arr[i].value() << ' ';
    }
    std::cout << std::endl;
    try{
        tile::Tile t = static_cast<tile::Tile>(arr[2]) + static_cast<tile::Tile>(arr[3]);
        std::cout << (t).value();
    }
    catch (...){
        std::cout << "Error" << '\n';
    }

    /*if (*arr[3] != 0){
        if (*arr[2] == *arr[3]){
            *arr[3] += *arr[2];
            arr[2]->value(0);
        }
        else if (*arr[2] == 0 && *arr[1] == *arr[3]){
            *arr[3] += *arr[1];
            arr[1]->value(0);
        }
        else if (*arr[2] == 0 && *arr[1] == 0 && *arr[0] == *arr[3]){
            *arr[3] += *arr[0];
            arr[0]->value(0);
        }
    }*/
    /*if (*arr[2] != 0){
        if (*arr[2] == *arr[1]){
            *arr[2] += *arr[1];
            arr[1]->value(0);
        }
        else if (*arr[1] == 0 && *arr[0] == *arr[2]){
            *arr[2] += *arr[0];
            arr[0]->value(0);
        }
    }
    if (*arr[1] != 0){
        if (*arr[1] == *arr[0]){
            *arr[1] += *arr[0];
            arr[0]->value(0);
        }
    }*/
    //delete x;
    return 0;
}