#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "grid.h"
#include "tile.h"
#include "titleScreen.h"
#include "score.h"

const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
const int fg = 469;

const SDL_Color background = {0xfa, 0xf8, 0xef, 0xff};
SDL_Rect containerRect = 
    {WINDOW_WIDTH / 2 - fg / 2, WINDOW_HEIGHT / 2 - fg / 2, fg, fg};

enum level{
    TITLE_SCREEN,
    MAIN_GAME
};

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow(
        "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    std::string name = "2048";
    title::Title* gameTitle = new title::Title(name);
    SDL_Rect scoreBox = {100, 100, 120, 75}, highScoreBox = {300, 300, 225, 75};
    std::string scoreName = "SCORE", highScoreName = "BEST";
    SDL_Color boxColor = {0xbb, 0xad, 0xa0, 0xff};
    SDL_Color textColor = {0xee, 0xe4, 0xda, 0xff};
    SDL_Color scoreColor = {0xff, 0xff, 0xff, 0xff};
    score::Score* lowScore = new score::Score(scoreBox, scoreName, boxColor, textColor, 25, 0, scoreColor);
    score::Score* highScore = new score::Score(highScoreBox, highScoreName, boxColor, textColor, 25, 0, scoreColor);

    grid::Grid* game = new grid::Grid(renderer, highScore);

    {
        bool running = true;
        level curLevel = TITLE_SCREEN;

        while (running){
            SDL_SetRenderDrawColor(
                renderer, background.r, background.g, background.b, background.a);
            SDL_RenderClear(renderer);
            SDL_Event event;
            switch(curLevel){
            case MAIN_GAME:
                while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT || game->check_unmove()){
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                    else if (event.key.keysym.sym == SDLK_w){
                        auto board1 = game->derefGrid();
                        game->move_board_up();
                        auto board2 = game->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*game);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_a){
                        auto board1 = game->derefGrid();
                        game->move_board_left();
                        auto board2 = game->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*game);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_s){
                        auto board1 = game->derefGrid();
                        game->move_board_down();
                        auto board2 = game->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*game);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_d){
                        auto board1 = game->derefGrid();
                        game->move_board_right();
                        auto board2 = game->derefGrid();
                        if (!grid::grid_comp(board1, board2)){
                            grid::gen_num(*game);
                        }
                    }
                }
            }

                game->updateFont();
                lowScore->updateScore(game->score());

                lowScore->displayScore(renderer);
                highScore->displayScore(renderer);
                game->draw_grid(renderer, containerRect);
                break;

            case TITLE_SCREEN:
                while (SDL_PollEvent(&event)){
                    switch(event.type){
                        case SDL_QUIT:
                        running = false;
                        break;

                        case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE){
                            running = false;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        int x, y;
                        auto buttons = SDL_GetMouseState(&x, &y);

                        if (gameTitle->playClicked(x, y)){
                            curLevel = MAIN_GAME;
                        }
                        else if (gameTitle->quitClicked(x, y)){
                            running = false;
                        }
                        break;
                    }
                }
                gameTitle->renderAll(renderer);
            }
            SDL_RenderPresent(renderer);
        }
    }
    game->updateHighScore(highScore);
    std::cout << "Score: " 
              << game->score()
              << "\nHigh Score: " 
              << game->getHighScore(highScore) 
              << '\n';

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete game;
    delete lowScore, highScore;
    return 0;
}