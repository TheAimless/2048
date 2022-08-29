#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "grid.h"
#include "tile.h"

const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
const int fg = 469;

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow(
        "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font* numFont = TTF_OpenFont("Helvetica.ttf", 30);
    grid::Grid* x = new grid::Grid(numFont, renderer);

    {
        bool running = true;

        while (running){
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT || x->check_unmove()){
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                    else if (event.key.keysym.sym == SDLK_w){
                        auto board1 = x->derefGrid();
                        x->move_board_up();
                        auto board2 = x->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*x);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_a){
                        auto board1 = x->derefGrid();
                        x->move_board_left();
                        auto board2 = x->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*x);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_s){
                        auto board1 = x->derefGrid();
                        x->move_board_down();
                        auto board2 = x->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*x);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_d){
                        auto board1 = x->derefGrid();
                        x->move_board_right();
                        auto board2 = x->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*x);
                        }
                    }
                }
            }
            // Renders background
            SDL_SetRenderDrawColor(renderer, 0xfa, 0xf8, 0xef, 0xff);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0xbb, 0xad, 0xa0, 0xff);
            SDL_Rect rect{WINDOW_WIDTH / 2 - fg / 2, WINDOW_HEIGHT / 2 - fg / 2, fg, fg};
            SDL_RenderFillRect(renderer, &rect);

            SDL_Color tileColor{0xcd, 0xc1, 0xb4, 0xff};
            SDL_Color textColor{0xff, 0xff, 0xff, 0xff};
            x->draw_grid(renderer, tileColor, textColor);
            
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(numFont);
    SDL_Quit();
    delete x;
    return 0;
}