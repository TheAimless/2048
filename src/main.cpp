#include <SDL2/SDL.h>
#include <iostream>
#include "grid.h"
#include "tile.h"

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    grid::Grid* x = new grid::Grid();

    {
        auto board = x->Board();
        bool running = true;

        while (running){
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                for (int i = 0; i < grid::height; ++i){
                    for (int j = 0; j < grid::width; ++j){
                        std::cout << board[i][j]->value() << ' ';
                    }
                    std::cout << '\n'; 
                }
                std::cout << '\n';

                if (event.type == SDL_QUIT || x->check_unmove()){
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                    else if (event.key.keysym.sym == SDLK_w){
                        x->move_board_up();
                    }
                    else if (event.key.keysym.sym == SDLK_a){
                        x->move_board_left();
                    }
                    else if (event.key.keysym.sym == SDLK_s){
                        x->move_board_down();
                    }
                    else if (event.key.keysym.sym == SDLK_d){
                        x->move_board_right();
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xfa, 0xf8, 0xef, 0xff);
            SDL_RenderClear(renderer);
            
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete x;
    return 0;
}